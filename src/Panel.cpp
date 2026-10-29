//Panel.cpp

#include <iostream>
#include <utility>
#include <algorithm>

#include "Panel.hpp"
#include "CybrUtil.hpp"

Panel::Panel(PanelPosition _position,
        const std::string& _title,
        const std::string& _border,
        const std::string& _theme,
        const std::string& _id) :
    position(_position),
    title(_title), id(_id.empty() ? _title : _id), border(border_palette.at(_border)),
    theme(color_palette.at(_theme)){
        if (position.mode == PanelPosition::Mode::Absolute) {
            x_pos = static_cast<int>(position.x);
            y_pos = static_cast<int>(position.y);
            width = static_cast<int>(position.w);
            height = static_cast<int>(position.h);

        } else {
            x_pos = y_pos = width = height = 0;
        }
    }

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

Rect Panel::get_rect() const {
    return Rect{x_pos, y_pos, width + 2, height + 2};
}

std::string Panel::get_title() const {
    return title;
}

const std::string& Panel::get_id() const {
    return id;
}

void Panel::layout(const CybrUtil::Terminal term, const LayoutContext& context) {
    if (position.mode == PanelPosition::Mode::Relative) {
        int available_width = std::max(0, term.width - (2 * term.margin));
        int available_height = std::max(0, term.height - (2 * term.margin));
        width = std::max(0, int(position.w * available_width) - 2);
        height = std::max(0, int(position.h * available_height) - 2);
        x_pos = std::clamp(int((position.x * available_width) + term.margin + 1) - static_cast<int>((width + 2) / 2),
               term.margin + 1,
               std::max(term.margin + 1, term.margin + 1 + available_width - (width + 2)));
        y_pos = std::clamp(int((position.y * available_height) + term.margin + 1) - static_cast<int>((height + 2) / 2),
                term.margin + 1,
                std::max(term.margin + 1, term.margin + 1 + available_height - (height + 2)));
    }
    if (position.mode == PanelPosition::Mode::Anchored) {
        Rect r = position.anchor(context);
        x_pos = r.x;
        y_pos = r.y;
        width = std::max(0, r.w - 2);
        height = std::max(0, r.h - 2);
    }
    layout_elements();
}

void Panel::layout_elements() { 
    for (auto& element : elements) {
        element->layout_relative(width, height);
    }
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

const PanelPosition::Mode Panel::get_panel_position() const {
    return position.mode;
}

const std::vector<std::unique_ptr<Element>>& Panel::get_elements() const {
    return elements;
}

