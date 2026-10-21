//CybrUtil.cpp

#include <iostream>

#include "CybrUtil.hpp"

namespace CybrUtil {
    
    //clear screen
    void cls() {
        std::cout << "\033[2J";
    }

    void debug(std::string text, int row) {
        std::string out;
        if (! row) {
            out = "\033[40;1H" + text;
        }
        else {
            out = "\033[" + std::to_string(40 + row) + ";1H" + text;
        }
        std::cout << out << std::flush;
    }
}
