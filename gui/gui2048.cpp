#include "gui2048.h"

#include <QVBoxLayout>
#include <QGridLayout>
#include <QKeyEvent>
#include <QString>
#include <QMessageBox>

#include "qtile.h"

using std::vector;

GUI2048::GUI2048(int rows, int cols, QWidget *parent)
    : QMainWindow(parent), _game(rows, cols), _gui_board(rows, vector<QTile*>(cols)) {
    _centralWidget = new QWidget(this);

    // title
    _title = new QLabel("2048");
    _title->setStyleSheet("QLabel { color: rgbs(119,110,101); font: 56pt; font: bold }");
    _title->setFixedHeight(80);

    // score
    _score = new QLabel(QString("SCORE: %1").arg(_game.score(), 6));
    _score->setStyleSheet("QLabel { color: rgb(235,224,214); font: 18pt; }");
    _score->setFixedHeight(50);

    auto mainLayout = new QVBoxLayout();
    mainLayout->insertWidget(1, _title, 0, Qt::AlignHCenter);
    mainLayout->insertWidget(1, _score, 0, Qt::AlignRight);

    auto boardLayout = new QGridLayout();
    for (int i = 0; i < _gui_board.size(); ++i)
        for (int j = 0; j < _gui_board[i].size(); ++j) {
            QTile *tile = new QTile(_game.get_board().get(i, j));
            _gui_board[i][j] = tile;
            boardLayout->addWidget(tile,i ,j);
        }
    mainLayout->addLayout(boardLayout);

    _centralWidget->setLayout(mainLayout);

    this->setCentralWidget(_centralWidget);
    this->setStyleSheet("GUI2048 { background-color: rgb(187,173,160) }");
    this->setWindowTitle("2048");

    this->resize(500, 500 + _title->height() + _score->height());
}

GUI2048::~GUI2048() {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            delete _gui_board[i][j];
}

void GUI2048::run() {
    this->show();
    _game.subscribe(shared_from_this());
    _game.reset();
}

void GUI2048::update() {
    updateTiles();
    updateScore();
    if (_game.game_over()) {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Game over");
        msgBox.setText("Play again?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::Ok);
        if (msgBox.exec() == QMessageBox::Ok)
            _game.reset();
    }
}

void GUI2048::updateTiles() {
    for (int i = 0; i < _gui_board.size(); ++i)
        for (int j = 0; j < _gui_board[i].size(); ++j)
            _gui_board[i][j]->setValue(_game.get_board().get(i, j));
}

void GUI2048::updateScore() {
    _score->setText(QString("SCORE: %1").arg(_game.score()));
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
