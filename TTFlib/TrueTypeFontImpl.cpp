#include "TrueTypeFontImpl.h"

#include <algorithm>
#include <bit>
#include <format>

#include "TTF_types.h"
#include "TTF_head.h"

TrueTypeFontImpl::TrueTypeFontImpl(const std::string& font_file_name)
{
	file_name = font_file_name;
	file.open(file_name, std::ios_base::in | std::ios_base::binary);
	if (!file.is_open())
	{
		throw std::runtime_error(std::format("Could not open {}.", file_name));
	}

	auto bytes_read = file.sgetn(reinterpret_cast<std::byte *>(&table_directory),
			sizeof table_directory);
	if (bytes_read != sizeof table_directory)
	{
		throw std::runtime_error(std::format("Could not read table directory in {}", file_name));
	}
	table_directory.fix_endianness();

	if (table_directory.sfnt_version != 0x00010000 && table_directory.sfnt_version != 0x4f54544f)
	{
		throw std::runtime_error(std::format("Invalid sfntVersion in {}", file_name));
	}

	// Should we verify search_range, entry_selector, and range_shift?

	table_records.reset(new TTF_table_record[table_directory.num_tables]);
	bytes_read = file.sgetn(reinterpret_cast<std::byte*>(table_records.get()),
			sizeof TTF_table_record * table_directory.num_tables);
	if (bytes_read != sizeof TTF_table_record * table_directory.num_tables)
	{
		throw std::runtime_error(std::format("Could not read table records in {}", file_name));
	}
	for (size_t i = 0; i < table_directory.num_tables; i++)
	{
		table_records[i].fix_endianness();
	}
	
	read_record<TTF_head>(&head, Tag_head);
}

TTF_version TrueTypeFontImpl::get_header_version() const
{
	return TTF_version{ head.major_version, head.minor_version };
}

static bool compare_tag(const TTF_Tag lhs, const TTF_Tag rhs)
{
	// lhs and rhs are basically 4-character strings; the easiest
	// way to compare them is to byteswap them and compare them
	// as 32-bit values.
	uint32_t ulhs = std::byteswap(*reinterpret_cast<const uint32_t*>(lhs));
	uint32_t urhs = std::byteswap(*reinterpret_cast<const uint32_t*>(rhs));
	return ulhs < urhs;
}

static bool compare_record_tag(const TTF_table_record& lhs, const TTF_Tag rhs)
{
	return compare_tag(lhs.table_tag, rhs);
}

TTF_table_record* TrueTypeFontImpl::find_table_record(const TTF_Tag tag)
{
	TTF_table_record* first = &table_records[0];
	TTF_table_record* last = &table_records[table_directory.num_tables];
	auto p = std::lower_bound(first, last, tag, compare_record_tag);

	// Make sure we really found it.
	if (p == last || compare_tag(tag, p->table_tag))
	{
		p = nullptr;
	}
	return p;
}

static std::string tag_to_string(const TTF_Tag tag)
{
	return std::string{ reinterpret_cast<const char*>(tag), 4 };
}

template<class RecType>
void TrueTypeFontImpl::read_record(RecType* rec, const TTF_Tag tag)
{
	TTF_table_record* rec_ptr = find_table_record(tag);
	if (rec_ptr == nullptr)
	{
		throw std::runtime_error(std::format("No '{}' record in {}", tag_to_string(tag), file_name));
	}
	file.pubseekpos(rec_ptr->offset, std::ios_base::in);
	auto bytes_read = file.sgetn(reinterpret_cast<std::byte*>(rec), sizeof(RecType));
	if (bytes_read != sizeof(RecType))
	{
		throw std::runtime_error(std::format("Could not read '{}' table in {}", tag_to_string(tag), file_name));
	}
	rec->fix_endianness();
}
