#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <memory>
#include <QLabel>

#include "../core/game.h"
#include "../core/observer.h"

class QTile;
class QWidget;
class QKeyEvent;

class GUI2048 final : public QMainWindow, public Observer, public std::enable_shared_from_this<GUI2048> {
    Q_OBJECT
    QLabel *_title;
    QLabel *_score;
    QWidget *_centralWidget;
public:
    ~GUI2048();
    void run();
    void quit();
    static std::shared_ptr<GUI2048> create(int rows, int cols, QWidget *parent = 0);

private:
    GUI2048(int rows, int cols, QWidget *parent = 0);

    void update() override;
    void updateTiles();
    void updateScore();

    Game _game;
    std::vector<std::vector<QTile*>> _gui_board;

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
