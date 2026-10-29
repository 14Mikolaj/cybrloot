//Scene.cpp

#include <utility>
#include <stdexcept>
#include <unordered_set>

#include "Scene.hpp"


Scene::Scene(const std::string& _name) :
    name(_name){}

void Scene::add_panel(Panel panel) {
    panel.layout_elements();
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

void Scene::layout_panels(const CybrUtil::Terminal term) {
    // Validate IDs up front: a display title is not necessarily unique.
    std::unordered_set<std::string> ids;
    for (const auto& panel : panels) {
        const auto& id = panel.get_id();
        if (id.empty()) {
            throw std::invalid_argument("Panel ID must not be empty");
        }
        if (!ids.insert(id).second) {
            throw std::invalid_argument("Duplicate panel ID: " + id);
        }
    }

    LayoutContext context{term.width, term.height, {}};
    std::vector<bool> resolved(panels.size(), false);
    std::size_t remaining = panels.size();

    while (remaining > 0) {
        bool made_progress = false;
        for (std::size_t i = 0; i < panels.size(); ++i) {
            if (resolved[i]) {
                continue;
            }
            try {
                panels[i].layout(term, context);
            } catch (const MissingPanelDependency& e) {
                if (!ids.contains(e.id)) {
                    throw std::invalid_argument("Unknown panel ID: " + e.id);
                }
                continue; // Forward reference; retry after its dependency is laid out.
            }
            context.panels.emplace(panels[i].get_id(), panels[i].get_rect());
            resolved[i] = true;
            --remaining;
            made_progress = true;
        }

        if (!made_progress) {
            std::string pending;
            for (std::size_t i = 0; i < panels.size(); ++i) {
                if (!resolved[i]) {
                    if (!pending.empty()) pending += ", ";
                    pending += panels[i].get_id();
                }
            }
            throw std::logic_error("Circular panel layout dependencies: " + pending);
        }
    }
}

const std::string& Scene::get_name() const {
    return name;
}

const std::vector<Panel>& Scene::get_panels() const {
    return panels;
}
