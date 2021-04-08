//
// Created by jebbin on 07/04/21.
//

#include "scattered.h"
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>

Scattered::Scattered(Window *window, unsigned short difficulty) :
        Game(window),
        difficulty(difficulty) {}

Scattered::~Scattered() = default;

void Scattered::start() {
    int w, h;
    SDL_GetWindowSize(window->get_window(), &w, &h);
    float i = 1;

    std::vector<Sprite> sprites;

    for (int i = 0; i < 10; i++) {
        struct Sprite s = {new TextSprite(Window::renderer,
                                          "Random " + std::to_string(i),
                                          {255, 255, 255, 255}),
                           rand() % w, rand() % h};
        sprites.push_back(s);
    }

    std::vector<Sprite>::iterator itr;
    itr = sprites.begin();
    game_state = RUNNING;
    while (!window->isClosed() && game_state == RUNNING && itr < sprites.end()) {
        window->clear();
        itr->t->display(itr->x, itr->y, Window::renderer);

        render_bar(itr->x + 100, itr->y + 30, -100, 3, i,
                   {255, 255, 255, 255},
                   {0, 0, 0, 0});
        poll_events();
        i -= 0.0001;
        if (i <= 0) {
            itr++;
            i = 1;
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

void Scattered::render_bar(int x, int y, int w, int h, float Percent, SDL_Color FGColor, SDL_Color BGColor) {
    Percent = Percent > 1.f ? 1.f : Percent < 0.f ? 0.f : Percent;
    SDL_Color old;
    SDL_GetRenderDrawColor(Window::renderer, &old.r, &old.g, &old.g, &old.a);
    SDL_Rect bgRect = {x, y, w, h};
    SDL_SetRenderDrawColor(Window::renderer, BGColor.r, BGColor.g, BGColor.b, BGColor.a);
    SDL_RenderFillRect(Window::renderer, &bgRect);
    SDL_SetRenderDrawColor(Window::renderer, FGColor.r, FGColor.g, FGColor.b, FGColor.a);
    int pw = (int) ((float) w * Percent);
    int px = x + (w - pw);
    SDL_Rect fgRect = {px, y, pw, h};
    SDL_RenderFillRect(Window::renderer, &fgRect);
    SDL_SetRenderDrawColor(Window::renderer, old.r, old.g, old.b, old.a);
}