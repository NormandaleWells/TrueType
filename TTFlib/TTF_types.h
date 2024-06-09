#pragma once

#include <cinttypes>

// This header defines the basic TrueType data types listed in
//
//		https://learn.microsoft.com/en-us/typography/opentype/spec/otff
//
// Since a lot of these names (e.g. uint8) are commonly defined
// in lots of libraries, the names here are prefixed with TTF_.
// Thus, int8 because TTF_int8, UFWORD becomes TTF_UFWORD, etc.

// These types should be used only internally to the TrueTypeFontImpl
// class; they should not "leak out" to the rest of the world.

using TTF_uint8 = std::uint8_t;
using TTF_int8 = std::int8_t;
using TTF_uint16 = std::uint16_t;
using TTF_int16 = std::int16_t;
using TTF_uint24 = std::uint32_t;
using TTF_uint32 = std::uint32_t;
using TTF_int32 = std::int32_t;
using TTF_Fixed = std::int32_t;			// 16.16 fixed point number
using TTF_FWORD = std::int16_t;
using TTF_UFWORD = std::uint16_t;
using TTF_F2DOT14 = std::int16_t;		// 14.2 fixed point number
using TTF_LONGDATETIME = std::int64_t;	// seconds since 1904/01/01:00:00:00
using TTF_Tag = std::uint8_t[4];
using TTF_Offset8 = std::uint8_t;
using TTF_Offset16 = std::uint16_t;
using TTF_Offset24 = std::uint32_t;
using TTF_Offset32 = std::uint32_t;

const TTF_Tag Tag_head = { 'h', 'e', 'a', 'd' };
const TTF_Tag Tag_glyf = { 'g', 'l', 'y', 'f' };
