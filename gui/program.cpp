#include <iostream>
#include <memory>

using std::make_shared;

#include "console2048.h"

int main() {
    auto game = make_shared<Console2048>(4, 4);
    game->start();
}

