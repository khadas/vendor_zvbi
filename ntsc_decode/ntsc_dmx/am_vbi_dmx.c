/***************************************************************************
 *	Copyright C 2009 by Amlogic, Inc. All Rights Reserved.
 */
/**\file
 * \brief
 *
 * \author Gong Ke <ke.gong@amlogic.com>
 * \date 2010-05-21: create the document
 ***************************************************************************/

#define AM_DEBUG_LEVEL 1

#include "am_vbi_internal.h"
#include "vbi_dmx.h"
#include <string.h>
#include <assert.h>

/****************************************************************************
 * Macro definitions
 ***************************************************************************/

//#define DMX_WAIT_CB /*Wait callback function stop in API*/

#define DMX_SYNC

#define DMX_BUF_SIZE	   (4096)
#define DMX_POLL_TIMEOUT   (200)

#define DMX_DEV_COUNT	   (2)


#define DMX_CHAN_ISSET_FILTER(chan,fid)	   ((chan)->filter_mask[(fid)>>3]&(1<<((fid)&3)))
#define DMX_CHAN_SET_FILTER(chan,fid)	   ((chan)->filter_mask[(fid)>>3]|=(1<<((fid)&3)))
#define DMX_CHAN_CLR_FILTER(chan,fid)	   ((chan)->filter_mask[(fid)>>3]&=~(1<<((fid)&3)))


/****************************************************************************
 * Static data
 ***************************************************************************/


extern const  AM_VBI_Driver_t linux_vbi_drv ;

pthread_mutex_t am_gAdpLock	 = PTHREAD_MUTEX_INITIALIZER;

static AM_VBI_Device_t dmx_devices[DMX_DEV_COUNT] =
{

{
.drv = &linux_vbi_drv,
.src = DUAL_FD1,
},
{
.drv = &linux_vbi_drv,
.src = DUAL_FD2,
}
};

/****************************************************************************
 * Static functions
 ***************************************************************************/

/**\brief Get the device structure pointer according to the device number*/
static inline AM_ErrorCode_t dmx_get_dev(int dev_no, AM_VBI_Device_t **dev)
{
	if ((dev_no < 0) || (dev_no >= DMX_DEV_COUNT))
	{
		AM_DEBUG("invalid demux device number %d, must in(%d~%d)", dev_no, 0, DMX_DEV_COUNT-1);
		return AM_VBI_DMX_ERR_INVALID_DEV_NO;
	}

	*dev = &dmx_devices[dev_no];
	return AM_SUCCESS;
}

/**\brief Get the device structure according to the device number and check if the device is open*/
static inline AM_ErrorCode_t dmx_get_openned_dev(int dev_no, AM_VBI_Device_t **dev)
{
	int ret = (dmx_get_dev(dev_no, dev));

	if (!(*dev)->opened)
	{
		AM_DEBUG( "demux device %d has not been opened", dev_no);
		return AM_VBI_DMX_ERR_INVALID_DEV_NO;
	}

	return AM_SUCCESS;
}

/**\brief Get the corresponding filter structure according to the ID, and check whether the device is in use*/
static inline AM_ErrorCode_t dmx_get_used_filter(AM_VBI_Device_t *dev, int filter_id, AM_VBI_Filter_t **pf)
{
	AM_VBI_Filter_t *filter;

	if ((filter_id < 0) || (filter_id >= DMX_FILTER_COUNT))
	{
		AM_DEBUG( "invalid filter id, must in %d~%d", 0, DMX_FILTER_COUNT-1);
		return AM_VBI_DMX_ERR_INVALID_ID;
	}

	filter = &dev->filters[filter_id];

	if (!filter->used)
	{
		AM_DEBUG( "filter %d has not been allocated", filter_id);
		return AM_VBI_DMX_ERR_NOT_ALLOCATED;
	}

	*pf = filter;
	return AM_SUCCESS;
}

/**\brief data detection thread*/
static void* dmx_data_thread(void *arg)
{
	AM_VBI_Device_t *dev = (AM_VBI_Device_t*)arg;
	static uint8_t sec_buf[128];
	uint8_t *sec;
	int sec_len;
	AM_VBI_FilterMask_t mask;
	AM_ErrorCode_t ret;
	int count = 0;
	while (dev->enable_thread)
	{
		//**********************************temp****************
		AM_DEBUG( "***************!!!!thread count = %d\n",count++);
		//if(count ++ == 100)
		//	break;
		//**********************************finish****************
		AM_DMX_FILTER_MASK_CLEAR(&mask);
		int id;

		ret = dev->drv->poll(dev, &mask, DMX_POLL_TIMEOUT);
		if (ret == AM_SUCCESS)
		{
			AM_DEBUG( "***************thread AM_SUCCESS **********\n");
			if (AM_DMX_FILTER_MASK_ISEMPTY(&mask))
				continue;

#if defined(DMX_WAIT_CB) || defined(DMX_SYNC)
			pthread_mutex_lock(&dev->lock);
			dev->flags |= DMX_FL_RUN_CB;
			pthread_mutex_unlock(&dev->lock);
#endif

			for (id=0; id<DMX_FILTER_COUNT; id++)
			{
				AM_VBI_Filter_t *filter=&dev->filters[id];
				AM_DMX_DataCb cb;
				void *data;

				if (!AM_DMX_FILTER_MASK_ISSET(&mask, id))
					continue;

				if (!filter->enable || !filter->used)
					continue;

				sec_len = sizeof(sec_buf);

#ifndef DMX_WAIT_CB
				pthread_mutex_lock(&dev->lock);
#endif
				if (!filter->enable || !filter->used)
				{
					ret = AM_FAILURE;
				}
				else
				{
					cb	 = filter->cb;
					data = filter->user_data;
					ret	 = dev->drv->read(dev, filter, sec_buf, &sec_len);
				}
#ifndef DMX_WAIT_CB
				pthread_mutex_unlock(&dev->lock);
#endif
				if (ret == AM_VBI_DMX_ERR_TIMEOUT)
				{
					sec = NULL;
					sec_len = 0;
				}
				else if (ret!=AM_SUCCESS)
				{
					continue;
				}
				else
				{
					sec = sec_buf;
				}

				if (cb)
				{
					if (id && sec) {
						int fd = (long)filter->drv_data;
						AM_DEBUG( "filter %d data callback len fd:%d len:%d, %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x",
						id, fd, sec_len,
						sec[0], sec[1], sec[2], sec[3], sec[4],
						sec[5], sec[6], sec[7], sec[8], sec[9]);
					}
					cb(dev->dev_no, id, sec, sec_len, data);
					if (id && sec)
					AM_DEBUG( "filter %d data callback ok", id);
				}
			}
#if defined(DMX_WAIT_CB) || defined(DMX_SYNC)
			pthread_mutex_lock(&dev->lock);
			dev->flags &= ~DMX_FL_RUN_CB;
			pthread_mutex_unlock(&dev->lock);
			pthread_cond_broadcast(&dev->cond);
#endif
		}
		else
			AM_DEBUG( "poll fail \n");
		usleep(1000 * 200);
	}

	return NULL;
}

/**\brief wait for the callback function to stop running */
static inline AM_ErrorCode_t dmx_wait_cb(AM_VBI_Device_t *dev)
{
#ifdef DMX_WAIT_CB
	if (dev->thread != pthread_self())
	{
		while (dev->flags & DMX_FL_RUN_CB)
			pthread_cond_wait(&dev->cond, &dev->lock);
	}
#endif
	return AM_SUCCESS;
}

/**\brief stop Section filter*/
static AM_ErrorCode_t dmx_stop_filter(AM_VBI_Device_t *dev, AM_VBI_Filter_t *filter)
{
	AM_ErrorCode_t ret = AM_SUCCESS;

	if (!filter->used || !filter->enable)
	{
		return ret;
	}

	if (dev->drv->enable_filter)
	{
		ret = dev->drv->enable_filter(dev, filter, AM_FALSE);
	}

	if (ret >= 0)
	{
		filter->enable = AM_FALSE;
	}

	return ret;
}

/**\brief release filter*/
static int dmx_free_filter(AM_VBI_Device_t *dev, AM_VBI_Filter_t *filter)
{
	AM_ErrorCode_t ret = AM_SUCCESS;

	if (!filter->used)
		return ret;

	ret = dmx_stop_filter(dev, filter);

	if (ret == AM_SUCCESS)
	{
		if (dev->drv->free_filter)
		{
			ret = dev->drv->free_filter(dev, filter);
		}
	}

	if (ret == AM_SUCCESS)
	{
		filter->used = AM_FALSE;
	}

	return ret;
}

/**************************************************** ****************************
 * API functions
 **************************************************** ************************/

/**\brief Open the demultiplexing device
 * \param dev_no demultiplexing device number
 * \param[in] para Demultiplexing device startup parameters
 * \return
 * - AM_SUCCESS success
 * - other value error code (see am_dmx.h)
 */
AM_ErrorCode_t AM_NTSC_DMX_Open(int dev_no, const AM_VBI_DMX_OpenPara_t *para)
{
	AM_VBI_Device_t *dev;
	AM_ErrorCode_t ret = AM_SUCCESS;

	assert(para);

	ret = (dmx_get_dev(dev_no, &dev));

	pthread_mutex_lock(&am_gAdpLock);

	if (dev->opened)
	{
		AM_DEBUG("demux device %d has already been opened", dev_no);
		ret = AM_VBI_DMX_ERR_BUSY;
		goto final;
	}

	dev->dev_no = dev_no;

	if (dev->drv->open)
	{
		ret = dev->drv->open(dev, para);
	}

	if (ret == AM_SUCCESS)
	{
		pthread_mutex_init(&dev->lock, NULL);
		pthread_cond_init(&dev->cond, NULL);
		dev->enable_thread = AM_TRUE;
		dev->flags = 0;

		if (pthread_create(&dev->thread, NULL, dmx_data_thread, dev))
		{
			pthread_mutex_destroy(&dev->lock);
			pthread_cond_destroy(&dev->cond);
			ret = AM_VBI_DMX_ERR_CANNOT_CREATE_THREAD;
		}
	}

	if (ret == AM_SUCCESS)
	{
		dev->opened = AM_TRUE;
	}
final:
	pthread_mutex_unlock(&am_gAdpLock);

	return ret;
}

/**\brief close the demultiplexing device
 * \param dev_no demultiplexing device number
 * \return
 * - AM_SUCCESS success
 * - other value error code (see am_dmx.h)
 */
AM_ErrorCode_t AM_NTSC_DMX_Close(int dev_no)
{
	AM_VBI_Device_t *dev;
	AM_ErrorCode_t ret = AM_SUCCESS;
	int i;

	ret = (dmx_get_openned_dev(dev_no, &dev));

	pthread_mutex_lock(&am_gAdpLock);

	dev->enable_thread = AM_FALSE;
	pthread_join(dev->thread, NULL);

	for (i = 0; i < DMX_FILTER_COUNT; i++)
	{
		dmx_free_filter(dev, &dev->filters[i]);
	}

	if (dev->drv->close)
	{
		dev->drv->close(dev);
	}

	pthread_mutex_destroy(&dev->lock);
	pthread_cond_destroy(&dev->cond);

	dev->opened = AM_FALSE;

	pthread_mutex_unlock(&am_gAdpLock);

	return ret;
}

/**\brief assigns a filter
 * \param dev_no demultiplexing device number
 * \param[out] fhandle returns the filter handle
 * \return
 * - AM_SUCCESS success
 * - other value error code (see am_dmx.h)
 */
AM_ErrorCode_t AM_NTSC_DMX_AllocateFilter(int dev_no, int *fhandle)
{
	AM_VBI_Device_t *dev;
	AM_ErrorCode_t ret = AM_SUCCESS;
	int fid;

	assert(fhandle);

	ret = (dmx_get_openned_dev(dev_no, &dev));

	pthread_mutex_lock(&dev->lock);

	for (fid=0; fid<DMX_FILTER_COUNT; fid++)
	{
		AM_DEBUG( "dev->filters[fid].used = %d\n",dev->filters[fid].used);
		if (!dev->filters[fid].used)
			break;
	}

	if (fid >= DMX_FILTER_COUNT)
	{
		AM_DEBUG( "no free section filter");
		ret = AM_VBI_DMX_ERR_NO_FREE_FILTER;
	}

	if (ret == AM_SUCCESS)
	{
		AM_DEBUG( "AM_NTSC_DMX_AllocateFilter AM_SUCCESS fid = %d\n",fid);
		dmx_wait_cb(dev);

		dev->filters[fid].id   = fid;
		if (dev->drv->alloc_filter)
		{
			ret = dev->drv->alloc_filter(dev, &dev->filters[fid]);
		}
	}

	if (ret == AM_SUCCESS)
	{
		dev->filters[fid].used = AM_TRUE;
		*fhandle = fid;

		AM_DEBUG( "allocate filter %d \n", fid);
	}

	pthread_mutex_unlock(&dev->lock);

	return ret;
}

/**\brief release a filter
  * \param dev_no demultiplexing device number
  * \param fhandle filter handle
  * \return
  * - AM_SUCCESS success
  * - other value error code (see am_dmx.h)
  */
AM_ErrorCode_t AM_NTSC_DMX_FreeFilter(int dev_no, int fhandle)
{
	AM_VBI_Device_t *dev;
	AM_VBI_Filter_t *filter;
	AM_ErrorCode_t ret = AM_SUCCESS;

	ret = (dmx_get_openned_dev(dev_no, &dev));

	pthread_mutex_lock(&dev->lock);

	ret = dmx_get_used_filter(dev, fhandle, &filter);

	if (ret == AM_SUCCESS)
	{
		dmx_wait_cb(dev);
		ret = dmx_free_filter(dev, filter);
		AM_DEBUG( "free filter %d", fhandle);
	}

	pthread_mutex_unlock(&dev->lock);

	return ret;
}

/**\brief start a filter
  * \param dev_no demultiplexing device number
  * \param fhandle filter handle
  * \return
  * - AM_SUCCESS success
  * - other value error code (see am_dmx.h)
  */
AM_ErrorCode_t AM_NTSC_DMX_StartFilter(int dev_no, int fhandle)
{
	AM_DEBUG("AM_NTSC_DMX_StartFilter*************\n");
	AM_VBI_Device_t *dev;
	AM_VBI_Filter_t *filter = NULL;
	AM_ErrorCode_t ret = AM_SUCCESS;

	ret = (dmx_get_openned_dev(dev_no, &dev));

	pthread_mutex_lock(&dev->lock);

	ret = dmx_get_used_filter(dev, fhandle, &filter);

	if (!filter->enable)
	{
		if (ret == AM_SUCCESS)
		{
			if (dev->drv->enable_filter)
			{
				ret = dev->drv->enable_filter(dev, filter, AM_TRUE);
			}
		}

		if (ret == AM_SUCCESS)
		{
			filter->enable = AM_TRUE;
		}
	}

	pthread_mutex_unlock(&dev->lock);

	return ret;
}

/**\brief stop a filter
  * \param dev_no demultiplexing device number
  * \param fhandle filter handle
  * \return
  * - AM_SUCCESS success
  * - other value error code (see am_dmx.h)
  */
AM_ErrorCode_t AM_NTSC_DMX_StopFilter(int dev_no, int fhandle)
{
	AM_VBI_Device_t *dev;
	AM_VBI_Filter_t *filter = NULL;
	AM_ErrorCode_t ret = AM_SUCCESS;

	ret = (dmx_get_openned_dev(dev_no, &dev));

	pthread_mutex_lock(&dev->lock);

	ret = dmx_get_used_filter(dev, fhandle, &filter);

	if (filter->enable)
	{
		if (ret == AM_SUCCESS)
		{
			dmx_wait_cb(dev);
			ret = dmx_stop_filter(dev, filter);
		}
	}

	pthread_mutex_unlock(&dev->lock);

	return ret;
}

/**\brief Set a filter buffer size
  * \param dev_no demultiplexing device number
  * \param fhandle filter handle
  * \param size buffer size
  * \return
  * - AM_SUCCESS success
  * - other value error code (see am_dmx.h)
  */
AM_ErrorCode_t AM_NTSC_DMX_SetBufferSize(int dev_no, int fhandle, int size)
{
	AM_VBI_Device_t *dev;
	AM_VBI_Filter_t *filter;
	AM_ErrorCode_t ret = AM_SUCCESS;

	ret = (dmx_get_openned_dev(dev_no, &dev));

	pthread_mutex_lock(&dev->lock);

	if (!dev->drv->set_buf_size)
	{
		AM_DEBUG( "do not support set_buf_size");
		ret = AM_VBI_DMX_ERR_NOT_SUPPORTED;
	}

	if (ret == AM_SUCCESS)
		ret = dmx_get_used_filter(dev, fhandle, &filter);

	if (ret == AM_SUCCESS)
		ret = dev->drv->set_buf_size(dev, filter, size);

	pthread_mutex_unlock(&dev->lock);

	return ret;
}

/**\brief Get the callback function and user parameters corresponding to a filter
  * \param dev_no demultiplexing device number
  * \param fhandle filter handle
  * \param[out] cb returns the callback function corresponding to the filter
  * \param[out] data returns user parameters
  * \return
  * - AM_SUCCESS success
  * - other value error code (see am_dmx.h)
  */
AM_ErrorCode_t AM_NTSC_DMX_GetCallback(int dev_no, int fhandle, AM_DMX_DataCb *cb, void **data)
{
	AM_VBI_Device_t *dev;
	AM_VBI_Filter_t *filter;
	AM_ErrorCode_t ret = AM_SUCCESS;

	ret = (dmx_get_openned_dev(dev_no, &dev));

	pthread_mutex_lock(&dev->lock);

	ret = dmx_get_used_filter(dev, fhandle, &filter);

	if (ret == AM_SUCCESS)
	{
		if (cb)
			*cb = filter->cb;

		if (data)
			*data = filter->user_data;
	}

	pthread_mutex_unlock(&dev->lock);

	return ret;
}

/**\brief Set the callback function and user parameters corresponding to a filter
  * \param dev_no demultiplexing device number
  * \param fhandle filter handle
  * \param[in] cb callback function
  * \param[in] data The user parameter of the callback function
  * \return
  * - AM_SUCCESS success
  * - other value error code (see am_dmx.h)
  */
AM_ErrorCode_t AM_NTSC_DMX_SetCallback(int dev_no, int fhandle, AM_DMX_DataCb cb, void *data)
{
	AM_DEBUG("AM_NTSC_DMX_SetCallback fhandle = %d\n",fhandle);
	AM_VBI_Device_t *dev;
	AM_VBI_Filter_t *filter;
	AM_ErrorCode_t ret = AM_SUCCESS;

	ret = (dmx_get_openned_dev(dev_no, &dev));

	pthread_mutex_lock(&dev->lock);

	ret = dmx_get_used_filter(dev, fhandle, &filter);

	if (ret == AM_SUCCESS)
	{
		AM_DEBUG("AM_NTSC_DMX_SetCallback AM_SUCCESS\n");
		dmx_wait_cb(dev);

		filter->cb = cb;
		filter->user_data = data;
	}

	pthread_mutex_unlock(&dev->lock);

	return ret;
}

/**\brief Set the input source of the demux device
  * \param dev_no demultiplexing device number
  * \param src input source
  * \return
  * - AM_SUCCESS success
  * - other value error code (see am_dmx.h)
  */
AM_ErrorCode_t AM_NTSC_DMX_SetSource(int dev_no, AM_VBI_DMX_Source_t src)
{
	AM_VBI_Device_t *dev;
	AM_ErrorCode_t ret = AM_SUCCESS;

	ret = (dmx_get_openned_dev(dev_no, &dev));

	pthread_mutex_lock(&dev->lock);
	if (!dev->drv->set_source)
	{
		AM_DEBUG( "do not support set_source");
		ret = AM_VBI_DMX_ERR_NOT_SUPPORTED;
	}

	if (ret == AM_SUCCESS)
	{
		ret = dev->drv->set_source(dev, src);
	}

	pthread_mutex_unlock(&dev->lock);

	if (ret == AM_SUCCESS)
	{
		pthread_mutex_lock(&am_gAdpLock);
		dev->src = src;
		pthread_mutex_unlock(&am_gAdpLock);
	}

	return ret;
}

/**\brief DMX synchronization, which can be used to wait for the callback function to finish executing
  * \param dev_no demultiplexing device number
  * \return
  * - AM_SUCCESS success
  * - other value error code (see am_dmx.h)
  */
AM_ErrorCode_t AM_NTSC_DMX_Sync(int dev_no)
{
	AM_VBI_Device_t *dev;
	AM_ErrorCode_t ret = AM_SUCCESS;

	ret = (dmx_get_openned_dev(dev_no, &dev));

	pthread_mutex_lock(&dev->lock);
	if (dev->thread != pthread_self())
	{
		while (dev->flags & DMX_FL_RUN_CB)
			pthread_cond_wait(&dev->cond, &dev->lock);
	}
	pthread_mutex_unlock(&dev->lock);

	return ret;
}

