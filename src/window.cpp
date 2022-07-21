//
// Created by jebbin on 30/03/21.
//
#include <iostream>
#include <utility>
#include "window.h"
#include <SDL2/SDL_mixer.h>

SDL_Renderer *Window::renderer = nullptr;

Window::Window(std::string title, int width, int height) :
        title(std::move(title)), width(width), height(height) {
    closed = !init();
}

Window::~Window() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    TTF_Quit();
}

bool Window::init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Failed to initialize SDL\n";
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) < 0) {
        std::cerr << "Failed to initialize audio\n";
    }

    // Amount of channels (Max amount of sounds playing at the same time)
    Mix_AllocateChannels(12);

    if (TTF_Init() == -1) {
        std::cerr << "Failed to initialize SDL_TTF\n";
        return false;
    }

    window = SDL_CreateWindow(
            title.c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_RESIZABLE
    );

    if (window == nullptr) {
        std::cerr << "Failed to create Window\n";
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cerr << "Failed to create Renderer\n";
    }

    return true;
}

void Window::pollEvents() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                closed = true;
                break;
            case SDL_TEXTINPUT:
                std::cout << event.text.text << "\n";
                break;
            default:
                break;
        }
    }
}

void Window::clear() const {
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 82, 82, 82, 255);
    SDL_RenderClear(renderer);
}

void Window::close() {
    closed = true;
}