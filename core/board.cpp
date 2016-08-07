#include "board.h"
#include <random>

using std::count;
using std::swap;

void Board::initialize()
{
    random_arise();
    random_arise();
}

int Board::blank_count() const
{
    auto num = 0;
    for (const auto &row : _board)
        num += count(row.begin(), row.end(), 0);
    return num;
}

void Board::random_arise()
{
    auto blanksCount = blank_count();
    if (blanksCount == 0) return;

    auto dest = random(1, blanksCount);
    auto curr = 0;
    for (auto &row : _board)
        for (auto &cell : row)
            if (cell == 0 && ++curr == dest) {
                cell = 2;
                return;
            }
}

void Board::move_left()
{
    auto moved = false;
    for (auto i = 0; i < _rows; ++i)
        for (auto j = 0; j < _cols; ++j)
            if (_board[i][j]) moved |= move_left(i, j);
    if (moved) random_arise();
}

bool Board::move_left(int i, int j)
{
    auto moved = false;
    for (; j > 0 && _board[i][j - 1] == 0; --j) {
        swap(_board[i][j], _board[i][j - 1]);
        moved = true;
    }
    if (j > 0 && _board[i][j - 1] == _board[i][j]) {
        merge(_board[i][j], _board[i][j - 1]);
        moved = true;
    }
    return moved;
}

void Board::move_right()
{
    auto moved = false;
    for (auto i = 0; i < _rows; ++i)
        for (auto j = _cols - 1; j >= 0; --j)
            if (_board[i][j]) moved |= move_right(i, j);
    if (moved) random_arise();
}

bool Board::move_right(int i, int j)
{
    auto moved = false;
    for (; j < _cols - 1 && _board[i][j + 1] == 0; ++j) {
        swap(_board[i][j], _board[i][j + 1]);
        moved = true;
    }
    if (j < _cols - 1 && _board[i][j + 1] == _board[i][j]) {
        merge(_board[i][j], _board[i][j + 1]);
        moved = true;
    }
    return moved;
}

void Board::move_up()
{
    auto moved = false;
    for (auto i = 0; i < _rows; ++i)
        for (auto j = 0; j < _cols; ++j)
            if (_board[i][j]) moved |= move_up(i, j);
    if (moved) random_arise();
}

bool Board::move_up(int i, int j)
{
    auto moved = false;
    for (; i > 0 && _board[i - 1][j] == 0; --i) {
        swap(_board[i][j], _board[i - 1][j]);
        moved = true;
    }
    if (i > 0 && _board[i - 1][j] == _board[i][j]) {
        merge(_board[i][j], _board[i - 1][j]);
        moved = true;
    }
    return moved;
}

void Board::move_down()
{
    auto moved = false;
    for (auto i = _rows - 1; i >= 0; --i)
        for (auto j = 0; j < _cols; ++j)
            if (_board[i][j]) moved |= move_down(i, j);
    if (moved) random_arise();
}

bool Board::move_down(int i, int j)
{
    auto moved = false;
    for (; i < _rows - 1 && _board[i + 1][j] == 0; ++i) {
        swap(_board[i][j], _board[i + 1][j]);
        moved = true;
    }
    if (i < _rows - 1 && _board[i + 1][j] == _board[i][j]) {
        merge(_board[i][j], _board[i + 1][j]);
        moved = true;
    }
    return moved;
}

void Board::merge(int &src, int &dest)
{
    dest += src;
    src = 0;
}

int Board::random(int min, int max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

bool Board::can_move() const
{
    if (blank_count()) return true;
    for (auto i = 0; i < _rows - 1; ++i)
        for (auto j = 0; j < _cols - 2; ++j)
            if (_board[i][j] == _board[i][j + 1]) return true;

    for (auto j = 0; j < _cols - 1; ++j)
        for (auto i = 0; i < _rows - 2; ++i)
            if (_board[i][j] == _board[i + 1][j]) return true;
    return false;
}
