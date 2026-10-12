//Element.cpp

#include <iostream>

#include "Element.hpp"

Element::Element(int _x, int _y) :
    x(_x), y(_y){}

Text::Text(int _x, int _y, std::string _content) :
    Element(_x, _y), content(_content){}


void Text::draw(int parent_x, int parent_y) const {
    std::string out_buffer = "\033[";
    out_buffer += std::to_string(parent_y + y + 1) + ";" + std::to_string(parent_x + x + 1) + "H";
    out_buffer += content;
    std::cout << out_buffer; 
}
