//Element.hpp

#pragma once

#include <string>
#include <optional>
#include <functional>

#include "BorderPalette.hpp"

struct Position {
    enum class Mode {
        Absolute,
        Relative
    };
    Mode mode;
    float x;
    float y;
    static Position absolute(int x, int y) {
        return {Mode::Absolute, float(x), float(y)};
    }
    static Position relative(float x, float y) {
        return {Mode::Relative, x, y};
    }
};


class Element {
public:
    int x;
    int y;
    Element(Position _position);
    Position position;
    virtual void draw(int parent_x, int parent_y, const TextColor& color) const = 0;
    virtual void update(int parent_x, int parent_y, const TextColor& color) const = 0;
    void layout_relative(int parent_w, int parent_h);
    void set_relative_pos(float _x, float _y);
    virtual ~Element() = default;
    virtual int get_width() const = 0;
    virtual int get_height() const = 0;
    enum class ColorRole {
        Normal,
        Highlight,
        Accent
    };
    virtual ColorRole color_role() const;
};


class Text : public Element {
public:
    Text(Position _position, std::string _content);
    Text(Position _position, std::function<std::string()> _content);
    void draw(int parent_x, int parent_y, const TextColor& color) const override;
    void update(int parent_x, int parent_y, const TextColor& color) const override;
    int get_width() const override;
    int get_height() const override;
private:
    std::function<std::string()> content;
    mutable std::string last_rendered;
    mutable bool dirty = true;
};

class Button : public Element {
public:
    Button(Position position, std::string _label, std::function<void()> _action);
    void draw(int parent_x, int parent_y, const TextColor& color) const override;
    void update(int parent_x, int parent_y, const TextColor& color) const override;
    void set_state(bool state);
    void activate();
    int get_width() const override;
    int get_height() const override;
    ColorRole color_role() const override;
private:
    std::function<void()> action;
    std::string label;
    bool highlighted = false;
    mutable bool last_state = false;
    mutable bool dirty = true;
};
