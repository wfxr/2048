#include "gui2048.h"
#include <QApplication>
#include <memory>

using std::make_shared;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto game = make_shared<GUI2048>(4, 4);
    game->show();
    game->start();

    return a.exec();
}
