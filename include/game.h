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
    Game(Window *window);

    ~Game();

    GameState game_state;

    virtual void start() = 0;

    virtual void pause() = 0;

protected:
    Window *window;
    unsigned int wpm;


};