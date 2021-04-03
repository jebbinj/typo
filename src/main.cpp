#include "window.h"
#include "TextSprite.h"

int main() {

    Window window("TYPO", 800, 600);
    TextSprite t_sprite(Window::renderer, "./../res/open-sans.ttf", 24, "TYPO", {255, 255, 255, 255});

    while (!window.isClosed()) {
        window.pollEvents();
        t_sprite.display(200, 200, Window::renderer);
        window.clear();
    }

    return 0;
}
