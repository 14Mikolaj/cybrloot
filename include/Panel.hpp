//Panel.hpp

#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Element.hpp"
#include "BorderPalette.hpp"
#include "CybrUtil.hpp"

struct PanelPosition {
    enum class Mode {
        Absolute,
        Relative
    };
    Mode mode;
    float x;
    float y;
    float w;
    float h;
    static PanelPosition absolute(int x, int y, int w, int h) {
        return {Mode::Absolute, float(x), float(y), float(w), float (h)};
    }
    static PanelPosition relative(float x, float y, float w, float h) {
        return {Mode::Relative, x, y, w, h};
    }
};

class Panel {
public:
    Panel(PanelPosition _position,
            const std::string& _title = "",
            const std::string& _border = "thin",
            const std::string& _theme = "CachyOS");
    void draw() const;
    void update() const;
    void add_element(std::unique_ptr<Element> element);
    void layout(const CybrUtil::Terminal term);
    void layout_elements();
    const TextColor& resolve_color(Element::ColorRole role) const;
    const std::vector<std::unique_ptr<Element>>& get_elements() const;
    const PanelPosition::Mode get_panel_position() const;
private:
    PanelPosition position;
    int x_pos;
    int y_pos;
    int width;
    int height;

    std::string title;

    BorderStyle border;
    ThemeColor theme;

    std::vector<std::unique_ptr<Element>> elements;
};
