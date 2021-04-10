#include "window.h"
#include "TextSprite.h"
#include "menu.h"
#include "scattered.h"

int main() {

    Window window("TYPO", 1280, 720);
    Menu menu(&window, {"START", "OPTIONS", "QUIT"});
    TextSprite::setFont("./../res/open-sans.ttf", 24);
    Game *game;

    int selection = menu.display_menu();
    if (selection == 2) window.close();

    game = new Scattered(&window, 10 - 9);
    game->start();

    delete game;

    return 0;
}
