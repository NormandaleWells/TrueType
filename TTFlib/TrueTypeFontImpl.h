#pragma once

#include <bit>
#include <cstddef>
#include <fstream>
#include <memory>
#include <string>

#include "TrueTypeFont.h"
#include "TTF_table_directory.h"
#include "TTF_head.h"

static_assert(std::endian::native == std::endian::little || std::endian::native == std::endian::big,
		"TTFlib does not support a mixed byte order");

using bfilebuf = std::basic_filebuf<std::byte>;

class TrueTypeFontImpl : public TrueTypeFont
{
public:
	explicit TrueTypeFontImpl(const std::string& file_name);

	TTF_version get_header_version() const override;

private:
	std::string file_name;
	bfilebuf file;
	TTF_table_directory table_directory;
	std::unique_ptr<TTF_table_record[]> table_records;

	TTF_head head;

	TTF_table_record* find_table_record(const TTF_Tag tag);
	template<class RecType>
	void read_record(RecType* rec, const TTF_Tag tag);
};
