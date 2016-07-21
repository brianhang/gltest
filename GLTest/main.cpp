#include "game.h"
#include <cstdlib>

int main(int argc, char *argv[]) {
    Game game;

    if (!game.initialize()) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}