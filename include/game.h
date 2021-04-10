//
// Created by jebbin on 06/04/21.
//
#pragma once

#include "window.h"

enum GameState {
    RUNNING,
    PAUSED,
    FINISHED
};

class Game {
public:
    explicit Game(Window *window);

    ~Game();

    mutable GameState game_state;

    virtual void start() = 0;

    virtual void pause() = 0;

protected:
    Window *window;
    mutable unsigned int wpm{};
};