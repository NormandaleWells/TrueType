#pragma once

// The 'head' table structure
//
// See https://learn.microsoft.com/en-us/typography/opentype/spec/head

#include "TTF_types.h"

#pragma pack(push)
#pragma pack(1)

struct TTF_head
{
	TTF_uint16 major_version;
	TTF_uint16 minor_version;
	TTF_Fixed font_revision;
	TTF_uint32 checksum_adjustment;
	TTF_uint32 magic_number;
	TTF_uint16 flags;
	TTF_uint16 units_per_em;
	TTF_LONGDATETIME created;
	TTF_LONGDATETIME modified;
	TTF_int16 x_min;
	TTF_int16 y_min;
	TTF_int16 x_max;
	TTF_int16 y_max;
	TTF_uint16 mac_style;
	TTF_uint16 lowest_rec_PPEM;
	TTF_int16 font_direction_hint;
	TTF_int16 index_to_loc_format;
	TTF_int16 glyph_data_format;
	void fix_endianness();
};

#pragma pack(pop)
