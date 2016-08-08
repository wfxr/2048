#include "gui2048.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QKeyEvent>
#include <QString>

#include "qtile.h"

using std::vector;

GUI2048::GUI2048(int rows, int cols, QWidget *parent)
    : QMainWindow(parent), _game(rows, cols), _gui_board(rows, vector<QTile*>(cols)) {
    resize(550,500);

    _centralWidget = new QWidget(this);
    setCentralWidget(_centralWidget);

    auto boardLayout = new QGridLayout();
    for (int i = 0; i < _gui_board.size(); ++i)
        for (int j = 0; j < _gui_board[i].size(); ++j) {
            QTile *tile = new QTile(_game.get_board().get(i, j));
            _gui_board[i][j] = tile;
            boardLayout->addWidget(tile,i ,j);
        }

    _centralWidget->setLayout(boardLayout);

    setStyleSheet("GUI2048 { background-color: rgb(187,173,160) }");
}

GUI2048::~GUI2048()
{
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            delete _gui_board[i][j];
}

void GUI2048::start() {
    _game.subscribe(shared_from_this());
    _game.start();
}

void GUI2048::update() {
    updateTiles();
}

void GUI2048::updateTiles() {
    for (int i = 0; i < _gui_board.size(); ++i)
        for (int j = 0; j < _gui_board[i].size(); ++j)
            _gui_board[i][j]->setNum(_game.get_board().get(i, j));
}

void GUI2048::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        _game.move_up();
        break;
    case Qt::Key_Left:
        _game.move_left();
        break;
    case Qt::Key_Right:
        _game.move_right();
        break;
    case Qt::Key_Down:
        _game.move_down();
        break;
    }
}
