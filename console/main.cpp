#include <iostream>
#include <memory>

using std::make_shared;

#include "console2048.h"

int main() {
    auto game = Console2048::create(8, 6);
    game->start();
}

