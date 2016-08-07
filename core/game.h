#pragma once

#include <functional>

#include "board.h"
#include "subject.h"

enum class Direction {
    Up,
    Down,
    Left,
    Right
};

class Game : public Subject {
public:
    Game(int rows, int cols) : _board(rows, cols) {}
    void start() {
        _board.init();
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

    const Board& get_board() const {
        return _board;
    }

    bool game_over() const {
        return !_board.can_move();
    }

    void set_input_source(std::function<Direction(void)> source) {
        _get_direction = source;
    }
private:
    std::function<Direction(void)> _get_direction;
    int _score = 0;
    Board _board;
};
