//
// Created by jebbin on 12/04/21.
//

#include "sound.h"
#include <iostream>

sound::sound(const std::string &path, int volume) : chunk(Mix_LoadWAV(path.c_str()), Mix_FreeChunk) {
    if (!chunk) {
        std::cerr << "Failed to load wav file: " << path;
    }
    Mix_VolumeChunk(chunk.get(), volume);
}

void sound::play() const {
    Mix_PlayChannel(-1, chunk.get(), 0);
}

void sound::play(int times) const {
    Mix_PlayChannel(-1, chunk.get(), times - 1);
}

void sound::set_volume(int volume) const {
    Mix_VolumeChunk(chunk.get(), volume);
}