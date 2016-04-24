#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QStackedWidget(parent)
{
    menu = new GameMenu;
    view = new GameView;
    this->addWidget(view);
    this->addWidget(menu);
    connect(menu, SIGNAL(startClicked()), this, SLOT(showView()));
}
GameWindow::~GameWindow()
{
    delete menu;
    delete view;
}
void GameWindow::showView()
{
    setCurrentWidget(view);
}
