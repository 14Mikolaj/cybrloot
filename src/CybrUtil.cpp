//CybrUtil.cpp

#include <iostream>

#include "CybrUtil.hpp"


namespace CybrUtil {
    
    //clear screen
    void cls() {
        std::cout << "\033[2J";
    }
}
