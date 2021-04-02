#include "window.h"

int main() {

    Window window("TYPO", 800, 600);

    while (!window.isClosed()) {
        window.pollEvents();
    }

    return 0;
}
