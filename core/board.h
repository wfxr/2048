#pragma once

#include <vector>

class Board {
public:
    Board(int rows, int cols)
        : _rows(rows), _cols(cols), _board(rows, std::vector<int>(cols)) {}

    void set(int i, int j, int val) { _board[i][j] = val; }
    int get(int i, int j) const { return _board[i][j]; }

    int rows() const { return _rows; }
    int cols() const { return _cols; }

    void initialize();
    void random_arise();

    void move_left();
    void move_right();
    void move_up();
    void move_down();

    int blank_count() const;
    bool can_move() const;

private:
    bool move_left(int i, int j);
    bool move_right(int i, int j);
    bool move_up(int i, int j);
    bool move_down(int i, int j);

    static void merge(int &src, int &dest);
    static int random(int min, int max);

    int _rows;
    int _cols;
    std::vector<std::vector<int>> _board;
};
