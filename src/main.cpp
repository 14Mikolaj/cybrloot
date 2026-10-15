//main.cpp

#include <iostream>
#include <chrono>
#include <thread>

#include "Scene.hpp"
#include "Panel.hpp"
#include "CybrUtil.hpp"
#include "UIManager.hpp"

using namespace CybrUtil;

struct game_data {
    int data;
    int money;
};

int main() {
    bool running = true;
    game_data game{100, 50};
    UIManager UIManager;
    Scene dashboard("dashboard");
    Panel data_panel(50,20,20,8, "DATA", "thick", "Ubuntu");
    data_panel.add_element(std::make_unique<Text>(0, 0, [&game](){return "DATA: " + std::to_string(game.data);}));
    dashboard.add_panel(std::move(data_panel));
    UIManager.add_scene(std::make_unique<Scene>(std::move(dashboard)));
    UIManager.set_scene("dashboard");
    cls();
    UIManager.draw_scene();
    for (int i = 0; i < 100; i++) {
        game.data += 250;
        UIManager.update_scene();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    for (int i = 0; i < 100; i ++) {
        game.data -= 400;
        UIManager.update_scene();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    std::cout << "\nHello World!\n";
    return 0;
}

