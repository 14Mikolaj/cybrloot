//Element.cpp

#include <iostream>
#include <algorithm>
#include <utility>

#include "Element.hpp"

Element::Element(int _x, int _y) :
    x(_x), y(_y){}

//static text
Text::Text(int _x, int _y, std::string _content) :
    Element(_x, _y), content([text = std::move(_content)](){return text;}){}

//dynamic text
Text::Text(int _x, int _y, std::function<std::string()> _content) :
    Element(_x, _y), content(std::move(_content)){}

void Text::draw(int parent_x, int parent_y) const {
    std::string new_content = content();
    std::string out_buffer = "\033[";
    out_buffer += std::to_string(parent_y + y + 1) + ";" + std::to_string(parent_x + x + 1) + "H";
    out_buffer += new_content;
    std::cout << out_buffer; 
    last_rendered = std::move(new_content);
    dirty = false;
}

void Text::update(int parent_x, int parent_y) const {
    std::string out_buffer;
    std::string current = content();
    if (!dirty && current == last_rendered) {
        return;
    }
    std::size_t length = std::max(current.size(), last_rendered.size());
    for (std::size_t c = 0; c < length; c++) {
        char old_char = c < last_rendered.size() ? last_rendered[c] : ' ';
        char new_char = c < current.size() ? current[c] : ' ';
        if (dirty || old_char != new_char) {
            out_buffer += "\033[" + std::to_string(parent_y + y + 1) + ";" + std::to_string(parent_x + x + 1 + static_cast<int>(c)) + "H"; out_buffer += new_char; }
    }
    if (!out_buffer.empty()) { 
        std::cout << out_buffer << std::flush;
    }
    last_rendered = std::move(current);
    dirty = false;
}
