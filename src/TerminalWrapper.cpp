//TerminalWrapper.cpp

#include "TerminalWrapper.hpp"


void TerminalWrapper::init() {
    tcgetattr(STDIN_FILENO, &original);
    settings = original;
    settings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &settings);
}

void TerminalWrapper::restore() {
    tcsetattr(STDIN_FILENO, TCSANOW, &original);
}

TerminalWrapper::~TerminalWrapper() {
    restore();
}
