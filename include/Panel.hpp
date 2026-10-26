//Panel.hpp

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Element.hpp"
#include "BorderPalette.hpp"

class Panel {
public:
    Panel(int _x, int _y, int _w, int _h,
            const std::string& _title = "",
            const std::string& _border = "thin",
            const std::string& _theme = "CachyOS");
    void draw() const;
    void update() const;
    void add_element(std::unique_ptr<Element> element);
    const TextColor& resolve_color(Element::ColorRole role) const;
    const std::vector<std::unique_ptr<Element>>& get_elements() const;
private:
    int x_pos;
    int y_pos;
    int width;
    int height;

    std::string title;

    BorderStyle border;
    ThemeColor theme;

    std::vector<std::unique_ptr<Element>> elements;
};
