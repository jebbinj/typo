//
// Created by jebbin on 10/04/21.
//

#include "ScatteredSprite.h"
#include "window.h"

const SDL_Color redBG = {255, 75, 60, 0};
const SDL_Color greenBG = {61, 255, 126, 0};

ScatteredSprite::ScatteredSprite(SDL_Renderer *renderer, const std::string &text, const SDL_Color &color) : TextSprite(
        renderer, text, color) {
    length = text.length();
    index = -1;
}

void ScatteredSprite::char_in(const char c) {
    if (index + 1 < str.length()) {
        ++index;
        buffer.push_back(c);
    }
}

void ScatteredSprite::del_char() {
    if (index < 0) {
        return;
    }
    if (!index - 1 == -1) {
        --index;
    } else {
        index = -1;
    }
    buffer.pop_back();
}

void ScatteredSprite::render_cursor() {
    int w;
    TTF_SizeUTF8(TextSprite::font, str.substr(0, index < 0 ? 1 : index + 2).c_str(), &w, nullptr);
    SDL_Rect cursorRect = {text_rect.x, text_rect.y, w, text_rect.h};
    SDL_SetRenderDrawColor(Window::renderer, 54, 54, 54, 255);
    SDL_RenderFillRect(Window::renderer, &cursorRect);
    SDL_Color bgColor = validate_buffer() ? greenBG : redBG;
    TTF_SizeUTF8(TextSprite::font, str.substr(0, index < 0 ? 0 : index + 1).c_str(), &w, nullptr);
    SDL_Rect stateRect = {text_rect.x, text_rect.y, w, text_rect.h};
    SDL_SetRenderDrawColor(Window::renderer, bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    SDL_RenderFillRect(Window::renderer, &stateRect);
}

bool ScatteredSprite::validate_buffer() {
    return (buffer == str.substr(0, index < 0 ? 0 : index + 1));
}

unsigned short int ScatteredSprite::validate() {
    unsigned short int errorChars = index + 1;
    for (int i = 0; i <= index; i++) {
        if (str[i] == buffer[i]) {
            errorChars--;
        }
    }
    return errorChars;
}
