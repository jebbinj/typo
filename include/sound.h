//
// Created by jebbin on 12/04/21.
//
#pragma once

#include <SDL2/SDL_mixer.h>
#include <string>
#include <memory>

class sound {
public:
    sound(const std::string &path, int volume);

    void play() const;

    void play(int times) const;

    void set_volume(int volume) const;

private:
    std::unique_ptr<Mix_Chunk, void (*)(Mix_Chunk *)> chunk;
};


