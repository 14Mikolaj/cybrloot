//UIManager.cpp

#include <iostream>

#include "UIManager.hpp"
#include "Scene.hpp"
#include "Panel.hpp"

UIManager::UIManager(CybrUtil::Terminal& _term):
    term(_term){};

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

void UIManager::init(CybrUtil::GameData& game) {

    Scene welcome("welcome");
    Panel welcome_panel(PanelPosition::absolute(5, 3, 55, 10), "Welcome", "double", "Mint");
    welcome_panel.add_element(std::make_unique<Text>(Position::absolute(2, 2), "Welcome to cybrloot. Have you played before?"));
    welcome_panel.add_element(std::make_unique<Button>(Position::relative(0.33f, 0.50f), "[LOAD GAME]", [this](){})); 
    welcome_panel.add_element(std::make_unique<Button>(Position::relative(0.66f, 0.50f), "[NEW GAME]", [this](){CybrUtil::cls();set_scene("dashboard");layout_panels();draw_scene();})); 
    welcome.add_panel(std::move(welcome_panel));
    this->add_scene(std::make_unique<Scene>(std::move(welcome)));

    Scene newplayer("newplayer");

    Scene loadsave("loadsave");

    Scene dashboard("dashboard");
    Panel menu_panel(PanelPosition::relative(0.0f, 0.0f, 0.2f, 0.75f), "MENU", "thin", "Arch");
    Panel nodes_panel(PanelPosition::relative(1.0f, 0.0f, 0.2f, 0.75f), "NODES", "thick", "CachyOS");
    Panel data_panel(PanelPosition::anchored([](const LayoutContext ctx){
                const auto& menu = ctx.get("MENU");
                const auto& nodes = ctx.get("NODES");
                return Rect{menu.right(), menu.top(), nodes.left() - menu.right(), menu.h / 3};
                }), "DATA", "double", "Mint");
    Panel console_panel(PanelPosition::anchored([](const LayoutContext ctx) {
                const auto& data = ctx.get("DATA");
                const auto& menu = ctx.get("MENU");
                return Rect{
                data.left(),
                data.bottom(),
                data.w,
                menu.bottom() - data.bottom()};
                }), "CONSOLE", "rounded", "Ubuntu");
    data_panel.add_element(std::make_unique<Text>(Position::relative(0.5f, 0.5f), [&game](){return "DATA: " + std::to_string(game.data);}));
    dashboard.add_panel(std::move(menu_panel));
    dashboard.add_panel(std::move(nodes_panel));
    dashboard.add_panel(std::move(data_panel));
    dashboard.add_panel(std::move(console_panel));
    add_scene(std::make_unique<Scene>(std::move(dashboard)));

    set_scene("welcome");
 
}

void UIManager::add_scene(std::unique_ptr<Scene> scene) {
    scenes.push_back(std::move(scene));
}

void UIManager::set_scene(std::string scene_name) {
    for (auto& scene : scenes){
        if (scene->get_name() == scene_name) {
                cur_scene = scene.get();
                get_focusable_list();
                return;
        } 
    }
}

void UIManager::layout_panels() {
    if (cur_scene) {
        cur_scene->layout_panels(term);
    }
}

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
