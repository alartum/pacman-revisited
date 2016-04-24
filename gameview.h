// ************************************************************
//*                    GameView                                *
//* Окно, отображающее сцену                                   *
// ************************************************************
#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QTimer>
#include "gamescene.h"

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = 0);
    ~GameView();
private:
    //игровая сцена ~ уровень
    QGraphicsScene *gameScene;
    // Таймер для обновления.
    QTimer timer;
signals:

public slots:

};

#endif // GAMEVIEW_H
