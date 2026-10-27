//UIManager.hpp

#pragma once

#include <memory>
#include <utility>
#include <optional>

#include "Scene.hpp"
#include "CybrUtil.hpp"

class UIManager {
    public:
        UIManager(CybrUtil::Terminal& _term);
        void add_scene(std::unique_ptr<Scene> scene);
        void set_scene(std::string scene_name);
        void draw_scene();
        void update_scene();
        void init(CybrUtil::GameData& game);
        void process_input(CybrUtil::action input);
        void layout_panels();
    private:
        CybrUtil::Terminal& term;
        void get_focusable_list();
        std::vector<std::unique_ptr<Scene>> scenes;
        Scene* cur_scene = nullptr;
        std::vector<Button*> focusables;
        std::optional<std::size_t> focused_index;
};
