//Panel.hpp

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>
#include <utility>
#include <unordered_map>
#include <stdexcept>

#include "Element.hpp"
#include "BorderPalette.hpp"
#include "CybrUtil.hpp"

struct Rect {
    int x, y, w, h;
    int left() const {return x;}
    int right() const {return x + w;}
    int top() const {return y;}
    int bottom() const {return y + h;}
};

// This signals that an anchored panel needs another panel's rectangle first.
class MissingPanelDependency : public std::out_of_range {
public:
    explicit MissingPanelDependency(std::string missing_id)
        : std::out_of_range("Unresolved panel id: " + missing_id), id(std::move(missing_id)) {}

    std::string id;
};

struct LayoutContext {
    int cols;
    int rows;
    std::unordered_map<std::string, Rect> panels;
    const Rect& get(const std::string& id) const {
        auto it = panels.find(id);
        if (it == panels.end()) {
            throw MissingPanelDependency(id);
        }
        return it->second;
    }
};

struct PanelPosition {
    enum class Mode {
        Absolute,
        Relative,
        Anchored
    };
    Mode mode;
    float x, y, w, h;
    // Anchors should be side-effect-free: layout may retry them while resolving dependencies.
    std::function<Rect(const LayoutContext&)> anchor;
    static PanelPosition absolute(int x, int y, int w, int h) {
        return {Mode::Absolute, float(x), float(y), float(w), float (h)};
    }
    static PanelPosition relative(float x, float y, float w, float h) {
        return {Mode::Relative, x, y, w, h};
    }
    static PanelPosition anchored(std::function<Rect(const LayoutContext&)> rule){
        return {Mode::Anchored, 0, 0, 0, 0, std::move(rule)};
    }
};

class Panel {
public:
    Panel(PanelPosition _position,
            const std::string& _title = "",
            const std::string& _border = "thin",
            const std::string& _theme = "CachyOS",
            const std::string& _id = "");
    void draw() const;
    void update() const;
    void add_element(std::unique_ptr<Element> element);
    void layout(const CybrUtil::Terminal term, const LayoutContext& context);
    void layout_elements();
    Rect get_rect() const;
    std::string get_title() const;
    const std::string& get_id() const;
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
    std::string id;

    BorderStyle border;
    ThemeColor theme;

    std::vector<std::unique_ptr<Element>> elements;
};
