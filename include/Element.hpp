//Element.hpp

#pragma once

#include <string>
#include <functional>

#include "BorderPalette.hpp"

class Element {
public:
    Element(int _x, int _y);
    int x;
    int y;
    virtual void draw(int parent_x, int parent_y, const TextColor& color) const = 0;
    virtual void update(int parent_x, int parent_y, const TextColor& color) const = 0;
    virtual ~Element() = default;
    enum class ColorRole {
        Normal,
        Highlight,
        Accent
    };
    virtual ColorRole color_role() const;
};


class Text : public Element {
public:
    Text(int _x, int _y, std::string _content);
    Text(int _x, int _y, std::function<std::string()> _content);
    void draw(int parent_x, int parent_y, const TextColor& color) const override;
    void update(int parent_x, int parent_y, const TextColor& color) const override;
private:
    std::function<std::string()> content;
    mutable std::string last_rendered;
    mutable bool dirty = true;
};

class Button : public Element {
public:
    Button(int _x, int _y, std::string _label, std::function<void()> _action);
    void draw(int parent_x, int parent_y, const TextColor& color) const override;
    void update(int parent_x, int parent_y, const TextColor& color) const override;
    void set_state(bool state);
    void activate();
    ColorRole color_role() const override;
private:
    std::function<void()> action;
    std::string label;
    bool highlighted = false;
    mutable bool last_state = false;
    mutable bool dirty = true;
};
