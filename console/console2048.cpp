#include "console2048.h"

#ifdef WIN32
#include <conio.h>
#include <windows.h>

#define print printf
#define getch _getch

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#else
#define UNIX
#include <ncurses.h>
#define print printw
#endif


void Console2048::clear_screen() {
#ifdef WIN32
    system("cls");
#else
    clear();
#endif
}

void Console2048::console_prepare() {
#ifdef WIN32
    // Hide cursor
    static auto output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = 1;
    SetConsoleCursorInfo(output, &cursor);
#else
    initscr();  // Start curse mode
    noecho();   // Don't echo while we do getch
    curs_set(0);    // Hide cursor
    keypad(stdscr, TRUE);   // To get arrow key
#endif

}

Console2048::Console2048(int rows, int cols) : _game(rows, cols) {

}

Console2048::~Console2048()
{
#ifdef UNIX
    endwin();   // End curses mode
#endif
}

void Console2048::update()
{
    clear_screen();
    print_title();
    print_score();
    print_board();
}

void Console2048::print_title() const
{
    print("\n");
    print("%17d\n", 2048);
    print("%18s\n\n", "======");
#ifdef UNIX
    refresh();
#endif
}

void Console2048::start()
{
    _game.subscribe(get_ptr());

    console_prepare();
    _game.reset();

    while (!_game.game_over()) {
        switch (getch()) {
        case KEY_UP:
        case 'w':
        case 'k':
            _game.move_up();
            break;
        case KEY_DOWN:
        case 's':
        case 'j':
            _game.move_down();
            break;
        case KEY_LEFT:
        case 'a':
        case 'h':
            _game.move_left();
            break;
        case KEY_RIGHT:
        case 'd':
        case 'l':
            _game.move_right();
            break;
        default:
            break;
        }
    }
}

void Console2048::print_board() const
{
    auto board = _game.get_board();
    for (auto i = 0; i < board.rows(); ++i) {
        for (auto j = 0; j < board.cols(); ++j) {
            auto num = board.get(i, j);
            if (num == 0)
                print("    .");
            else
                print("%5d", num);
            print("  ");
        }
        print("\n\n\n");
    }
#ifdef UNIX
    refresh();
#endif
}

void Console2048::print_score() const {
    print("%20s", "Score:");
    print("%6d\n\n", _game.score());
#ifdef UNIX
    refresh();
#endif
}

std::shared_ptr<Console2048> Console2048::get_ptr()
{
    return shared_from_this();
}
