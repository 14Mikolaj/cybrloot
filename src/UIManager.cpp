//UIManager.cpp

#include "UIManager.hpp"

void UIManager::add_scene(std::unique_ptr<Scene> scene) {
    scenes.push_back(std::move(scene));
};
void UIManager::set_scene(std::string scene_name) {
    for (auto& scene : scenes){
        if (scene->get_name() == scene_name) {
                cur_scene = scene.get();
                return;
        } 
    }
};
void UIManager::draw_scene() {
    if (cur_scene) {
        cur_scene->draw();
    }
}
void UIManager::update_scene() {
    if (cur_scene) {
        cur_scene->update();
    }
}
