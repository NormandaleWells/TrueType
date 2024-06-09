#pragma once

// The TTF table directory.
//
// See https://learn.microsoft.com/en-us/typography/opentype/spec/otff

#include <bit>
#include <memory>

#include "TTF_types.h"

#pragma pack(push)
#pragma pack(1)

struct TTF_table_record
{
	TTF_Tag table_tag;
	TTF_uint32 checksum;
	TTF_Offset32 offset;
	TTF_uint32 length;
	void fix_endianness();
};

struct TTF_table_directory
{
	TTF_uint32 sfnt_version;
	TTF_uint16 num_tables;
	TTF_uint16 search_range;
	TTF_uint16 entry_selector;
	TTF_uint16 range_shift;
	void fix_endianness();
};

#pragma pack(pop)
