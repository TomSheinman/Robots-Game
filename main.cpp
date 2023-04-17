#include "Game.h"

int main() {

    Game game;
    if (!game.play())
        return 1;
    return 0;
}
