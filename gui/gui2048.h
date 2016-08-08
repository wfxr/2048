#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <memory>

#include "../core/game.h"
#include "../core/observer.h"

class QTile;
class QWidget;
class QKeyEvent;

class GUI2048 : public QMainWindow, public Observer, public std::enable_shared_from_this<GUI2048> {
    Q_OBJECT
    QWidget *_centralWidget;
public:
    GUI2048(int rows, int cols, QWidget *parent = 0);
    ~GUI2048();

    void start();

private:
    void update() override;
    void updateTiles();
    std::vector<std::vector<QTile*>> _gui_board;
    Game _game;
protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
