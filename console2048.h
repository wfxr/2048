#include <iostream>
#include <memory>
#include <ncurses.h>

#include "game.h"
#include "observer.h"

class Console2048 : public Observer,
                    public std::enable_shared_from_this<Console2048> {
public:
    Console2048(int rows, int cols) : _game(rows, cols) {
    }

    ~Console2048() {
        curs_set(_orginal_cursor);
        endwin();   // End curses mode
    }

    void update() override {
        clear();
        print_title();
        print_board();
        refresh();
    }

    void print_title() {
        printw("          2048\n");
        printw("         ======\n");
    }

    void start() {
        _game.subscribe(get_ptr());
        _game.set_input_source(get_input_direction);

        initscr();  // Start curse mode
        noecho();   // Don't echo while we do getch
        _orginal_cursor = curs_set(0);    // Hide cursor
        keypad(stdscr, TRUE);   // To get arrow key

        _game.start();
    }

    void print_board() const {
        auto board = _game.get_board();
        for (int i = 0; i < board.rows(); ++i) {
            for (int j = 0; j < board.cols(); ++j) {
                auto num = board.get(i, j);
                if (num == 0)
                    printw("   .");
                else
                    printw("%4d", num);
                printw("  ");
            }
            printw("\n\n");
        }
    }

    std::shared_ptr<Console2048> get_ptr() { return shared_from_this(); }

    static Direction get_input_direction() {
        for (;;) {
            switch (getch()) {
            case KEY_UP:
            case 'w':
            case 'k':
                return Direction::Up;
            case KEY_DOWN:
            case 's':
            case 'j':
                return Direction::Down;
            case KEY_LEFT:
            case 'a':
            case 'h':
                return Direction::Left;
            case KEY_RIGHT:
            case 'd':
            case 'l':
                return Direction::Right;
            default:
                break;
            }
        }
    }

private:
    Game _game;
    int _orginal_cursor;
};
