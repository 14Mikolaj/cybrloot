//Element.hpp

#pragma once

#include <string>
#include <functional>


class Element {
public:
    Element(int _x, int _y);
    int x;
    int y;
    virtual void draw(int parent_x, int parent_y) const = 0;
    virtual void update(int parent_x, int parent_y) const = 0;
    virtual ~Element() = default;
};


class Text : public Element {
public:
    Text(int _x, int _y, std::string _content);
    Text(int _x, int _y, std::function<std::string()> _content);
    void draw(int parent_x, int parent_y) const override;
    void update(int parent_x, int parent_y) const override;
private:
    std::function<std::string()> content;
    mutable std::string last_rendered;
    mutable bool dirty = true;
};
