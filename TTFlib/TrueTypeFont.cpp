#include "TrueTypeFont.h"
#include "TrueTypeFontImpl.h"

std::unique_ptr<TrueTypeFont> open_font(const std::string& file_name)
{
    return std::make_unique<TrueTypeFontImpl>(file_name);
}
