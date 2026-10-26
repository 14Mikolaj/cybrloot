//Scene.cpp

#include <utility>

#include "Scene.hpp"


Scene::Scene(const std::string& _name) :
    name(_name){}

void Scene::add_panel(Panel panel) {
    panels.push_back(std::move(panel));
}

void Scene::draw() const {
    for (const auto& panel : panels) {
        panel.draw();
    }
}

void Scene::update() const {

    for (const auto& panel : panels) {
        panel.update();
    }
}

const std::string& Scene::get_name() const {
    return name;
}

const std::vector<Panel>& Scene::get_panels() const {
    return panels;
}
