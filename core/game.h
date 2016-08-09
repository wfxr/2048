#pragma once

#include <functional>

#include "board.h"
#include "subject.h"


class Game : public Subject {
public:
    Game(int rows, int cols) : _board(rows, cols), _score(0) {}
    void reset();

    const Board& get_board() const { return _board; }

    bool game_over() const { return !_board.can_move(); }
    int score() const { return _score; }

    void move_up();
    void move_down();
    void move_left();
    void move_right();
private:
    Board _board;
    int _score;
};
