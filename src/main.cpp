//main.cpp

#include <iostream>

#include "Scene.hpp"
#include "Panel.hpp"
#include "CybrUtil.hpp"

using namespace CybrUtil;

struct game_data {
    int data;
    int money;
};

int main() {
    Scene dashboard("dashboard");
    Panel panel_data(50,20,20,8, "DATA", "thick");
    panel_data.add_element(std::make_unique<Text>(0, 0, "DATA: 0"));
    dashboard.add_panel(std::move(panel_data));
    cls();
    dashboard.draw();
    std::cout << "\nHello World!\n";
    return 0;
}

