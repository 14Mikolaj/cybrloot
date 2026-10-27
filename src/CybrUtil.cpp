//CybrUtil.cpp

#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>

#include "CybrUtil.hpp"

namespace CybrUtil {
    
    //clear screen
    void cls() {
        std::cout << "\033[2J";
    }

    void debug(std::string text, int row) {
        std::string out = "";
        out += "\033[" + std::to_string(40 + row) + ";1H\033[2K" + text;
        std::cout << out << std::flush;
    }

    std::string a_to_string(action a) {
        switch (a) {
            case action::none:
                return "none";
            case action::left:
                return "left";
            case action::right:
                return "right";
            case action::up:
                return "up";
            case action::down:
                return "down";
            case action::quit:
                return "quit";
            case action::select:
                return "select";
            default:
                return "unknown";
        }
    }

    bool terminal_changed(Terminal& _terminal_size, Terminal& _last_terminal_size) {
        winsize size{};
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        _terminal_size.width = size.ws_col;
        _terminal_size.height = size.ws_row;
        if (_terminal_size.width != _last_terminal_size.width || _terminal_size.height != _last_terminal_size.height) {
            _last_terminal_size = _terminal_size;
            return 1;
        }
        return 0;
    }

}
