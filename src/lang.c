/*
 *  libzvbi - Teletext and Closed Caption character set
 *
 *  Copyright (C) 2000, 2001 Michael H. Schimek
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the
 *  Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301  USA.
 */

/* $Id: lang.c,v 1.15 2008/07/26 06:22:38 mschimek Exp $ */

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "lang.h"
#ifdef ANDROID
#include <android/log.h>
#define LOG_TAG    "ZVBI"
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#else
#define LOGI(...) printf(__VA_ARGS__)
#define LOGE(...) printf(__VA_ARGS__)
#endif

/*
 *  Teletext font descriptors
 *
 *  ETS 300 706 Table 32, 33, 34
 */
struct vbi_font_descr
vbi_font_descriptors[88] = {
	/* 0 - Western and Central Europe */
	{ LATIN_G0, LATIN_G2, ENGLISH,		"English" },
	{ LATIN_G0, LATIN_G2, GERMAN,		"Deutsch" },
	{ LATIN_G0, LATIN_G2, SWE_FIN_HUN,	"Svenska / Suomi / Magyar" },
	{ LATIN_G0, LATIN_G2, ITALIAN,		"Italiano" },
	{ LATIN_G0, LATIN_G2, FRENCH,		"Fran�ais" },
	{ LATIN_G0, LATIN_G2, PORTUG_SPANISH,	"Portugu�s / Espa�ol" },
	{ LATIN_G0, LATIN_G2, CZECH_SLOVAK,	"Cesky / Slovencina" },
	{ LATIN_G0, LATIN_G2, NO_SUBSET,	0 },

	/* 8 - Eastern Europe */
	{ LATIN_G0, LATIN_G2, POLISH,		"Polski" },
	{ LATIN_G0, LATIN_G2, GERMAN,		"Deutsch" },
	{ LATIN_G0, LATIN_G2, SWE_FIN_HUN,	"Svenska / Suomi / Magyar" },
	{ LATIN_G0, LATIN_G2, ITALIAN,		"Italiano" },
	{ LATIN_G0, LATIN_G2, FRENCH,		"Fran�ais" },
	{ LATIN_G0, LATIN_G2, NO_SUBSET,	0 },
	{ LATIN_G0, LATIN_G2, CZECH_SLOVAK,	"Cesky / Slovencina" },
	{ LATIN_G0, LATIN_G2, NO_SUBSET,	0 },

	/* 16 - Western Europe and Turkey */
	{ LATIN_G0, LATIN_G2, ENGLISH,		"English" },
	{ LATIN_G0, LATIN_G2, GERMAN,		"Deutsch" },
	{ LATIN_G0, LATIN_G2, SWE_FIN_HUN,	"Svenska / Suomi / Magyar" },
	{ LATIN_G0, LATIN_G2, ITALIAN,		"Italiano" },
	{ LATIN_G0, LATIN_G2, FRENCH,		"Fran�ais" },
	{ LATIN_G0, LATIN_G2, PORTUG_SPANISH,	"Portugu�s / Espa�ol" },
	{ LATIN_G0, LATIN_G2, TURKISH,		"T�rk�e" },
	{ LATIN_G0, LATIN_G2, ENGLISH,	0 },

	/* 24 - Central and Southeast Europe */
	{ LATIN_G0, LATIN_G2, NO_SUBSET,	0 },
	{ LATIN_G0, LATIN_G2, NO_SUBSET,	0 },
	{ LATIN_G0, LATIN_G2, NO_SUBSET,	0 },
	{ LATIN_G0, LATIN_G2, NO_SUBSET,	0 },
	{ LATIN_G0, LATIN_G2, NO_SUBSET,	0 },
	{ LATIN_G0, LATIN_G2, SERB_CRO_SLO,	"Srbski / Hrvatski / Slovenscina" },
	{ LATIN_G0, LATIN_G2, NO_SUBSET,	0 },
	{ LATIN_G0, LATIN_G2, RUMANIAN,		"Rom�na" },

	/* 32 - Cyrillic */
	{ CYRILLIC_1_G0, CYRILLIC_G2, NO_SUBSET, "Srpski / Hrvatski" }, //Serbian/Croatian
	{ LATIN_G0, LATIN_G2, GERMAN,		"Deutsch" },
	{ LATIN_G0, LATIN_G2, ESTONIAN,		"Eesti" },
	{ LATIN_G0, LATIN_G2, LETT_LITH,	"Lettish / Lietuviskai" },
	{ CYRILLIC_2_G0, CYRILLIC_G2, NO_SUBSET, "Russky / Balgarski " },
	{ CYRILLIC_3_G0, CYRILLIC_G2, NO_SUBSET, "Ukrayins'ka" },
	{ LATIN_G0, LATIN_G2, CZECH_SLOVAK,	"Cesky / Slovencina" },
	{ 0, 0, NO_SUBSET,			0 },

	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },

	/* 48 */
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ LATIN_G0, LATIN_G2, TURKISH,		"T�rk�e" },
	{ GREEK_G0, GREEK_G2, NO_SUBSET,	"Ellinika'" }, //Greek

	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },

	/* 64 - Arabic */
	{ LATIN_G0, ARABIC_G2, ENGLISH,		"Alarabia / English" },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ LATIN_G0, ARABIC_G2, FRENCH,		"Alarabia / Fran�ais" },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ ARABIC_G0, ARABIC_G2, NO_SUBSET,	"Alarabia" },

	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },

	/* 80 */
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ 0, 0, NO_SUBSET,			0 },
	{ HEBREW_G0, ARABIC_G2, NO_SUBSET,	"Ivrit" }, //Hebrew
	{ 0, 0, NO_SUBSET,			0 },
	{ ARABIC_G0, ARABIC_G2, NO_SUBSET,	"Alarabia" },

};

#if 0

/*
 *  These characters mimic a few common block mosaic, smooth mosaic
 *  or line drawing character patterns, eg. horizontal bars
 *
 *  Not currently used (anymore), maybe later.
 */
static const unsigned char
gfx_transcript[] = {
/* 2 */	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00,
/* 3 */	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x2B, 0x00, 0x00,
/* 2 */	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2D, 0x00, 0x00, 0x00,
/* 3 */	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x2B, 0x00, 0x00,
/* 6 */	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x00,
/* 7 */	0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
/* 6 */	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x00,
/* 7 */	0x5F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,
/* 2 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 3 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 4 */ 0x2B, 0x2B, 0x2B, 0x2B, 0x3C, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2B, 0x2A, 0x2A, 0x6F,
/* 5 */ 0x7C, 0x2D, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B, 0x3E, 0x3C, 0x00, 0x00, 0x00,
/* 6 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
/* 7 */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#endif

/*
 *  Teletext character set
 *
 *  (Similar to ISO 6937 -
 *   ftp://dkuug.dk/i18n/charmaps/ISO_6937)
 */

/*
 *  ETS 300 706 Table 36: Latin National Option Sub-sets
 *
 *  Latin G0 character code to Unicode mapping per national subset,
 *  unmodified codes (NO_SUBSET) in row zero.
 *
 *  [13][0] Turkish currency symbol not in Unicode, use private code U+E800
 */
static const unsigned short
national_subset[14][13] = {
  { 0x0023u, 0x0024u, 0x0040u, 0x005Bu, 0x005Cu, 0x005Du, 0x005Eu, 0x005Fu, 0x0060u, 0x007Bu, 0x007Cu, 0x007Du, 0x007Eu },
  { 0x0023u, 0x016Fu, 0x010Du, 0x0165u, 0x017Eu, 0x00FDu, 0x00EDu, 0x0159u, 0x00E9u, 0x00E1u, 0x011Bu, 0x00FAu, 0x0161u },
  { 0x00A3u, 0x0024u, 0x0040u, 0x2190u, 0x00BDu, 0x2192u, 0x2191u, 0x0023u, 0x2014u, 0x00BCu, 0x2016u, 0x00BEu, 0x00F7u },
  { 0x0023u, 0x00F5u, 0x0160u, 0x00C4u, 0x00D6u, 0x017Du, 0x00DCu, 0x00D5u, 0x0161u, 0x00E4u, 0x00F6u, 0x017Eu, 0x00FCu },
  { 0x00E9u, 0x00EFu, 0x00E0u, 0x00EBu, 0x00EAu, 0x00F9u, 0x00EEu, 0x0023u, 0x00E8u, 0x00E2u, 0x00F4u, 0x00FBu, 0x00E7u },
  { 0x0023u, 0x0024u, 0x00A7u, 0x00C4u, 0x00D6u, 0x00DCu, 0x005Eu, 0x005Fu, 0x00B0u, 0x00E4u, 0x00F6u, 0x00FCu, 0x00DFu },
  { 0x00A3u, 0x0024u, 0x00E9u, 0x00B0u, 0x00E7u, 0x2192u, 0x2191u, 0x0023u, 0x00F9u, 0x00E0u, 0x00F2u, 0x00E8u, 0x00ECu },
  { 0x0023u, 0x0024u, 0x0160u, 0x0117u, 0x0229u, 0x017Du, 0x010Du, 0x016Bu, 0x0161u, 0x0105u, 0x0173u, 0x017Eu, 0x012Fu },
  { 0x0023u, 0x0144u, 0x0105u, 0x01B5u, 0x015Au, 0x0141u, 0x0107u, 0x00F3u, 0x0119u, 0x017Cu, 0x015Bu, 0x0142u, 0x017Au },
  { 0x00E7u, 0x0024u, 0x00A1u, 0x00E1u, 0x00E9u, 0x00EDu, 0x00F3u, 0x00FAu, 0x00BFu, 0x00FCu, 0x00F1u, 0x00E8u, 0x00E0u },
  { 0x0023u, 0x00A4u, 0x0162u, 0x00C2u, 0x015Eu, 0x01CDu, 0x00CDu, 0x0131u, 0x0163u, 0x00E2u, 0x015Fu, 0X01CEu, 0x00EEu },
  { 0x0023u, 0x00CBu, 0x010Cu, 0x0106u, 0x017Du, 0x00D0u, 0x0160u, 0x00EBu, 0x010Du, 0x0107u, 0x017Eu, 0x00F0u, 0x0161u },
  { 0x0023u, 0x00A4u, 0x00C9u, 0x00C4u, 0x00D6u, 0x00C5u, 0x00DCu, 0x005Fu, 0x00E9u, 0x00E4u, 0x00F6u, 0x00E5u, 0x00FCu },
  { 0xE800u, 0x011Fu, 0x0130u, 0x015Eu, 0x00D6u, 0x00C7u, 0x00DCu, 0x011Eu, 0x0131u, 0x015Fu, 0x00F6u, 0x00E7u, 0x00FCu }
};

/*
 *  ETS 300 706 Table 37: Latin G2 Supplementary Set
 *
 *  0x49 seems to be dot below; not in Unicode (except combining), use U+002E.
 */
static const unsigned short
latin_g2[96] = {
  0x00A0u, 0x00A1u, 0x00A2u, 0x00A3u, 0x0024u, 0x00A5u, 0x0023u, 0x00A7u, 0x00A4u, 0x2018u, 0x201Cu, 0x00ABu, 0x2190u, 0x2191u, 0x2192u, 0x2193u,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00D7u, 0x00B5u, 0x00B6u, 0x00B7u, 0x00F7u, 0x2019u, 0x201Du, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0x00BFu,
  0x0020u, 0x02CBu, 0x02CAu, 0x02C6u, 0x02DCu, 0x02C9u, 0x02D8u, 0x02D9u, 0x00A8u, 0x002Eu, 0x02DAu, 0x02CFu, 0x02CDu, 0x02DDu, 0x02DBu, 0x02C7u,
  0x2014u, 0x00B9u, 0x00AEu, 0x00A9u, 0x2122u, 0x266Au, 0x20A0u, 0x2030u, 0x0251u, 0x0020u, 0x0020u, 0x0020u, 0x215Bu, 0x215Cu, 0x215Du, 0x215Eu,
  0x2126u, 0x00C6u, 0x00D0u, 0x00AAu, 0x0126u, 0x0020u, 0x0132u, 0x013Fu, 0x0141u, 0x00D8u, 0x0152u, 0x00BAu, 0x00DEu, 0x0166u, 0x014Au, 0x0149u,
  0x0138u, 0x00E6u, 0x0111u, 0x00F0u, 0x0127u, 0x0131u, 0x0133u, 0x0140u, 0x0142u, 0x00F8u, 0x0153u, 0x00DFu, 0x00FEu, 0x0167u, 0x014Bu, 0x25A0u
};

/*
 *  ETS 300 706 Table 38: Cyrillic G0 Primary Set - Option 1 - Serbian/Croatian
 */
static const unsigned short
cyrillic_1_g0[64] = {
  0x0427u, 0x0410u, 0x0411u, 0x0426u, 0x0414u, 0x0415u, 0x0424u, 0x0413u, 0x0425u, 0x0418u, 0x0408u, 0x041Au, 0x041Bu, 0x041Cu, 0x041Du, 0x041Eu,
  0x041Fu, 0x040Cu, 0x0420u, 0x0421u, 0x0422u, 0x0423u, 0x0412u, 0x0403u, 0x0409u, 0x040Au, 0x0417u, 0x040Bu, 0x0416u, 0x0402u, 0x0428u, 0x040Fu,
  0x0447u, 0x0430u, 0x0431u, 0x0446u, 0x0434u, 0x0435u, 0x0444u, 0x0433u, 0x0445u, 0x0438u, 0x0458u, 0x043Au, 0x043Bu, 0x043Cu, 0x043Du, 0x043Eu,
  0x043Fu, 0x045Cu, 0x0440u, 0x0441u, 0x0442u, 0x0443u, 0x0432u, 0x0453u, 0x0459u, 0x045Au, 0x0437u, 0x045Bu, 0x0436u, 0x0452u, 0x0448u, 0x25A0u
};

/*
 *  ETS 300 706 Table 39: Cyrillic G0 Primary Set - Option 2 - Russian/Bulgarian
 */
static const unsigned short
cyrillic_2_g0[64] = {
  0x042Eu, 0x0410u, 0x0411u, 0x0426u, 0x0414u, 0x0415u, 0x0424u, 0x0413u, 0x0425u, 0x0418u, 0x040Du, 0x041Au, 0x041Bu, 0x041Cu, 0x041Du, 0x041Eu,
  0x041Fu, 0x042Fu, 0x0420u, 0x0421u, 0x0422u, 0x0423u, 0x0416u, 0x0412u, 0x042Cu, 0x042Au, 0x0417u, 0x0428u, 0x042Du, 0x0429u, 0x0427u, 0x042Bu,
  0x044Eu, 0x0430u, 0x0431u, 0x0446u, 0x0434u, 0x0435u, 0x0444u, 0x0433u, 0x0445u, 0x0438u, 0x045Du, 0x043Au, 0x043Bu, 0x043Cu, 0x043Du, 0x043Eu,
  0x043Fu, 0x044Fu, 0x0440u, 0x0441u, 0x0442u, 0x0443u, 0x0436u, 0x0432u, 0x044Cu, 0x044Au, 0x0437u, 0x0448u, 0x044Du, 0x0449u, 0x0447u, 0x25A0u
};

/*
 *  ETS 300 706 Table 40: Cyrillic G0 Primary Set - Option 3 - Ukrainian
 */
static const unsigned short
cyrillic_3_g0[64] = {
  0x042Eu, 0x0410u, 0x0411u, 0x0426u, 0x0414u, 0x0415u, 0x0424u, 0x0413u, 0x0425u, 0x0418u, 0x040Du, 0x041Au, 0x041Bu, 0x041Cu, 0x041Du, 0x041Eu,
  0x041Fu, 0x042Fu, 0x0420u, 0x0421u, 0x0422u, 0x0423u, 0x0416u, 0x0412u, 0x042Cu, 0x0406u, 0x0417u, 0x0428u, 0x0404u, 0x0429u, 0x0427u, 0x0407u,
  0x044Eu, 0x0430u, 0x0431u, 0x0446u, 0x0434u, 0x0435u, 0x0444u, 0x0433u, 0x0445u, 0x0438u, 0x045Du, 0x043Au, 0x043Bu, 0x043Cu, 0x043Du, 0x043Eu,
  0x043Fu, 0x044Fu, 0x0440u, 0x0441u, 0x0442u, 0x0443u, 0x0436u, 0x0432u, 0x044Cu, 0x0456u, 0x0437u, 0x0448u, 0x0454u, 0x0449u, 0x0447u, 0x25A0u
};

/*
 *  ETS 300 706 Table 41: Cyrillic G2 Supplementary Set
 */
static const unsigned short
cyrillic_g2[96] = {
  0x00A0u, 0x00A1u, 0x00A2u, 0x00A3u, 0x0020u, 0x00A5u, 0x0023u, 0x00A7u, 0x0020u, 0x2018u, 0x201Cu, 0x00ABu, 0x2190u, 0x2191u, 0x2192u, 0x2193u,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x00D7u, 0x00B5u, 0x00B6u, 0x00B7u, 0x00F7u, 0x2019u, 0x201Du, 0x00BBu, 0x00BCu, 0x00BDu, 0x00BEu, 0x00BFu,
  0x0020u, 0x02CBu, 0x02CAu, 0x02C6u, 0x02DCu, 0x02C9u, 0x02D8u, 0x02D9u, 0x00A8u, 0x002Eu, 0x02DAu, 0x02CFu, 0x02CDu, 0x02DDu, 0x02DBu, 0x02C7u,
  0x2014u, 0x00B9u, 0x00AEu, 0x00A9u, 0x2122u, 0x266Au, 0x20A0u, 0x2030u, 0x0251u, 0x0141u, 0x0142u, 0x00DFu, 0x215Bu, 0x215Cu, 0x215Du, 0x215Eu,
  0x0044u, 0x0045u, 0x0046u, 0x0047u, 0x0049u, 0x004Au, 0x004Bu, 0x004Cu, 0x004Eu, 0x0051u, 0x0052u, 0x0053u, 0x0055u, 0x0056u, 0x0057u, 0x005Au,
  0x0064u, 0x0065u, 0x0066u, 0x0067u, 0x0069u, 0x006Au, 0x006Bu, 0x006Cu, 0x006Eu, 0x0071u, 0x0072u, 0x0073u, 0x0075u, 0x0076u, 0x0077u, 0x007Au
};

/*
 *  ETS 300 706 Table 42: Greek G0 Primary Set
 */
static const unsigned short
greek_g0[64] = {
  0x0390u, 0x0391u, 0x0392u, 0x0393u, 0x0394u, 0x0395u, 0x0396u, 0x0397u, 0x0398u, 0x0399u, 0x039Au, 0x039Bu, 0x039Cu, 0x039Du, 0x039Eu, 0x039Fu,
  0x03A0u, 0x03A1u, 0x0374u, 0x03A3u, 0x03A4u, 0x03A5u, 0x03A6u, 0x03A7u, 0x03A8u, 0x03A9u, 0x03AAu, 0x03ABu, 0x03ACu, 0x03ADu, 0x03AEu, 0x03AFu,
  0x03B0u, 0x03B1u, 0x03B2u, 0x03B3u, 0x03B4u, 0x03B5u, 0x03B6u, 0x03B7u, 0x03B8u, 0x03B9u, 0x03BAu, 0x03BBu, 0x03BCu, 0x03BDu, 0x03BEu, 0x03BFu,
  0x03C0u, 0x03C1u, 0x03C2u, 0x03C3u, 0x03C4u, 0x03C5u, 0x03C6u, 0x03C7u, 0x03C8u, 0x03C9u, 0x03CAu, 0x03CBu, 0x03CCu, 0x03CDu, 0x03CEu, 0x25A0u
};

/*
 *  ETS 300 706 Table 43: Greek G2 Supplementary Set
 */
static const unsigned short
greek_g2[96] = {
  0x00A0u, 0x0061u, 0x0062u, 0x00A3u, 0x0065u, 0x0068u, 0x0069u, 0x00A7u, 0x003Au, 0x2018u, 0x201Cu, 0x006Bu, 0x2190u, 0x2191u, 0x2192u, 0x2193u,
  0x00B0u, 0x00B1u, 0x00B2u, 0x00B3u, 0x0078u, 0x006Du, 0x006Eu, 0x0070u, 0x00F7u, 0x2019u, 0x201Du, 0x0074u, 0x00BCu, 0x00BDu, 0x00BEu, 0x0078u,
  0x0020u, 0x02CBu, 0x02CAu, 0x02C6u, 0x02DCu, 0x02C9u, 0x02D8u, 0x02D9u, 0x00A8u, 0x002Eu, 0x02DAu, 0x02CFu, 0x02CDu, 0x02DDu, 0x02DBu, 0x02C7u,
  0x003Fu, 0x00B9u, 0x00AEu, 0x00A9u, 0x2122u, 0x266Au, 0x20A0u, 0x2030u, 0x0251u, 0x038Au, 0x038Eu, 0x038Fu, 0x215Bu, 0x215Cu, 0x215Du, 0x215Eu,
  0x0043u, 0x0044u, 0x0046u, 0x0047u, 0x004Au, 0x004Cu, 0x0051u, 0x0052u, 0x0053u, 0x0055u, 0x0056u, 0x0057u, 0x0059u, 0x005Au, 0x0386u, 0x0389u,
  0x0063u, 0x0064u, 0x0066u, 0x0067u, 0x006Au, 0x006Cu, 0x0071u, 0x0072u, 0x0073u, 0x0075u, 0x0076u, 0x0077u, 0x0079u, 0x007Au, 0x0388u, 0x25A0u
};

/*
 *  ETS 300 706 Table 44: Arabic G0 Primary Set
 *
 *  XXX 0X0000 is what?
 *  Until these tables are finished use private codes U+E6xx.
 */
static const unsigned short
arabic_g0[96] = {
/*
  0x0020, 0x0021, 0x0022, 0x00A3, 0x0024, 0x0025, 0x0000, 0x0000, 0x0029, 0x0028, 0x002A, 0x002B, 0x060C, 0x002D, 0x002E, 0x002F,
  0x0030, 0x0031, 0x0032, 0x0033, 0x0034, 0x0035, 0x0036, 0x0037, 0x0038, 0x0039, 0x003A, 0x061B, 0x003E, 0x003D, 0x003C, 0x061F,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0630, 0x0631, 0x0632, 0x0633, 0x0634, 0x0635, 0x0636, 0x0637, 0x0638, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0023,
  0x0640, 0x0641, 0x0642, 0x0643, 0x0644, 0x0645, 0x0646, 0x0647, 0x0648, 0x0649, 0x064A, 0x062B, 0x062D, 0x062C, 0x062E, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x25A0
*/
  0x0020u, 0x0021u, 0x0022u, 0x00A3u, 0x0024u, 0x0025u, 0xE606u, 0xE607u, 0x0029u, 0x0028u, 0x002Au, 0x002Bu, 0x060Cu, 0x002Du, 0x002Eu, 0x002Fu,
  0x0030u, 0x0031u, 0x0032u, 0x0033u, 0x0034u, 0x0035u, 0x0036u, 0x0037u, 0x0038u, 0x0039u, 0x003Au, 0x061Bu, 0x003Eu, 0x003Du, 0x003Cu, 0x061Fu,
  0xE620u, 0xE621u, 0xE622u, 0xE623u, 0xE624u, 0xE625u, 0xE626u, 0xE627u, 0xE628u, 0xE629u, 0xE62Au, 0xE62Bu, 0xE62Cu, 0xE62Du, 0xE62Eu, 0xE62Fu,
  0xE630u, 0xE631u, 0xE632u, 0xE633u, 0xE634u, 0xE635u, 0xE636u, 0xE637u, 0xE638u, 0xE639u, 0xE63Au, 0xE63Bu, 0xE63Cu, 0xE63Du, 0xE63Eu, 0x0023u,
  0xE640u, 0xE641u, 0xE642u, 0xE643u, 0xE644u, 0xE645u, 0xE646u, 0xE647u, 0xE648u, 0xE649u, 0xE64Au, 0xE64Bu, 0xE64Cu, 0xE64Du, 0xE64Eu, 0xE64Fu,
  0xE650u, 0xE651u, 0xE652u, 0xE653u, 0xE654u, 0xE655u, 0xE656u, 0xE657u, 0xE658u, 0xE659u, 0xE65Au, 0xE65Bu, 0xE65Cu, 0xE65Du, 0xE65Eu, 0x25A0u
};

/*
 *  ETS 300 706 Table 45: Arabic G2 Supplementary Set
 *
 *  XXX 0X0000 is what?
 *  Until these tables are finished use private codes U+E7xx.
 */
static const unsigned short
arabic_g2[96] = {
/*
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0660, 0x0661, 0x0662, 0x0663, 0x0664, 0x0665, 0x0666, 0x0667, 0x0668, 0x0669, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
*/
  0xE660u, 0xE661u, 0xE662u, 0xE663u, 0xE664u, 0xE665u, 0xE666u, 0xE667u, 0xE668u, 0xE669u, 0xE66Au, 0xE66Bu, 0xE66Cu, 0xE66Du, 0xE66Eu, 0xE66Fu,
  0xE670u, 0xE671u, 0xE672u, 0xE673u, 0xE674u, 0xE675u, 0xE676u, 0xE677u, 0xE678u, 0xE679u, 0xE67Au, 0xE67Bu, 0xE67Cu, 0xE67Du, 0xE67Eu, 0xE67Fu,
  0x00E0u, 0x0041u, 0x0042u, 0x0043u, 0x0044u, 0x0045u, 0x0046u, 0x0047u, 0x0048u, 0x0049u, 0x004Au, 0x004Bu, 0x004Cu, 0x004Du, 0x004Eu, 0x004Fu,
  0x0050u, 0x0051u, 0x0052u, 0x0053u, 0x0054u, 0x0055u, 0x0056u, 0x0057u, 0x0058u, 0x0059u, 0x005Au, 0x00EBu, 0x00EAu, 0x00F9u, 0x00EEu, 0xE75Fu,
  0x00E9u, 0x0061u, 0x0062u, 0x0063u, 0x0064u, 0x0065u, 0x0066u, 0x0067u, 0x0068u, 0x0069u, 0x006Au, 0x006Bu, 0x006Cu, 0x006Du, 0x006Eu, 0x006Fu,
  0x0070u, 0x0071u, 0x0072u, 0x0073u, 0x0074u, 0x0075u, 0x0076u, 0x0077u, 0x0078u, 0x0079u, 0x007Au, 0x00E2u, 0x00F4u, 0x00FBu, 0x00E7u, 0x0020u
};

/*
 *  ETS 300 706 Table 46: Hebrew G0 Primary Set
 */
static const unsigned short
hebrew_g0[37] = {
  0x2190u, 0x00BDu, 0x2192u, 0x2191u, 0x0023u,
  0x05D0u, 0x05D1u, 0x05D2u, 0x05D3u, 0x05D4u, 0x05D5u, 0x05D6u, 0x05D7u, 0x05D8u, 0x05D9u, 0x05DAu, 0x05DBu, 0x05DCu, 0x05DDu, 0x05DEu, 0x05DFu,
  0x05E0u, 0x05E1u, 0x05E2u, 0x05E3u, 0x05E4u, 0x05E5u, 0x05E6u, 0x05E7u, 0x05E8u, 0x05E9u, 0x05EAu, 0x20AAu, 0x2016u, 0x00BEu, 0x00F7u, 0x25A0u
};

/**
 * @internal
 * @param s Teletext character set as listed in ETS 300 706 section 15.
 * @param n National character subset as listed in section 15, only
 *     applicable to character set LATIN_G0, ignored otherwise.
 * @param c Character code in range 0x20 ... 0x7F.
 *
 * Translate Teletext character code to Unicode.
 *
 * Exceptions:
 * ETS 300 706 Table 36 Latin National Subset Turkish character
 * 0x23 Turkish currency symbol is not representable in Unicode,
 * translated to private code U+E800. Was unable to identify all
 * Arabic glyphs in Table 44 and 45 Arabic G0 and G2, these are
 * mapped to private code U+E620 ... U+E67F and U+E720 ... U+E77F
 * respectively. Table 47 G1 Block Mosaic is not representable
 * in Unicode, translated to private code U+EE00 ... U+EE7F.
 * (contiguous form has bit 5 set, separate form cleared).
 * Table 48 G3 Smooth Mosaics and Line Drawing Set is not
 * representable in Unicode, translated to private code U+EF20
 * ... U+EF7F.
 *
 * Note that some Teletext character sets contain complementary
 * Latin characters. For example the Greek capital letters Alpha
 * and Beta are reused as Latin capital letter A and B, while a
 * separate code exists for Latin capital letter C. This function
 * is unable to distinguish between uses, so it will always translate
 * Greek A and B to Alpha and Beta, C to Latin C.
 *
 * Private codes U+F000 ... U+F7FF are reserved for DRCS.
 *
 * @return
 * Unicode value.
 */
unsigned int
vbi_teletext_unicode(vbi_character_set s, vbi_national_subset n, unsigned int c)
{
	int i;

	assert(c >= 0x20 && c <= 0x7F);
	LOGE("vbi_character_set %d vbi_national_subset %d unicode 0x%x", s, n, c);
	switch (s) {
	case LATIN_G0:
		/* shortcut */
		if (0xF8000019UL & (1 << (c & 31))) {
			if (n > 0) {
				assert(n < 14);

				for (i = 0; i < 13; i++)
					if (c == national_subset[0][i])
						return national_subset[n][i];
			}

			if (c == 0x24)
				return 0x00A4u;
			else if (c == 0x7C)
				return 0x00A6u;
			else if (c == 0x7F)
				return 0x25A0u;
		}

		return c;

	case LATIN_G2:
		return latin_g2[c - 0x20];

	case CYRILLIC_1_G0:
		if (c < 0x40)
			return c;
		else
			return cyrillic_1_g0[c - 0x40];

	case CYRILLIC_2_G0:
		if (c == 0x26)
			return 0x044Bu;
		else if (c < 0x40)
			return c;
		else
			return cyrillic_2_g0[c - 0x40];

	case CYRILLIC_3_G0:
		if (c == 0x26)
			return 0x00EFu;
		else if (c < 0x40)
			return c;
		else
			return cyrillic_3_g0[c - 0x40];

	case CYRILLIC_G2:
		return cyrillic_g2[c - 0x20];

	case GREEK_G0:
		if (c == 0x3C)
			return 0x00ABu;
		else if (c == 0x3E)
			return 0x00BBu;
		else if (c < 0x40)
			return c;
		else
			return greek_g0[c - 0x40];

	case GREEK_G2:
		return greek_g2[c - 0x20];

	case ARABIC_G0:
		return arabic_g0[c - 0x20];

	case ARABIC_G2:
		return arabic_g2[c - 0x20];

	case HEBREW_G0:
		if (c < 0x5B)
			return c;
		else
			return hebrew_g0[c - 0x5B];

	case BLOCK_MOSAIC_G1:
		/* 0x20 ... 0x3F -> 0xEE00 ... 0xEE1F separated */
		/*                  0xEE20 ... 0xEE3F contiguous */
		/* 0x60 ... 0x7F -> 0xEE40 ... 0xEE5F separated */
		/*                  0xEE60 ... 0xEE7F contiguous */
		assert(c < 0x40 || c >= 0x60);
		return 0xEE00u + c;

	case SMOOTH_MOSAIC_G3:
		return 0xEF00u + c;

	default:
		fprintf(stderr, "%s: unknown char set %d\n",
			__FUNCTION__, s);
		exit(EXIT_FAILURE);
	}
}

/*
 *  Unicode 0x00C0u ... 0x017Fu to
 *  Teletext accent ((Latin G2 0x40 ... 0x4F) - 0x40) << 12 + Latin G0
 */
static const unsigned short
composed[12 * 16] = {
  0x1041, 0x2041, 0x3041, 0x4041, 0x8041, 0xA041, 0x0000, 0xB043, 0x1045, 0x2045, 0x3045, 0x8045, 0x1049, 0x2049, 0x3049, 0x8049,
  0x0000, 0x404E, 0x104F, 0x204F, 0x304F, 0x404F, 0x804F, 0x0000, 0x0000, 0x1055, 0x2055, 0x3055, 0x8055, 0x2059, 0x0000, 0x0000,
  0x1061, 0x2061, 0x3061, 0x4061, 0x8061, 0xA061, 0x0000, 0xB063, 0x1065, 0x2065, 0x3065, 0x8065, 0x1069, 0x2069, 0x3069, 0x8069,
  0x0000, 0x406E, 0x106F, 0x206F, 0x306F, 0x406F, 0x806F, 0x0000, 0x00F9, 0x1075, 0x2075, 0x3075, 0x8075, 0x2079, 0x0000, 0x8079,
  0x5041, 0x5061, 0x6041, 0x6061, 0xE041, 0xE061, 0x2043, 0x2063, 0x3043, 0x3063, 0x7043, 0x7063, 0xF043, 0xF063, 0xF044, 0xF064,
  0x0000, 0x0000, 0x5045, 0x5065, 0x6045, 0x6065, 0x7045, 0x7065, 0xE045, 0xE065, 0xF045, 0xF065, 0x3047, 0x3067, 0x6047, 0x6067,
  0x7047, 0x7067, 0x0000, 0x0000, 0x3048, 0x3068, 0x0000, 0x0000, 0x4049, 0x4069, 0x5049, 0x5069, 0x6049, 0x6069, 0xE049, 0xE069,
  0x7049, 0x0000, 0x0000, 0x0000, 0x304A, 0x306A, 0x0000, 0x0000, 0x0000, 0x204C, 0x2049, 0x0000, 0x0000, 0xF04C, 0xF06C, 0x0000,
  0x0000, 0x0000, 0x0000, 0x204E, 0x206E, 0x0000, 0x0000, 0xF04E, 0xF06E, 0x0000, 0x0000, 0x0000, 0x504F, 0x506F, 0x604F, 0x606F,
  0xD04F, 0xD06F, 0x0000, 0x0000, 0x2052, 0x2072, 0x0000, 0x0000, 0xF052, 0xF072, 0x2053, 0x2073, 0x3053, 0x3073, 0xB053, 0xB073,
  0xF053, 0xF073, 0xB054, 0xB074, 0xF053, 0xF073, 0x0000, 0x0000, 0x4055, 0x4075, 0x5055, 0x5075, 0x6055, 0x6075, 0xA055, 0xA075,
  0xD055, 0xD075, 0xE055, 0xE075, 0x3057, 0x3077, 0x3059, 0x3079, 0x8059, 0x205A, 0x207A, 0x705A, 0x707A, 0xF05A, 0xF07A, 0x0000
};

/**
 * @internal
 * @param a Accent 0 ... 15.
 * @param c Character code in range 0x20 ... 0x7F.
 *
 * Translate Teletext Latin G1 character 0x20 ... 0x7F combined
 * with accent code from Latin G2 0x40 ... 0x4F to Unicode. Not all
 * combinations are representable in Unicode.
 *
 * @return
 * Unicode value or 0.
 */
unsigned int
vbi_teletext_composed_unicode(unsigned int a, unsigned int c)
{
	unsigned int i;

	assert(a <= 15);
	assert(c >= 0x20 && c <= 0x7F);

	if (a == 0)
		return vbi_teletext_unicode(LATIN_G0, NO_SUBSET, c);

	c += a << 12;
	//Patch: l'--> 7b -->0x2049
	if (c == 0x206c)
		c = 0xF06C;

	for (i = 0; i < sizeof(composed) / sizeof(composed[0]); i++)
		if (composed[i] == c)
			return 0x00C0u + i;
	return 0;
}

static inline int
is_blank(vbi_char c)
{
	/* flash/conceal: undecided; underline: nope. */
	if (c.flash || c.conceal || c.underline)
		return 0;
	else
		return c.unicode <= 0x0020
			|| c.unicode == 0x00A0
			|| c.unicode == 0xEE00  /* blank, separated */
			|| c.unicode == 0xEE20; /* blank, contiguous */
}

static inline int
is_full(vbi_char c)
{
	/* flash/conceal: undecided. */
	if (c.flash || c.conceal)
		return 0;
	else
		return c.unicode == 0xEE7F /* G1 block, contiguous form */
			|| c.unicode == 0xFF3F; /* G3 block */
}

/**
 * @internal
 * @param pg Formatted vbi_page to be optimized.
 * @param column First column, 0 ... pg->columns - 1.
 * @param row First row, 0 ... pg->rows - 1.
 * @param width Number of columns to optimize, 1 ... pg->columns.
 * @param height Number of rows to optimize, 1 ... pg->rows.
 *
 * Experimental.
 */
void
vbi_optimize_page(vbi_page *pg, int column, int row, int width, int height)
{
	vbi_char c, l, *cp;
	int column0, row0;
	int column1, row1;

	column0 = column;
	row0 = row;
	column1 = column + width;
	row1 = row + height;

	l = pg->text[pg->columns * row + column];

	for (row = row0; row < row1; row++)
		for (column = column0; column < column1; column++) {
			cp = pg->text + pg->columns * row + column;
			c = *cp;

			if (is_blank(c)) {
				c.bold = l.bold;
				c.italic = l.italic;
				c.foreground = l.foreground;
			} else if (is_full(c)) {
				c.bold = l.bold;
				c.italic = l.italic;
				c.background = l.background;
			}

			*cp = l = c;
		}

	for (row = row1 - 1; row >= row0; row--)
		for (column = column1 - 1; column >= column0; column--) {
			cp = pg->text + pg->columns * row + column;
			c = *cp;

			if (is_blank(c)) {
				c.bold = l.bold;
				c.italic = l.italic;
				c.foreground = l.foreground;
			} else if (is_full(c)) {
				c.bold = l.bold;
				c.italic = l.italic;
				c.background = l.background;
			}

			*cp = l = c;
		}
}

/*
	Closed Caption character set
*/

/* Closed Caption Basic Character Set.
   47 CFR Section 15.119 (g) */
static const uint16_t
caption [96][2] = {
	{ 0x0020, 0x0020 },
	{ 0x0021, 0x0021 },
	{ 0x0022, 0x0022 },
	{ 0x0023, 0x0023 },
	{ 0x0024, 0x0024 },
	{ 0x0025, 0x0025 },
	{ 0x0026, 0x0026 },
	{ 0x0027, 0x0027 },
	{ 0x0028, 0x0028 },
	{ 0x0029, 0x0029 },
	{ 0x00E1, 0x00C1 }, /* 0x2A a with acute accent */
	{ 0x002B, 0x002B },
	{ 0x002C, 0x002C },
	{ 0x002D, 0x002D },
	{ 0x002E, 0x002E },
	{ 0x002F, 0x002F },
	{ 0x0030, 0x0030 },
	{ 0x0031, 0x0031 },
	{ 0x0032, 0x0032 },
	{ 0x0033, 0x0033 },
	{ 0x0034, 0x0034 },
	{ 0x0035, 0x0035 },
	{ 0x0036, 0x0036 },
	{ 0x0037, 0x0037 },
	{ 0x0038, 0x0038 },
	{ 0x0039, 0x0039 },
	{ 0x003A, 0x003A },
	{ 0x003B, 0x003B },
	{ 0x003C, 0x003C },
	{ 0x003D, 0x003D },
	{ 0x003E, 0x003E },
	{ 0x003F, 0x003F },
	{ 0x0040, 0x0040 },
	{ 0x0041, 0x0041 },
	{ 0x0042, 0x0042 },
	{ 0x0043, 0x0043 },
	{ 0x0044, 0x0044 },
	{ 0x0045, 0x0045 },
	{ 0x0046, 0x0046 },
	{ 0x0047, 0x0047 },
	{ 0x0048, 0x0048 },
	{ 0x0049, 0x0049 },
	{ 0x004A, 0x004A },
	{ 0x004B, 0x004B },
	{ 0x004C, 0x004C },
	{ 0x004D, 0x004D },
	{ 0x004E, 0x004E },
	{ 0x004F, 0x004F },
	{ 0x0050, 0x0050 },
	{ 0x0051, 0x0051 },
	{ 0x0052, 0x0052 },
	{ 0x0053, 0x0053 },
	{ 0x0054, 0x0054 },
	{ 0x0055, 0x0055 },
	{ 0x0056, 0x0056 },
	{ 0x0057, 0x0057 },
	{ 0x0058, 0x0058 },
	{ 0x0059, 0x0059 },
	{ 0x005A, 0x005A },
	{ 0x005B, 0x005B },
	{ 0x00E9, 0x00C9 }, /* 0x5C e with acute accent */
	{ 0x005D, 0x005D },
	{ 0x00ED, 0x00CD }, /* 0x5E i with acute accent */
	{ 0x00F3, 0x00D3 }, /* 0x5F o with acute accent */
	{ 0x00FA, 0x00DA }, /* 0x60 u with acute accent */
	{ 0x0061, 0x0041 },
	{ 0x0062, 0x0042 },
	{ 0x0063, 0x0043 },
	{ 0x0064, 0x0044 },
	{ 0x0065, 0x0045 },
	{ 0x0066, 0x0046 },
	{ 0x0067, 0x0047 },
	{ 0x0068, 0x0048 },
	{ 0x0069, 0x0049 },
	{ 0x006A, 0x004A },
	{ 0x006B, 0x004B },
	{ 0x006C, 0x004C },
	{ 0x006D, 0x004D },
	{ 0x006E, 0x004E },
	{ 0x006F, 0x004F },
	{ 0x0070, 0x0050 },
	{ 0x0071, 0x0051 },
	{ 0x0072, 0x0052 },
	{ 0x0073, 0x0053 },
	{ 0x0074, 0x0054 },
	{ 0x0075, 0x0055 },
	{ 0x0076, 0x0056 },
	{ 0x0077, 0x0057 },
	{ 0x0078, 0x0058 },
	{ 0x0079, 0x0059 },
	{ 0x007A, 0x005A },
	{ 0x00E7, 0x00C7 }, /* 0x7B c with cedilla */
	{ 0x00F7, 0x00F7 }, /* 0x7C Division sign */
	{ 0x00D1, 0x00D1 }, /* 0x7D N with tilde */
	{ 0x00F1, 0x00D1 }, /* 0x7E n with tilde */
	{ 0x25A0, 0x25A0 }  /* 0x7F Black square */
};

/* Closed Caption Special Characters.
   47 CFR Section 15.119 (g) */
static const uint16_t
caption_special [16][2] = {
	{ 0x00AE, 0x00AE }, /* 0x1130 Registered symbol */
	{ 0x00B0, 0x00B0 }, /* 0x1131 Degree sign */
	{ 0x00BD, 0x00BD }, /* 0x1132 1/2 */
	{ 0x00BF, 0x00BF }, /* 0x1133 Inverse question mark */
	{ 0x2122, 0x2122 }, /* 0x1134 Trademark symbol */
	{ 0x00A2, 0x00A2 }, /* 0x1135 Cents sign */
	{ 0x00A3, 0x00A3 }, /* 0x1136 Pounds sign */
	{ 0x266A, 0x266A }, /* 0x1137 Music note */
	{ 0x00E0, 0x00C0 }, /* 0x1138 a with grave accent */
	{ 0x0020, 0x0020 }, /* 0x1139 Transparent space */
	{ 0x00E8, 0x00C8 }, /* 0x113A e with grave accent */
	{ 0x00E2, 0x00C2 }, /* 0x113B a with circumflex */
	{ 0x00EA, 0x00CA }, /* 0x113C e with circumflex */
	{ 0x00EE, 0x00CE }, /* 0x113D i with circumflex */
	{ 0x00F4, 0x00D4 }, /* 0x113E o with circumflex */
	{ 0x00FB, 0x00DB }  /* 0x113F u with circumflex */
};

/* Closed Caption Extended Character Set.
   EIA 608-B Section 6.4.2 */
static const uint16_t
caption_extended2 [32][2] = {
	{ 0x00C1, 0x00C1 }, /* 0x1220 A with acute accent */
	{ 0x00C9, 0x00C9 }, /* 0x1221 E with acute accent */
	{ 0x00D3, 0x00D3 }, /* 0x1222 O with acute accent */
	{ 0x00DA, 0x00DA }, /* 0x1223 U with acute accent */
	{ 0x00DC, 0x00DC }, /* 0x1224 U with diaeresis */
	{ 0x00FC, 0x00DC }, /* 0x1225 u with diaeresis */
	{ 0x2018, 0x2018 }, /* 0x1226 Opening single quote */
	{ 0x00A1, 0x00A1 }, /* 0x1227 Inverted exclamation mark */
	{ 0x002A, 0x002A }, /* 0x1228 Asterisk */
	{ 0x0027, 0x0027 }, /* 0x1229 Plain single quote */
	{ 0x2500, 0x2500 }, /* 0x122A Em dash (for box drawing) */
	{ 0x00A9, 0x00A9 }, /* 0x122B Copyright */
	{ 0x2120, 0x2120 }, /* 0x122C Service mark */
	{ 0x2022, 0x2022 }, /* 0x122D Round bullet */
	{ 0x201C, 0x201C }, /* 0x122E Opening double quotes */
	{ 0x201D, 0x201D }, /* 0x122F Closing double quotes */
	{ 0x00C0, 0x00C0 }, /* 0x1230 A with grave accent */
	{ 0x00C2, 0x00C2 }, /* 0x1231 A with circumflex accent */
	{ 0x00C7, 0x00C7 }, /* 0x1232 C with cedilla */
	{ 0x00C8, 0x00C8 }, /* 0x1233 E with grave accent */
	{ 0x00CA, 0x00CA }, /* 0x1234 E with circumflex accent */
	{ 0x00CB, 0x00CB }, /* 0x1235 E with diaeresis */
	{ 0x00EB, 0x00CB }, /* 0x1236 e with diaeresis */
	{ 0x00CE, 0x00CE }, /* 0x1237 I with circumflex */
	{ 0x00CF, 0x00CF }, /* 0x1238 I with diaeresis */
	{ 0x00EF, 0x00CF }, /* 0x1239 i with diaeresis */
	{ 0x00D4, 0x00D4 }, /* 0x123A O with circumflex */
	{ 0x00D9, 0x00D9 }, /* 0x123B U with grave accent */
	{ 0x00F9, 0x00D9 }, /* 0x123C u with grave accent */
	{ 0x00DB, 0x00DB }, /* 0x123D U with circumflex accent */
	{ 0x00AB, 0x00AB }, /* 0x123E Opening guillemets */
	{ 0x00BB, 0x00BB }  /* 0x123F Closing guillemets */
};

/* Closed Caption Extended Character Set.
   EIA 608-B Section 6.4.2 */
static const uint16_t
caption_extended3 [32][2] = {
	{ 0x00C3, 0x00C3 }, /* 0x1320 A with tilde */
	{ 0x00E3, 0x00C3 }, /* 0x1321 a with tilde */
	{ 0x00CD, 0x00CD }, /* 0x1322 I with acute accent */
	{ 0x00CC, 0x00CC }, /* 0x1323 I with grave accent */
	{ 0x00EC, 0x00CC }, /* 0x1324 i with grave accent */
	{ 0x00D2, 0x00D2 }, /* 0x1325 O with grave accent */
	{ 0x00F2, 0x00D2 }, /* 0x1326 o with grave accent */
	{ 0x00D5, 0x00D5 }, /* 0x1327 O with tilde */
	{ 0x00F5, 0x00D5 }, /* 0x1328 o with tilde */
	{ 0x007B, 0x007B }, /* 0x1329 Opening curly brace */
	{ 0x007D, 0x007D }, /* 0x132A Closing curly brace */
	{ 0x005C, 0x005C }, /* 0x132B Backslash */
	{ 0x005E, 0x005E }, /* 0x132C Caret */
	{ 0x005F, 0x005F }, /* 0x132D Underscore */
	{ 0x007C, 0x007C }, /* 0x132E Vertical bar */
	{ 0x007E, 0x007E }, /* 0x132F Tilde */
	{ 0x00C4, 0x00C4 }, /* 0x1330 A with diaeresis */
	{ 0x00E4, 0x00C4 }, /* 0x1331 a with diaeresis */
	{ 0x00D6, 0x00D6 }, /* 0x1332 O with diaeresis */
	{ 0x00F6, 0x00D6 }, /* 0x1333 o with diaeresis */
	{ 0x00DF, 0x00DF }, /* 0x1334 Sharp s */
	{ 0x00A5, 0x00A5 }, /* 0x1335 Yen sign */
	{ 0x00A4, 0x00A4 }, /* 0x1336 Currency sign */
	{ 0x2502, 0x2502 }, /* 0x1337 Vertical bar (for box drawing) */
	{ 0x00C5, 0x00C5 }, /* 0x1338 A with ring above */
	{ 0x00E5, 0x00C5 }, /* 0x1339 a with ring above */
	{ 0x00D8, 0x00D8 }, /* 0x133A O with slash */
	{ 0x00F8, 0x00D8 }, /* 0x133B o with slash */
	{ 0x250C, 0x250C }, /* 0x133C Upper left corner */
	{ 0x2510, 0x2510 }, /* 0x133D Upper right corner */
	{ 0x2514, 0x2514 }, /* 0x133E Lower left corner */
	{ 0x2518, 0x2518 }  /* 0x133F Lower right corner */
};

/**
 * @ingroup Conv
 * @param c Character code in range 0x20 ... 0x7F,
 *   0x1130 ... 0x113F, 0x1930 ... 0x193F, 0x1220 ... 0x123F,
 *   0x1A20 ... 0x1A3F, 0x1320 ... 0x133F, 0x1B20 ... 0x1B3F.
 * @param to_upper Convert the character to upper case. (Often
 *   programs are captioned in all upper case, but except for
 *   one character the basic and special CC character sets contain
 *   only lower case accented characters.)
 *
 * Converts a Closed Caption character code to Unicode. Codes
 * in range 0x1130 to 0x1B3F are "special characters" and "extended
 * characters" (e.g. caption command 11 37).
 *
 * @see vbi_strndup_iconv_caption()
 *
 * @return
 * Unicode value or 0 if @a c is outside the valid ranges.
 *
 * @since 0.2.23
 */
unsigned int
vbi_caption_unicode		(unsigned int		c,
				 vbi_bool		to_upper)
{
	to_upper = !!to_upper;

	/* Note the comparisons are sorted for shortest path. */
	if (likely (c < 0x80)) {
		if (likely (c >= 0x20)) {
			return caption[c - 0x20][to_upper];
		}
	} else {
		c &= ~0x0800; /* ignore channel bit */

		if (c < 0x1240) {
			if (c < 0x1140 && c >= 0x1130) {
				/* 001 c001  011 xxxx */
				return caption_special[c - 0x1130][to_upper];
			} else if (c >= 0x1220) {
				/* 001 c010  01x xxxx */
				return caption_extended2[c - 0x1220][to_upper];
			}
		} else if (c < 0x1340 && c >= 0x1320) {
			/* 001 c011  01x xxxx */
			return caption_extended3[c - 0x1320][to_upper];
		}
	}

	return 0;
}

/*
Local variables:
c-set-style: K&R
c-basic-offset: 8
End:
*/
