#pragma once

#include <iostream>
#include <memory>

#include "core/observer.h"
#include "core/game.h"

class Console2048 : public Observer,
                    public std::enable_shared_from_this<Console2048> {
public:
    Console2048(int rows, int cols);

    ~Console2048();

    void start();

    void update() override;

    void print_title() const;

    void print_board() const;

    void print_score() const;

    std::shared_ptr<Console2048> get_ptr();

private:
    static void clear_screen();
    static void console_prepare();
    Game _game;
};
