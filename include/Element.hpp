//Element.hpp

#pragma once

#include <string>


class Element {
public:
    Element(int _x, int _y);
    int x;
    int y;
    virtual void draw(int parent_x, int parent_y) const = 0;
    virtual ~Element() = default;
};


class Text : public Element {
public:
    Text(int _x, int _y, std::string _content);
    std::string content;
    void draw(int parent_x, int parent_y) const override;

};
