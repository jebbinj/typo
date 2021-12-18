//
// Created by jebbin on 07/04/21.
//

#pragma once

#include "game.h"
#include "sound.h"
#include "ScatteredSprite.h"

struct Sprite {
    ScatteredSprite *t;
    int x;
    int y;
    int w;
    int h;
    unsigned int startStamp;
};

class Scattered : public Game {
public:
    Scattered(Window *window, unsigned short difficulty);

    ~Scattered();

    void start() override;
    void pause() override;

private:
    unsigned short difficulty;
    unsigned poll_events();
    sound *keystroke;
    sound *error;
    static void render_bar(int x, int y, int w, float Percent, SDL_Color FGColor, SDL_Color BGColor);
};

