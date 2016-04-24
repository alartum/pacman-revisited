#include "gamewindow.h"
#include <QApplication>
#include <QDebug>

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    GameWindow game;
    GameScene::initializeSpriteSheet();
    game.show();
    return app.exec();
}
