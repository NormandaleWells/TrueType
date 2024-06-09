#include "TTF_table_directory.h"

void TTF_table_directory::fix_endianness()
{
	if constexpr (std::endian::native == std::endian::little)
	{
		sfnt_version   = std::byteswap(sfnt_version);
		num_tables     = std::byteswap(num_tables);
		search_range   = std::byteswap(search_range);
		entry_selector = std::byteswap(entry_selector);
		range_shift    = std::byteswap(range_shift);
	}
}

void TTF_table_record::fix_endianness()
{
	// Since the table_tag field is an array of uint8_t, we do
	// not have to swap the bytes to have it read correctly.
	if constexpr (std::endian::native == std::endian::little)
	{
		checksum = std::byteswap(checksum);
		offset   = std::byteswap(offset);
		length   = std::byteswap(length);
	}
}
