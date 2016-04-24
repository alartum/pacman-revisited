#include "pacman.h"
#include <QDebug>

Pacman::Pacman(int tileX, int tileY, qreal speed, QGraphicsItem *parent) :
        Entity(tileX, tileY, speed, parent)
{
    this->setFlag(ItemIsFocusable);
    requestedTurn = EMPTY;
    turnDirection = EMPTY;
    spritesStartPoint.setX(21);
    spritesStartPoint.setY(20);
    animationState = 2;
    intState = -2;
    setSpriteRect(1);
}

void Pacman::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
        case Qt::Key_Left:
            requestedTurn = LEFT;
            break;
        case Qt::Key_Right:
            requestedTurn = RIGHT;
            break;
        case Qt::Key_Up:
            requestedTurn = UP;
            break;
        case Qt::Key_Down:
            requestedTurn = DOWN;
            break;
    };
}

void Pacman::updateIfInCenter ()
{
    // Пытаемся повернуть.
    bool success = tryToTurn();

    // Если не удалось:
    if (!success) {
        // Пытаемся двинуться.
        tryToMove();
    }
}

bool Pacman::tryToTurn()
{
    if (turnDirection == EMPTY)
        return false;
    // Берём данные о тайле, в который хотим повернуть.
    bool tileToTurn = getTileInfo (turnDirection);

    // Если он проходим, поворачиваем.
    if (tileToTurn == true) {
        // Направление поворота теперь направление движения.
        setMovingDirection (turnDirection);
        // Нового направления для поворота пока нет.
        turnDirection = EMPTY;

        //Поворот удался.
        return true;
    }

    return false;
}

void Pacman::tryToMove()
{
    // Тайл, в который попадём при продолжении движения.
    bool tileToEnter = getTileInfo (getMovingDirection());

    // Если оказалось, что тайл для движения непроходим:
    if (tileToEnter == false) {
        setMovingDirection(Entity::STOP);
        animationState = 1;
        turnDirection = EMPTY;
    }
}

void Pacman::analyzeRequestedTurn()
{
    if ((getTileCoordinates().x() == 0 || getTileCoordinates().x() == 18)
        && getTileCoordinates().y() == 9)
        return;
    // Если поворот не потребован, то возвращаемся.
    if (requestedTurn == EMPTY)
        return;
    // Если он противоположен текущему направлению движения, то сразу меняем.
    if (isReversedDirection(requestedTurn)) {
        setMovingDirection(requestedTurn);
        // Обнуляем требуемый поворот.
        turnDirection = EMPTY;
    }
    // Если мы не движемся, то проверяем, можем ли двигаться в новом
    // направлении. Если так, то сдвигаемся.
    else if (getMovingDirection() == STOP) {
        if (getTileInfo(requestedTurn) == true) {
            setMovingDirection(requestedTurn);
        }
    }
    // В противном случае, просто будем поворачивать в потребованном направлении.
    else {
        turnDirection = requestedTurn;
    }
    // Оставался вариант, когда поворот совпадает с направлением движения.
    // Тогда ничего не делаем.
    // После обработки чистим потребованный поворот.
    requestedTurn = EMPTY;
}

void Pacman::normalUpdate()
{
    if (getMovingDirection() != Entity::STOP) {
        updateAnimationState ();
        updateSpriteRect ();
    }
    // Производим первоначальную обработку поворотов.
    analyzeRequestedTurn();
}

void Pacman::updateAnimationState()
{
   if (intState < 2) {
        intState ++;
   }
   else {
       intState = -2;
   }
   animationState = abs(intState);
}

void Pacman::updateSpriteRect ()
{
    if (animationState == 2) {
        setSpriteRect(1);
    }
    else {
        int current;
        switch (getMovingDirection())
        {
        case LEFT:
            current = 3;
            break;
        case RIGHT:
            current = 5;
            break;
        case UP:
            current = 7;
            break;
        case DOWN:
            current = 9;
            break;
        case STOP:
            break; // Ignore
        case EMPTY:
            break; // Ignore
        }
        setSpriteRect(current - animationState);
    }
}
