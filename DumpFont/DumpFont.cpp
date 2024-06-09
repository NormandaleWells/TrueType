
#include <print>

#include "TrueTypeFont.h"

int main(int argc, char * argv[])
{
    if (argc < 2)
    {
        std::print("Usage: DumpFont <font_file_name>");
        return 0;
    }

    std::print("Dumping font file {}:\n", argv[1]);

    auto font = open_font(argv[1]);
    
    auto [major, minor] = font->get_header_version();
    std::print("Version: {}.{}\n", major, minor);
}
