//
// Created by jebbin on 03/04/21.
//

#include "TextSprite.h"
#include <iostream>

TextSprite::TextSprite(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &text,
                       const SDL_Color &color) {
    text_texture = loadFont(renderer, font_path, font_size, text, color);
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
TextSprite::loadFont(SDL_Renderer *renderer, const std::string &font_path, int font_size, const std::string &text,
                     const SDL_Color &color) {
    TTF_Font *font = TTF_OpenFont(font_path.c_str(), font_size);
    if (!font) {
        std::cerr << "Failed to load font.\n";
    }
    auto text_sprite_surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!text_sprite_surface) {
        std::cerr << "Failed to create text sprite surface\n";
    }
    auto text_sprite_texture = SDL_CreateTextureFromSurface(renderer, text_sprite_surface);
    if (!text_sprite_texture) {
        std::cerr << "Failed to create a text sprite texture \n";
    }
    SDL_FreeSurface(text_sprite_surface);
    return text_sprite_texture;
}