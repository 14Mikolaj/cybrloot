//UIManager.cpp

#include <iostream>

#include "UIManager.hpp"

void UIManager::get_focusable_list() {
    focusables.clear();
    focused_index = 0;
    for (auto& panel : cur_scene->get_panels()) {
        for (auto& element : panel.get_elements()) {
            if (auto* button = dynamic_cast<Button*>(element.get())) {
                focusables.push_back(button);
            }
        }
    }
    if (focusables.size() > 0) {
        focusables[0]->set_state(true);
    }
}

void UIManager::add_scene(std::unique_ptr<Scene> scene) {
    scenes.push_back(std::move(scene));
};

void UIManager::set_scene(std::string scene_name) {
    for (auto& scene : scenes){
        if (scene->get_name() == scene_name) {
                cur_scene = scene.get();
                get_focusable_list();
                return;
        } 
    }
};
void UIManager::draw_scene() {
    if (cur_scene) {
        cur_scene->draw();
        std::cout << std::flush;
    }
}

void UIManager::update_scene() {
    if (cur_scene) {
        cur_scene->update();
        std::cout << std::flush;
    }
}

void UIManager::process_input(CybrUtil::action input) {
    if (focusables.empty() || ! focused_index) {
        return;
    }
    auto& index = focused_index.value();
    auto previous_index = index;
    switch (input) {
        case CybrUtil::action::left:
        case CybrUtil::action::up:
            if (index == 0) {
                index = focusables.size() - 1;
            } else {
                index -= 1;
            }
            break;
        case CybrUtil::action::right:
        case CybrUtil::action::down:
            if (index == focusables.size() - 1) {
                index = 0;
            } else {
                index += 1;
            }
            break;
        case CybrUtil::action::select:
            focusables[index]->activate();
            return;
        default:
            return;
    }
    if (index != previous_index) {
        focusables[previous_index]->set_state(false);
        focusables[index]->set_state(true);
    }
}
