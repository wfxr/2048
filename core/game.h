#pragma once

#include <functional>

#include "board.h"
#include "subject.h"
#include "direction.h"


class Game : public Subject {
public:
    Game(int rows, int cols) : _board(rows, cols) {}
    void start();

    const Board& get_board() const { return _board; }

    bool game_over() const { return !_board.can_move(); }

    void set_input_source(std::function<Direction(void)> source) {
        _get_direction = source;
    }
private:
    std::function<Direction(void)> _get_direction;
    int _score = 0;
    Board _board;
};
