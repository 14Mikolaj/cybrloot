//TerminalWrapper.hpp

#pragma once

#include <iostream>
#include <termios.h>
#include <unistd.h>


class TerminalWrapper {
public:
    void init();
    void restore();
    ~TerminalWrapper();
private:

    termios original;
    termios settings;
};
