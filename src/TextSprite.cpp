//
// Created by jebbin on 03/04/21.
//

#include "TextSprite.h"
#include <iostream>

TTF_Font *TextSprite::font = nullptr;

TextSprite::TextSprite(SDL_Renderer *renderer, const std::string &text,
                       const SDL_Color &color) {
    text_texture = loadFont(renderer, text, color);
    str = text;
    SDL_QueryTexture(text_texture, nullptr, nullptr, &text_rect.w, &text_rect.h);
}

TextSprite::~TextSprite() {
    SDL_DestroyTexture(text_texture);
}

void TextSprite::display(int x, int y, SDL_Renderer *renderer) const {
    text_rect.x = x;
    text_rect.y = y;
    if (SDL_RenderCopy(renderer, text_texture, nullptr, &text_rect) < 0) {
        std::cerr << "RenderCopy error: " << SDL_GetError() << std::endl;
    }
}

SDL_Texture *
TextSprite::loadFont(SDL_Renderer *renderer, const std::string &text,
                     const SDL_Color &color) {
    auto text_sprite_surface = TTF_RenderUTF8_Solid(font, text.c_str(), color);
    if (!text_sprite_surface) {
        std::cerr << "Failed to create text sprite surface\n";
    }
    auto text_sprite_texture = SDL_CreateTextureFromSurface(renderer, text_sprite_surface);
    if (!text_sprite_texture) {
        std::cerr << "Failed to create a text sprite texture\n";
    }
    SDL_FreeSurface(text_sprite_surface);
    return text_sprite_texture;
}

void TextSprite::setFont(const std::string &path, int size) {
    font = TTF_OpenFont(path.c_str(), size);
    if(!font) {
        std::cerr << "Failed to load the font\n";
    }
}