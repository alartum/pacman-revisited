#include "gameview.h"
#include <QDebug>

GameView::GameView(QWidget *parent) :
    QGraphicsView(parent)
{
    this->gameScene = new GameScene;
    this->setScene(gameScene);
    this->setCacheMode(QGraphicsView::CacheBackground);
    this->setRenderHint(QPainter::Antialiasing, false);
    this->setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing);
    connect (&timer, SIGNAL(timeout()), gameScene, SLOT(advance()));
    timer.start(50);
}
GameView::~GameView()
{
    delete gameScene;
}
