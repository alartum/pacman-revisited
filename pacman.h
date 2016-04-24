#ifndef PACMAN_H
#define PACMAN_H
#include "entity.h"
#include <QKeyEvent>
#include <QObject>
#include <QTimer>

class Pacman : public Entity
{
    Q_OBJECT
public:
    Pacman(int tileX = 0, int tileY = 0, qreal speed = 3, QGraphicsItem * parent = 0);
private:
    // Потребованный поворот.
    Entity::Direction requestedTurn;
    // Направление, в котором нам хотелось бы повернуть.
    // Если NONE, значит не хотим поворачивать.
    Entity::Direction turnDirection;
    // Статус анимации. Показывает, на каком этапе сейчас анимация.
    int animationState;
    // Вспомогательный статус, служит для получения статуса анимации.
    int intState;

    void updateIfInCenter();
    void normalUpdate();
    // Обработчик потребованных поворотов.
    void analyzeRequestedTurn();
    // Поворачиваем и, если это удалось, проходим ещё distance
    // в новом направлении
    bool tryToTurn();
    // Проходим в заданном направлении distance, если это возможно.
    void tryToMove();
    void keyPressEvent(QKeyEvent * event);
    void updateAnimationState ();
    void updateSpriteRect ();
};

#endif // PACMAN_H
