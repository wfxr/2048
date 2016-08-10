#pragma once

#include <iostream>
#include <memory>

#include "core/observer.h"
#include "core/game.h"

class Console2048 final : public Observer,
                    public std::enable_shared_from_this<Console2048> {
public:
    static std::shared_ptr<Console2048> create(int rows, int cols);

    void start();

    void update() override;

    void print_title() const;

    void print_board() const;

    void print_score() const;

    ~Console2048();
private:
    Console2048(int rows, int cols);

    static void clear_screen();
    static void console_prepare();
    Game _game;
};
