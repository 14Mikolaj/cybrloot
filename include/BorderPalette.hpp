//BorderPalette.hpp

#pragma once

#include <string>
#include <unordered_map>

struct ThemeColor {
    int bg;
    int fg;
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
    {"CachyOS", {17, 117}},
    {"Mint", {236, 106}},
    {"Arch", {18, 75}},
    {"Ubuntu", {53, 224}}
};
