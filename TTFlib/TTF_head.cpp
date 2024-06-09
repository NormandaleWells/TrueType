
#include <bit>

#include "TTF_head.h"

void TTF_head::fix_endianness()
{
	if constexpr (std::endian::native == std::endian::little)
	{
		major_version       = std::byteswap(major_version);
		minor_version       = std::byteswap(minor_version);
		font_revision       = std::byteswap(font_revision);
		checksum_adjustment = std::byteswap(checksum_adjustment);
		magic_number        = std::byteswap(magic_number);
		flags               = std::byteswap(flags);
		units_per_em        = std::byteswap(units_per_em);
		created             = std::byteswap(created);
		modified            = std::byteswap(modified);
		x_min               = std::byteswap(x_min);
		y_min               = std::byteswap(y_min);
		x_max               = std::byteswap(x_max);
		y_max               = std::byteswap(y_max);
		mac_style           = std::byteswap(mac_style);
		lowest_rec_PPEM     = std::byteswap(lowest_rec_PPEM);
		font_direction_hint = std::byteswap(font_direction_hint);
		index_to_loc_format = std::byteswap(index_to_loc_format);
		glyph_data_format   = std::byteswap(glyph_data_format);
	}
}
