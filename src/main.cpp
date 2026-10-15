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
    game_data game{100, 50};
    UIManager UI;

    Scene welcome("welcome");
    Panel welcome_panel(5, 3, 55, 10, "Welcome", "double", "Mint");
    welcome_panel.add_element(std::make_unique<Text>(2, 2, "Welcome to cybrloot. Have you played before?"));
    auto load_button = std::make_unique<Button>(10, 5, "[LOAD GAME]", [](){});
    Button* load_ptr = load_button.get();
    welcome_panel.add_element(std::move(load_button));
    //welcome_panel.add_element(std::make_unique<Button>(10, 5, "[LOAD GAME]", [](){})); 
    welcome_panel.add_element(std::make_unique<Text>(25, 5, "[NEW GAME]")); 
    welcome.add_panel(std::move(welcome_panel));
    UI.add_scene(std::make_unique<Scene>(std::move(welcome)));

    Scene newplayer("newplayer");

    Scene loadsave("loadsave");

    Scene dashboard("dashboard");
    Panel data_panel(50,20,20,8, "DATA", "thick", "Ubuntu");
    data_panel.add_element(std::make_unique<Text>(0, 0, [&game](){return "DATA: " + std::to_string(game.data);}));
    dashboard.add_panel(std::move(data_panel));
    UI.add_scene(std::make_unique<Scene>(std::move(dashboard)));

    UI.set_scene("welcome");
    cls();
    UI.draw_scene();

    bool tog = false;
    for (int i = 0; i < 15; i++) {
        load_ptr->set_state(tog);
        game.data += 250;
        UI.update_scene();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        tog = !tog;
    }
    for (int i = 0; i < 1; i ++) {
        game.data -= 400;
        UI.update_scene();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }


    std::cout << "\nHello World!\n";
    return 0;
}

