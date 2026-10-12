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
