//Element.cpp

#include <iostream>
#include <algorithm>
#include <utility>
#include <cmath>

#include "Element.hpp"

Element::Element(Position _position) :
    x(0), y(0), position(_position) {
        if (position.mode == Position::Mode::Absolute) {
            x = static_cast<int>(position.x);
            y = static_cast<int>(position.y);
        }
    };

    Element::ColorRole Element::color_role() const {
    return ColorRole::Normal;
}

void Element::layout_relative(int parent_w, int parent_h) {
    if (position.mode != Position::Mode::Relative) {
        return;
    }
    x = (parent_w * position.x) - std::round(get_width() / 2.0f);
    y = (parent_h * position.y) - std::round(get_height() / 2.0f);
}


//static text
Text::Text(Position _position, std::string _content) :
    Element(_position), content([text = std::move(_content)](){return text;}){}

//dynamic text
Text::Text(Position _position, std::function<std::string()> _content) :
    Element(_position), content(std::move(_content)){}

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

int Text::get_width() const {
    return content().length();
}

int Text::get_height() const {
    return 1;
}

Button::Button(Position _position, std::string _label, std::function<void()> _action) :
    Element(_position), label(std::move(_label)), action(std::move(_action)), highlighted(false){}

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
    out_buffer += "\033[0m";
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
    out_buffer += "\033[0m";
    std::cout << out_buffer;
    last_state = highlighted;
    dirty = false;
}

int Button::get_width() const {
    return label.size();
}

int Button::get_height() const {
    return 1;
}

void Button::set_state(bool state){
    if (highlighted != state) {
        highlighted = state;
        dirty = true;
    }
}
