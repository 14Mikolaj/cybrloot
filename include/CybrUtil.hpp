//CybrUtil.hpp

#pragma once

#include <string>

namespace CybrUtil {
    
    void cls(); 
    void debug(std::string text, int row = 0);
    
    struct GameData {
        int data;
        int money;
    };

    enum class action {
        none,
        left,
        right,
        up,
        down,
        quit,
        select,
    };

    std::string a_to_string(action a);

    struct Terminal {
        int width;
        int height;
        int margin;
    };

    
    bool terminal_changed(Terminal& _terminal_size, Terminal& _last_terminal_size);

}
