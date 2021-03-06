#include "gui2048.h"
#include <QApplication>
#include <memory>

using std::make_shared;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto game = GUI2048::create(4, 4);
    game->run();

    return a.exec();
}
