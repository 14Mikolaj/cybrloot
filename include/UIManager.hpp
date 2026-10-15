//UIManager.hpp

#pragma once

#include <memory>
#include <utility>

#include "Scene.hpp"

class UIManager {
    public:
        void add_scene(std::unique_ptr<Scene> scene);
        void set_scene(std::string scene_name);
        void draw_scene();
        void update_scene();
        void init(std::string path);
    private:
        std::vector<std::unique_ptr<Scene>> scenes;
        Scene* cur_scene = nullptr;
};
