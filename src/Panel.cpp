//Panel.cpp

#include <iostream>
#include <utility>

#include "Panel.hpp"

Panel::Panel(int _x, int _y, int _w, int _h,
        const std::string& _title,
        const std::string& _border,
        const std::string& _theme) :
    x_pos(_x), y_pos(_y), width(_w), height(_h),
    title(_title), border(border_palette.at(_border)),
    theme(color_palette.at(_theme)){}

void Panel::draw() const {
    std::string out_buffer;
    int title_start = (width - title.size()) / 2;
    out_buffer += "\033[38;5;" + std::to_string(theme.normal.fg) + "m\033[48;5;" + std::to_string(theme.normal.bg) + "m";

    for ( int row = 0; row <= height + 1; row++) {
        out_buffer += "\033[" + std::to_string(y_pos + row) + ";" + std::to_string(x_pos) + "H";
        if (row == 0 ) {
            out_buffer += border.tl;
        } else if (row == height + 1) {
           out_buffer += border.bl;
        } else {
            out_buffer += border.v;
        }
        for ( int col = 0 ; col < width ; col++) {
            if (row != 0 && row != height + 1) {
                out_buffer += " ";
            } else {
                if (row == 0 && !title.empty() && col >= (title_start) && col < title_start + title.size()) {
                    out_buffer += title[col - title_start];  
                } else {
                out_buffer += border.h;
                }
            }
        }
        if (row == 0) {
            out_buffer += border.tr;
        } else if (row == height + 1) {
            out_buffer += border.br;
        } else {
            out_buffer += border.v;
        }
    }
    std::cout << out_buffer;

    for (const auto& element : elements) {
        const TextColor& color = resolve_color(element->color_role());
        element->draw(x_pos, y_pos, color);
    }

}

void Panel::update() const {
    for (const auto& element : elements) {
        const TextColor& color = resolve_color(element->color_role());
        element->update(x_pos, y_pos, color);
    }
}

void Panel::add_element(std::unique_ptr<Element> element) {
  elements.push_back(std::move(element)); 
}

const TextColor& Panel::resolve_color(Element::ColorRole role) const {
    switch (role) {
        case Element::ColorRole::Highlight:
            return theme.highlight;
        case Element::ColorRole::Accent:
            return theme.accent;
        default:
            return theme.normal;
    }
}

const std::vector<std::unique_ptr<Element>>& Panel::get_elements() const {
    return elements;
}
