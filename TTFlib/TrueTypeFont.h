#pragma once

#include <cinttypes>
#include <memory>
#include <string>
#include <tuple>

using TTF_version = std::tuple<std::uint16_t, std::uint16_t>;

class TrueTypeFont
{
public:
	explicit TrueTypeFont() = default;
	virtual TTF_version get_header_version() const = 0;
};

std::unique_ptr<TrueTypeFont> open_font(const std::string& file_name);
