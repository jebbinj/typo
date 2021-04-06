#include "window.h"
#include "TextSprite.h"
#include "menu.h"

int main() {

    Window window("TYPO", 800, 600);
    Menu menu(&window, {"START", "OPTIONS", "QUIT"});
    TextSprite::setFont("./../res/open-sans.ttf", 24);

    int selection = menu.display_menu();
    if (selection == 2) window.close();

    while (!window.isClosed()) {
        window.pollEvents();
        // t_sprite.display(rand() % 700 + 600, rand() % 700 + 400, Window::renderer);

        window.clear();
    }

    return 0;
}
