//
// Created by jebbin on 03/04/21.
//
#pragma once

#include <SDL2/SDL_ttf.h>
#include <string>

class TextSprite {
public:
    TextSprite(SDL_Renderer *renderer,
               const std::string &text,
               const SDL_Color &color);

    ~TextSprite();

    void display(int x, int y,
                 SDL_Renderer *renderer) const;

    static TTF_Font *font;

    static void setFont(const std::string &path, int size);

    void update_text(const std::string &text, SDL_Renderer *renderer);

protected:
    std::string str;

    mutable SDL_Rect text_rect{};

private:
    SDL_Texture *text_texture = nullptr;
};


