#include "game.h"



void Game::start()
{
    _board.initialize();
    notify();

    while (!game_over()) {
        switch (_get_direction()) {
        case Direction::Up:
            _board.move_up();
            break;
        case Direction::Down:
            _board.move_down();
            break;
        case Direction::Left:
            _board.move_left();
            break;
        case Direction::Right:
            _board.move_right();
            break;
        }

        notify();
    }
}
