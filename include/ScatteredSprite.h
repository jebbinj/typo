//
// Created by jebbin on 10/04/21.
//

#pragma once

#include "TextSprite.h"

class ScatteredSprite : public TextSprite {
public:
    ScatteredSprite(SDL_Renderer *renderer, const std::string &text, const SDL_Color &color);

    void char_in(char c);

    void del_char();

    bool validate_buffer();

    void render_cursor();

private:
    int index;
    unsigned short length;
    std::string buffer;
};


