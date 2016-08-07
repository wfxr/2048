#pragma once

#include <algorithm>
#include <random>
#include <utility>
#include <vector>

class Board {
public:
    Board(int rows, int cols)
        : _rows(rows), _cols(cols), _board(rows, std::vector<int>(cols)) {}

    void set(int i, int j, int val) { _board[i][j] = val; }
    int get(int i, int j) const { return _board[i][j]; }

    int rows() const { return _rows; }
    int cols() const { return _cols; }

    void init() {
        random_arise();
        random_arise();
    }

    int blanks_count() const {
        auto num = 0;
        for (const auto &row : _board)
            num += std::count(row.begin(), row.end(), 0);
        return num;
    }

    void random_arise() {
        auto blanksCount = blanks_count();
        if (blanksCount == 0) return;

        auto dest = random(1, blanksCount);
        int curr = 0;
        for (auto &row : _board)
            for (auto &cell : row)
                if (cell == 0 && ++curr == dest) {
                        cell = 2;
                        return;
                    }
    }

    void move_left() {
        auto moved = false;
        for (int i = 0; i < _rows; ++i)
            for (int j = 0; j < _cols; ++j)
                if (_board[i][j]) moved |= move_left(i, j);
        if (moved) random_arise();
    }

    void move_right() {
        auto moved = false;
        for (int i = 0; i < _rows; ++i)
            for (int j = _cols - 1; j >= 0; --j)
                if (_board[i][j]) moved |= move_right(i, j);
        if (moved) random_arise();
    }

    void move_up() {
        auto moved = false;
        for (int i = 0; i < _rows; ++i)
            for (int j = 0; j < _cols; ++j)
                if (_board[i][j]) moved |= move_up(i, j);
        if (moved) random_arise();
    }

    void move_down() {
        auto moved = false;
        for (int i = _rows - 1; i >= 0; --i)
            for (int j = 0; j < _cols; ++j)
                if (_board[i][j]) moved |= move_down(i, j);
        if (moved) random_arise();
    }

    bool can_move() const {
        if (blanks_count()) return true;
        for (int i = 0; i < _rows - 1; ++i)
            for (int j = 0; j < _cols - 2; ++j)
                if (_board[i][j] == _board[i][j + 1]) return true;

        for (int j = 0; j < _cols - 1; ++j)
            for (int i = 0; i < _rows - 2; ++i)
                if (_board[i][j] == _board[i + 1][j]) return true;
        return false;
    }

private:
    bool move_left(int i, int j) {
        auto moved = false;
        for (; j > 0 && _board[i][j - 1] == 0; --j) {
            std::swap(_board[i][j], _board[i][j - 1]);
            moved = true;
        }
        if (j > 0 && _board[i][j - 1] == _board[i][j]) {
            merge(_board[i][j], _board[i][j - 1]);
            moved = true;
        }
        return moved;
    }

    bool move_right(int i, int j) {
        auto moved = false;
        for (; j < _cols - 1 && _board[i][j + 1] == 0; ++j) {
            std::swap(_board[i][j], _board[i][j + 1]);
            moved = true;
        }
        if (j < _cols - 1 && _board[i][j + 1] == _board[i][j]) {
            merge(_board[i][j], _board[i][j + 1]);
            moved = true;
        }
        return moved;
    }

    bool move_up(int i, int j) {
        auto moved = false;
        for (; i > 0 && _board[i - 1][j] == 0; --i) {
            std::swap(_board[i][j], _board[i - 1][j]);
            moved = true;
        }
        if (i > 0 && _board[i - 1][j] == _board[i][j]) {
            merge(_board[i][j], _board[i - 1][j]);
            moved = true;
        }
        return moved;
    }

    bool move_down(int i, int j) {
        auto moved = false;
        for (; i < _rows - 1 && _board[i + 1][j] == 0; ++i) {
            std::swap(_board[i][j], _board[i + 1][j]);
            moved = true;
        }
        if (i < _rows - 1 && _board[i + 1][j] == _board[i][j]) {
            merge(_board[i][j], _board[i + 1][j]);
            moved = true;
        }
        return moved;
    }

    void merge(int &src, int &dest) {
        dest += src;
        src = 0;
    }

    int random(int min, int max) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    int _rows;
    int _cols;
    std::vector<std::vector<int>> _board;
};
