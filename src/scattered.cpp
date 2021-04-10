//
// Created by jebbin on 07/04/21.
//

#include "scattered.h"
#include "ScatteredSprite.h"
#include <ctime>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <SDL2/SDL.h>

Scattered::Scattered(Window *window, unsigned short difficulty) :
        Game(window),
        difficulty(difficulty) {}

Scattered::~Scattered() = default;

void Scattered::start() {
    int w, h, spriteW, spriteH, xRand, yRand;
    SDL_GetWindowSize(window->get_window(), &w, &h);
    float percent = 1;

    std::vector<Sprite> sprites;

    std::srand(std::time(nullptr));

    for (int k = 0; k < 100; k++) {
        TTF_SizeUTF8(TextSprite::font, ("Random " + std::to_string(k)).c_str(), &spriteW, &spriteH);
        xRand = std::rand() % w;
        if (xRand + spriteW > w) {
            xRand -= (xRand + spriteW) - w;
            xRand -= 20;
        }
        yRand = std::rand() % h;
        if (yRand + spriteH > h) {
            yRand -= (yRand + spriteH) - h;
            yRand -= 25;
        }
        struct Sprite s = {new ScatteredSprite(Window::renderer,
                                               "Random " + std::to_string(k),
                                               {255, 255, 255, 255}),
                           xRand, yRand, spriteW, spriteH, 0};
        sprites.push_back(s);
    }

    std::vector<Sprite>::iterator itr;
    itr = sprites.begin();
    game_state = RUNNING;
    while (!window->isClosed() && game_state == RUNNING && itr < sprites.end()) {
        window->clear();
        if (itr->startStamp == 0) {
            itr->startStamp = SDL_GetTicks();
        }
        itr->t->display(itr->x, itr->y, Window::renderer);
        render_bar(itr->x + itr->w, itr->y + itr->h, -1 * itr->w, percent,
                   {255, 255, 255, 255},
                   {0, 0, 0, 0});
        poll_events();

        if ((float) (SDL_GetTicks() - itr->startStamp) >= (difficulty * 1000.0)) {
            itr++;
            percent = 1;
        } else {
            percent = 1 - (float) (SDL_GetTicks() - itr->startStamp) / (difficulty * 1000.0);
        }
    }
}

void Scattered::pause() {
    game_state = PAUSED;
}

void Scattered::poll_events() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                window->close();
                break;
            default:
                break;
        }
    }
}

void Scattered::render_bar(int x, int y, int w, float Percent, SDL_Color FGColor, SDL_Color BGColor) {
    Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
    SDL_Color old;
    SDL_GetRenderDrawColor(Window::renderer, &old.r, &old.g, &old.g, &old.a);
    SDL_Rect bgRect = {x, y, w, 3};
    SDL_SetRenderDrawColor(Window::renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
    SDL_RenderFillRect(Window::renderer, &bgRect);
    SDL_SetRenderDrawColor(Window::renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
    int pw = (int) ((float) w * Percent);
    int px = x + (w - pw);
    SDL_Rect fgRect = {px, y, pw, 3};
    SDL_RenderFillRect(Window::renderer, &fgRect);
    SDL_SetRenderDrawColor(Window::renderer, old.r, old.g, old.b, old.a);
}