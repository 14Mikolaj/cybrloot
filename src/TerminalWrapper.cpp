//TerminalWrapper.cpp

#include <unistd.h>

#include "TerminalWrapper.hpp"

using namespace CybrUtil;

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

char TerminalWrapper::read_input() {
    char key;
    if (read(STDIN_FILENO, &key, 1) != 1) {
        return '\0';
    }
    return key;
}

action TerminalWrapper::parse_input() {
    char key = read_input();
    if (key == '\033') {
        char second = read_input();
        if(second == '[') {
            char third = read_input();
            switch(third) {
                case 'A':
                    return action::up;
                case 'B':
                    return action::down;
                case 'C':
                    return action::right;case'D':return action::left;}}return action::none;}
    switch (key){
        case 'h':
        case 'H':
            return action::left;
        case 'j':
        case 'J':
            return action::down;
        case 'k':
        case 'K':
            return action::up;
        case 'l':
        case 'L':
            return action::right;
        case 'q':
        case 'Q':
            return action::quit;
        case '\r':
        case '\n':
            return action::select;
    }
    return action::none;
}
