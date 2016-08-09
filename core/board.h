#pragma once

#include <vector>
#include <utility>


enum class Direction;

class Board {
public:
    Board(int rows, int cols)
        : _rows(rows), _cols(cols), _board(rows, std::vector<int>(cols)) {}

    void set(int i, int j, int val) { _board[i][j] = val; }
    int get(int i, int j) const { return _board[i][j]; }

    int rows() const { return _rows; }
    int cols() const { return _cols; }

    void reset();
    void random_arise();

    int move(Direction direction);

    int blank_count() const;
    bool can_move() const;

private:
    std::pair<bool, int> move_left(int i, int j);
    std::pair<bool, int> move_right(int i, int j);
    std::pair<bool, int> move_up(int i, int j);
    std::pair<bool, int> move_down(int i, int j);

    static int& merge(int & to, int & from);
    static int random(int min, int max);

    int _rows;
    int _cols;
    std::vector<std::vector<int>> _board;
};
