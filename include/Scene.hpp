//Scene.hpp

#pragma once

#include <string>
#include <vector>

#include "Panel.hpp"
#include "CybrUtil.hpp"


class Scene {
public:
    Scene(const std::string& _name);
    void add_panel(Panel panel);
    void draw() const;
    const std::string& get_name() const;
    void update() const;
    void layout_panels(const CybrUtil::Terminal term);
    const std::vector<Panel>& get_panels() const;
private:
    std::string name;
    std::vector<Panel> panels;
};
