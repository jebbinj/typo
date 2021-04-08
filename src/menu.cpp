//
// Created by jebbin on 05/04/21.
//
#include "menu.h"
#include "TextSprite.h"
#include <iostream>
#include <utility>

Menu::Menu(Window *window, std::vector<std::string> options) {
    this->options = std::move(options);
    this->window = window;
    selection = 0;
}

int Menu::poll_events() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                window->close();
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_j:
                        selection + 1 < options.size() && ++selection;
                        break;
                    case SDLK_k:
                        selection - 1 >= 0 && --selection;
                        break;
                    case SDLK_RETURN:
                        return selection;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
    return -1;
}

int Menu::display_menu() {
    if (options.empty()) {
        std::cerr << "Options member empty!" << std::endl;
    }

    while (!window->isClosed()) {
        window->clear();

        int i = 0;
        int w, h, optionWidth, optionHeight;
        SDL_GetWindowSize(window->get_window(), &w, &h);
        for (std::string &option : options) {
            TextSprite menuItem(Window::renderer, i == selection ? "- " + option + " -" : option, {255, 255, 255, 255});
            TTF_SizeText(TextSprite::font,
                         (i == selection ? "- " + option + " -" : option).c_str(),
                         &optionWidth,
                         &optionHeight);
            menuItem.display(w / 2 - (optionWidth / 2), (h / 2 - optionHeight) + (i * 25), Window::renderer);
            ++i;
        }

        int e = poll_events();

        if (e != -1) {
            return e;
        }
    }
}
