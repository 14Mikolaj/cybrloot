//Element.cpp

#include <iostream>
#include <algorithm>
#include <utility>

#include "Element.hpp"

Element::Element(int _x, int _y) :
    x(_x), y(_y){}

    Element::ColorRole Element::color_role() const {
    return ColorRole::Normal;
}

//static text
Text::Text(int _x, int _y, std::string _content) :
    Element(_x, _y), content([text = std::move(_content)](){return text;}){}

//dynamic text
Text::Text(int _x, int _y, std::function<std::string()> _content) :
    Element(_x, _y), content(std::move(_content)){}

void Text::draw(int parent_x, int parent_y, const TextColor& color) const {
    std::string new_content = content();
    std::string out_buffer = "\033[";
    out_buffer += std::to_string(parent_y + y + 1) + ";" + std::to_string(parent_x + x + 1) + "H";
    out_buffer += "\033[38;5;" + std::to_string(color.fg) + "m\033[48;5;" + std::to_string(color.bg) + "m";
    out_buffer += new_content;
    std::cout << out_buffer; 
    last_rendered = std::move(new_content);
    dirty = false;
}

void Text::update(int parent_x, int parent_y, const TextColor& color) const {
    std::string out_buffer;
    std::string current = content();
    if (!dirty && current == last_rendered) {
        return;
    }
    out_buffer += "\033[38;5;" + std::to_string(color.fg) + "m\033[48;5;" + std::to_string(color.bg) + "m";
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

Button::Button(int _x, int _y, std::string _label, std::function<void()> _action) :
    Element(_x, _y), label(std::move(_label)), action(std::move(_action)), highlighted(false){}

    Button::ColorRole Button::color_role() const {
        return highlighted ? ColorRole::Highlight : ColorRole::Normal;
    }

void Button::activate() {
    if (action){
        action();
    }
}

void Button::draw(int parent_x, int parent_y, const TextColor& color) const {
    std::string out_buffer = "\033[";
    out_buffer += std::to_string(parent_y + y + 1) + ";" + std::to_string(parent_x + x + 1) + "H";
    out_buffer += "\033[38;5;" + std::to_string(color.fg) + "m\033[48;5;" + std::to_string(color.bg) + "m";
    out_buffer += label;
    std::cout << out_buffer;
    last_state = highlighted;
    dirty = false;
}

void Button::update(int parent_x, int parent_y, const TextColor& color) const {
    if (!dirty && highlighted == last_state) {
        return;
    }
    std::string out_buffer = "\033[";
    out_buffer += std::to_string(parent_y + y + 1) + ";" + std::to_string(parent_x + x + 1) + "H";
    out_buffer += "\033[38;5;" + std::to_string(color.fg) + "m\033[48;5;" + std::to_string(color.bg) + "m";
    out_buffer += label;
    std::cout << out_buffer;
    last_state = highlighted;
    dirty = false;
}

void Button::set_state(bool state){
    if (highlighted != state) {
        highlighted = state;
        dirty = true;
    }
}
