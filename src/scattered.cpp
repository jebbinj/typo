//
// Created by jebbin on 07/04/21.
//

#include "scattered.h"
#include "ScatteredSprite.h"
#include "wordlist.h"
#include <ctime>
#include <string>
#include <cstdlib>
#include <vector>
#include <SDL2/SDL.h>

Scattered::Scattered(Window *window, unsigned short difficulty) :
        Game(window),
        difficulty(difficulty) {
    keystroke = new sound("./../res/keystroke.wav", 10);
    error = new sound("./../res/error.wav", 15);
}

Scattered::~Scattered() = default;

void Scattered::start() {
    int w, h, spriteW, spriteH, xRand, yRand;
    std::string word, score{"0 WPM"};
    unsigned int sym, startTime{SDL_GetTicks()}, typedChars{0}, errorChars{0};
    float percent = 1;
    TextSprite scoreText(Window::renderer, score, {255, 255, 255});
    std::vector<Sprite> sprites;

    SDL_GetWindowSize(window->get_window(), &w, &h);

    std::srand(std::time(nullptr));

    for (int k = 0; k < 1000; k++) {
        word = words[std::rand() % words.size()];
        TTF_SizeUTF8(TextSprite::font, word.c_str(), &spriteW, &spriteH);
        xRand = std::rand() % w;
        if (xRand + spriteW > w) {
            xRand -= (xRand + spriteW) - w;
            xRand -= 20;
        }
        yRand = std::rand() % h;
        if (yRand + spriteH > h) {
            yRand -= (yRand + spriteH) - h;
            yRand -= 30;
        }
        struct Sprite s = {new ScatteredSprite(Window::renderer,
                                               word,
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
        scoreText.update_text(std::to_string(wpm) + " WPM", Window::renderer);
        scoreText.display(w - 100, 10, Window::renderer);
        itr->t->render_cursor();
        itr->t->display(itr->x, itr->y, Window::renderer);
        (itr + 1)->t->display((itr + 1)->x, (itr + 1)->y, Window::renderer);
        render_bar(itr->x + itr->w, itr->y + itr->h, -1 * itr->w, percent,
                   {255, 255, 255, 255},
                   {0, 0, 0, 0});

        sym = poll_events();

        if (sym == SDLK_SPACE || sym == SDLK_RETURN || sym == SDLK_RETURN2) {
            unsigned short int errors = itr->t->validate();
            if (errors) {
                errorChars += errors;
                error->play();
            }
            wpm = ((typedChars / 5) - errorChars * 1.0) / (((double) (SDL_GetTicks() - startTime) / 1000) / 60);
            itr++;
            percent = 1;
        } else {
            if (sym != 0) {
                if (sym == 999) {
                    itr->t->del_char();
                } else {
                    itr->t->char_in((char) sym);
                    if (!itr->t->validate_buffer())
                        error->play();
                    else
                        wpm = ((++typedChars / 5) - errorChars * 1.0) /
                              (((double) (SDL_GetTicks() - startTime) / 1000) / 60);
                }
            }
            if ((float) (SDL_GetTicks() - itr->startStamp) >= (difficulty * 1000.0)) {
                if (itr->t->validate())
                    error->play();
                itr++;
                percent = 1;
            } else {
                percent = 1 - (float) (SDL_GetTicks() - itr->startStamp) / (difficulty * 1000.0);
            }
        }
    }
}

void Scattered::pause() {
    game_state = PAUSED;
}

unsigned int Scattered::poll_events() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                window->close();
                break;
            case SDL_KEYDOWN:
                keystroke->play();
                if (event.key.keysym.sym == SDLK_BACKSPACE)
                    return 999;
                else if (event.key.keysym.sym == SDLK_ESCAPE) {
                    game_state = PAUSED;
                    break;
                }
                return event.key.keysym.sym;
            default:
                return 0;
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