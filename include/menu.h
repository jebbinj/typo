//
// Created by jebbin on 05/04/21.
//
#pragma once

#include "window.h"
#include <string>
#include <vector>
#include <SDL2/SDL.h>

class Menu {
public:
    Menu(Window *window, std::vector<std::string> options);

    int display_menu();

private:
    std::vector<std::string> options;
    int selection;
    Window *window;

    int poll_events();
};