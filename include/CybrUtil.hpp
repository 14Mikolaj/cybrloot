//CybrUtil.hpp

#pragma once

#include <string>

namespace CybrUtil {
    
    void cls(); 
    void debug(std::string text, int row = 0);
    
    struct game_data {
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
    };

    std::string a_to_string(action a);
    

}
