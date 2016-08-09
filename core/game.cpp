#include "game.h"
#include "direction.h"

void Game::reset()
{
    _board.reset();
    notify();
}

void Game::move_up() {
    _score += _board.move(Direction::Up);
    notify();
}

void Game::move_down() {
    _score += _board.move(Direction::Down);
    notify();
}

void Game::move_left() {
    _score += _board.move(Direction::Left);
    notify();
}

void Game::move_right() {
    _score += _board.move(Direction::Right);
    notify();
}
