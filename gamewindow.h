// ************************************************************
//*                    GameWindow                              *
//* Главное окно игры. Осуществляет связь между меню и игровым *
//* процессом.                                                 *
// ************************************************************
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QStackedWidget>
#include "gamemenu.h"
#include "gameview.h"

class GameWindow : public QStackedWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = 0);
    ~GameWindow ();
private:
    //игровое меню
    GameMenu *menu;
    //окно с игрой
    GameView *view;
private slots:
    void showView();
};

#endif // GAMEWINDOW_H
