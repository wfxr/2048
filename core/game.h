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

    void move_up();
    void move_down();
    void move_left();
    void move_right();
private:
    Board _board;
};
