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


Direction Console2048::get_input_direction()
{
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
    print_board();
}

void Console2048::print_title()
{
    print("\n");
    print("             2048\n");
    print("            ======\n\n");
#ifdef UNIX
    refresh();
#endif
}

void Console2048::start()
{
    _game.subscribe(get_ptr());
    _game.set_input_source(get_input_direction);

    console_prepare();
    _game.start();
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

std::shared_ptr<Console2048> Console2048::get_ptr()
{
    return shared_from_this();
}
