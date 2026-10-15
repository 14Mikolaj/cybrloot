//Scene.hpp

#pragma once

#include <string>
#include <vector>

#include "Panel.hpp"


class Scene {
public:
    Scene(const std::string& _name);
    void add_panel(Panel panel);
    void draw() const;
    const std::string& get_name() const;
    void update() const;
private:
    std::string name;
    std::vector<Panel> panels;
};
