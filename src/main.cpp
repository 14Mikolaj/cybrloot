//main.cpp

#include <iostream>
#include <chrono>
#include <thread>
#include <termios.h>
#include <unistd.h>
#include <poll.h>

#include "Scene.hpp"
#include "Panel.hpp"
#include "CybrUtil.hpp"
#include "UIManager.hpp"
#include "TerminalWrapper.hpp"

using namespace CybrUtil;


int main() {
    TerminalWrapper Terminal;
    Terminal.init();
    pollfd pfd{STDIN_FILENO, POLLIN, 0};
    using Clock = std::chrono::steady_clock;
    constexpr auto tick = std::chrono::milliseconds(6);
    constexpr double tick_seconds = 0.006;
    auto previous = Clock::now();
    Clock::duration accumulator = Clock::duration::zero();
    double data_fraction = 0.0;
    double data_per_second = 1.0;

    game_data game{100, 50};
    UIManager UI;
    action input;

    Scene welcome("welcome");
    Panel welcome_panel(5, 3, 55, 10, "Welcome", "double", "Mint");
    welcome_panel.add_element(std::make_unique<Text>(2, 2, "Welcome to cybrloot. Have you played before?"));
    //auto load_button = std::make_unique<Button>(10, 5, "[LOAD GAME]", [](){});
    ///Button* load_ptr = load_button.get();
    //welcome_panel.add_element(std::move(load_button));
    welcome_panel.add_element(std::make_unique<Button>(10, 5, "[LOAD GAME]", [](){})); 
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

    UI.set_scene("dashboard");
    cls();
    UI.draw_scene();

    while (true) {
        int ready = poll(&pfd, 1, 6);
        if (ready) {
            input = Terminal.parse_input();
            debug(a_to_string(input));
            //UI.process_input(input);
            if (input == action::quit) {
                break;
            }
        }
        auto now = Clock::now();
        accumulator += now - previous;
        previous = now;
        auto ticks = accumulator / tick;
        accumulator -= ticks * tick;
        if (ticks > 0) {
            data_fraction += ticks * tick_seconds * data_per_second;
            int earned = static_cast<int>(data_fraction);
            game.data += earned;
            data_fraction -= earned;
        }
        UI.update_scene();
    }

    debug("Hello World", 2);
    return 0;
}

