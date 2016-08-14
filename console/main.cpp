#include "console2048.h"

int main() {
    auto game = Console2048::create(4, 4);
    game->start();
}
