#include "board.h"
#include "direction.h"

#include <random>
#include <algorithm>

using std::count;
using std::swap;
using std::pair;
using std::make_pair;

void Board::reset() {
    for (auto& row : _board)
        for (auto& cell : row)
            cell = 0;
    random_arise();
    random_arise();
}

int Board::blank_count() const {
    auto num = 0;
    for (const auto &row : _board)
        num += count(row.begin(), row.end(), 0);
    return num;
}

void Board::random_arise() {
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

pair<bool, int> Board::move_left(int i, int j) {
    auto moved = false;
    auto score = 0;
    for (; j > 0 && _board[i][j - 1] == 0; --j) {
        swap(_board[i][j], _board[i][j - 1]);
        moved = true;
    }

    if (j > 0 && _board[i][j - 1] == _board[i][j]) {
        score = merge(_board[i][j - 1], _board[i][j]);
        moved = true;
    }

    return make_pair(moved, score);
}

pair<bool, int> Board::move_right(int i, int j) {
    auto moved = false;
    auto score = 0;
    for (; j < _cols - 1 && _board[i][j + 1] == 0; ++j) {
        swap(_board[i][j], _board[i][j + 1]);
        moved = true;
    }

    if (j < _cols - 1 && _board[i][j + 1] == _board[i][j]) {
        score = merge(_board[i][j + 1], _board[i][j]);
        moved = true;
    }

    return make_pair(moved, score);
}

pair<bool, int> Board::move_up(int i, int j) {
    auto moved = false;
    auto score = 0;
    for (; i > 0 && _board[i - 1][j] == 0; --i) {
        swap(_board[i][j], _board[i - 1][j]);
        moved = true;
    }

    if (i > 0 && _board[i - 1][j] == _board[i][j]) {
        score = merge(_board[i - 1][j], _board[i][j]);
        moved = true;
    }

    return make_pair(moved, score);
}

pair<bool, int> Board::move_down(int i, int j) {
    auto moved = false;
    auto score = 0;
    for (; i < _rows - 1 && _board[i + 1][j] == 0; ++i) {
        swap(_board[i][j], _board[i + 1][j]);
        moved = true;
    }

    if (i < _rows - 1 && _board[i + 1][j] == _board[i][j]) {
        score = merge(_board[i + 1][j], _board[i][j]);
        moved = true;
    }

    return make_pair(moved, score);
}

int Board::move(Direction direction) {
    auto moved = false;
    auto score = 0;
    switch (direction) {
        case Direction::Up:
            for (auto row = 0; row < _rows; ++row)
                for (auto col = 0; col < _cols; ++col)
                    if (_board[row][col]) {
                        auto result = move_up(row, col);
                        moved |= result.first;
                        score += result.second;
                    }
            break;
        case Direction::Down:
            for (auto row = _rows - 1; row >= 0; --row)
                for (auto col = 0; col < _cols; ++col)
                    if (_board[row][col]) {
                        auto result = move_down(row, col);
                        moved |= result.first;
                        score += result.second;
                    }
            break;
        case Direction::Left:
            for (auto row = 0; row < _rows; ++row)
                for (auto col = 0; col < _cols; ++col)
                    if (_board[row][col]) {
                        auto result = move_left(row, col);
                        moved |= result.first;
                        score += result.second;
                    }
            break;
        case Direction::Right:
            for (auto row = 0; row < _rows; ++row)
                for (auto col = _cols - 1; col >= 0; --col)
                    if (_board[row][col]) {
                        auto result = move_right(row, col);
                        moved |= result.first;
                        score += result.second;
                    }
            break;
        default: break;
    }

    if (moved) random_arise();
    return score;
}

int& Board::merge(int & to, int & from)
{
    to += from;
    from = 0;
    return to;
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
