//
// Created by jebbin on 30/03/21.
//
#pragma once

#include <string>
#include <SDL2/SDL.h>

class Window {
public:
    Window(std::string title,
           int width,
           int height
    );

    ~Window();

    inline bool isClosed() const {
        return closed;
    }

    void pollEvents();

private:
    std::string title;
    int width = 800;
    int height = 600;
    bool closed = false;

    bool init();

    SDL_Window *window = nullptr;
};


