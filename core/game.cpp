#include "game.h"



void Game::start()
{
    _board.initialize();
    notify();
}

void Game::move_up() {
    _board.move_up();
    notify();
}

void Game::move_down() {
    _board.move_down();
    notify();
}

void Game::move_left() {
    _board.move_left();
    notify();
}

void Game::move_right() {
    _board.move_right();
    notify();
}
