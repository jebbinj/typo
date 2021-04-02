//
// Created by jebbin on 30/03/21.
//
#include <iostream>
#include <utility>
#include "window.h"

Window::Window(std::string title, int width, int height) :
        title(std::move(title)), width(width), height(height) {
    if (!init()) {
        closed = true;
    }
}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

bool Window::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL\n";
        return false;
    }

    window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_RESIZABLE
    );

    if (window == nullptr) {
        std::cerr << "Failed to create Window\n";
    }

    return true;
}

void Window::pollEvents() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                closed = true;
                break;
            default:
                break;
        }
    }
}