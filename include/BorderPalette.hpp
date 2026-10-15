//BorderPalette.hpp

#pragma once

#include <string>
#include <unordered_map>

struct TextColor {
    int bg;
    int fg;
};

struct ThemeColor {
    TextColor normal;
    TextColor highlight;
    TextColor accent;
};

struct BorderStyle {
    std::string tl;
    std::string tr;
    std::string bl;
    std::string br;
    std::string h;
    std::string v;
};

inline const std::unordered_map<std::string, BorderStyle> border_palette = {
    {"thin", 
        {"┌" ,"┐", "└", "┘", "─", "│"}},
    {"rounded", 
        {"╭", "╮", "╰", "╯", "─", "│"}},
    {"double",
        {"╔", "╗", "╚", "╝", "═", "║"}},
    {"thick", 
        {"┏", "┓", "┗", "┛", "━", "┃"}}
};

inline const std::unordered_map<std::string, ThemeColor> color_palette = {
    {"CachyOS", {{17, 117}, {25, 153}, {17, 115}}},
    {"Mint", {{236, 106}, {150, 22}, {236, 118}}},
    {"Arch", {{18, 75}, {33, 17}, {18, 117}}},
    {"Ubuntu", {{53, 224}, {169, 53}, {53, 163}}}
};
