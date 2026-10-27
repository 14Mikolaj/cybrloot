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
    Terminal terminal_size{0, 0, 2};
    Terminal last_terminal_size = terminal_size;

    TerminalWrapper Terminal;
    Terminal.init();
    pollfd pfd{STDIN_FILENO, POLLIN, 0};
    using Clock = std::chrono::steady_clock;
    constexpr auto tick = std::chrono::milliseconds(6);
    constexpr double tick_seconds = 0.006;
    auto previous = Clock::now();
    Clock::duration accumulator = Clock::duration::zero();
    double data_fraction = 0.0;
    double data_per_second = 90.0;

    GameData game{100, 50};
    UIManager UI(terminal_size);
    action input;

    UI.init(game);
    terminal_changed(terminal_size, last_terminal_size);
    UI.layout_panels();
    cls();
    UI.draw_scene();

    while (true) {
        if (terminal_changed(terminal_size, last_terminal_size)) {
            UI.layout_panels();
            cls();
            UI.draw_scene();
        }
        int ready = poll(&pfd, 1, 6);
        if (ready) {
            input = Terminal.parse_input();
            debug(a_to_string(input));
            UI.process_input(input);
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

