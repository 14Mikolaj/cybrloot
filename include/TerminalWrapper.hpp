//TerminalWrapper.hpp

#pragma once

#include <termios.h>
#include <unistd.h>

#include "CybrUtil.hpp"


class TerminalWrapper {
public:
    void init();
    void restore();
    ~TerminalWrapper();
    char read_input();
    CybrUtil::action parse_input();
private:

    termios original;
    termios settings;
};
