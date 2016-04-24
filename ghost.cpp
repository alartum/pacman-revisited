#include "ghost.h"
#include <QDebug>
#include "pacman.h"
#include <math.h>

Ghost::Ghost(int tileX, int tileY, qreal speed, QGraphicsItem *parent) :
    Entity(tileX, tileY, speed, parent)
{
    emit getPacmanPosition(aimPoint);
    setMovingDirection(RIGHT);
    animationState = 0;
    spritesStartPoint.setX(20);
    spritesStartPoint.setY(115);
}

//void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
//           QWidget *widget)
//{
//    painter->setBrush(Qt::red);
//    painter->setPen(Qt::NoPen);
//    painter->drawEllipse(boundingRect().center(), Entity::getSize() / 2, Entity::getSize() / 2);
//}

double Ghost::computeSquareDistance(QPoint fromTile, QPoint toTile)
{
    // x и y составляющие расстояния в прямоугольных координатах
    double x = fromTile.x() - toTile.x(),
        y = fromTile.y() - toTile.y(),
        squareDistance;
    // Расстояние получается сложением квадратов составляющих.
    squareDistance = pow(x, 2) + pow(y, 2);

    return squareDistance;
}

void Ghost::updateIfInCenter ()
{
    // Целевая точка - положение пакмана.
    emit getPacmanPosition(aimPoint);

    // Находим возможные направления движения.
    QList<QPair<Entity::Direction, double> > directions = getAvailableDirections();
    // Выбираем, куда хотим поворачивать.
    Entity::Direction bestDirection = findBestDirection(directions);
    // Меняем направление движения.
    setMovingDirection(bestDirection);
}

QList<QPair<Entity::Direction, double> > Ghost::getAvailableDirections()
{
    // Список тайлов, доступных для движения из данной точки.
    QList<QPair<Entity::Direction, double> > directions;

    // Смотрим по всем направлениям.
    for (int i = UP; i < STOP; ++i) {
        Entity::Direction iToDirection = static_cast<Entity::Direction> (i);
        // Если направление не противоположно данному
        // и тайл в этом направлении проходим,
        if (!isReversedDirection(iToDirection) && getTileInfo(iToDirection)) {
            // то берём координаты этого тайла.
            QPoint nextTile = getNextTileCoordinates(iToDirection);
            // Считаем расстояние до целевой точки.
            double distanceToAimPoint = computeSquareDistance(nextTile, aimPoint);
            // Формируем пару.
            QPair<Entity::Direction, double> availableDirection(iToDirection, distanceToAimPoint);
            // Запихиваем её в список.
            directions.append(availableDirection);
        }
    }

    return directions;
}

Entity::Direction Ghost::findBestDirection (QList<QPair<Entity::Direction, qreal> > directions)
{
    // Если размер списка "кандидатов" на поворот 0, то мы в тупике.
    if (directions.size() == 0) {
        qDebug()<<"Ghost::findBestDirection: Error! I'm in deadlock!";
        return Entity::STOP;
    }
    if (directions.size() == 1)
        return directions.at(0).first;

    // Минимальная дистанция равна сначала первому кандидату.
    int minimumDistance = directions.at(0).second;
    // Лучшее направление движения. Опять же, равно таковому у первого кандидата.
    Entity::Direction bestDirection = directions.at(0).first;

    // Ищем что-нибудь получше.
    for (int i = 1; i < directions.size(); i++) {
        // Текущее расстояние.
        double currentDistance = directions.at(i).second;
        // Если меньше, меняем минимум и лучшее направление.
        if (currentDistance < minimumDistance) {
            minimumDistance = currentDistance;
            bestDirection = directions.at(i).first;
        }
    }

    return bestDirection;
}

void Ghost::normalUpdate()
{
    updateAnimationState ();
    updateSpriteRect ();
    // Координаты тайла с пакманом
    QPoint dinnerPosition;

    //Обновляем их.
    getPacmanPosition(dinnerPosition);
    if (dinnerPosition == getTileCoordinates()) {
        emit nearPacman();
    }
}

void Ghost::updateAnimationState()
{
   animationState++;
   animationState %= 2;
}

void Ghost::updateSpriteRect ()
{
    int current;

    switch (getMovingDirection())
    {
    case LEFT:
        current = 1;
        break;
    case RIGHT:
        current = 5;
        break;
    case UP:
        current = 7;
        break;
    case DOWN:
        current = 3;
        break;
    case STOP:
        break; // Ignore
    case EMPTY:
        break; // Ignore
    }
    setSpriteRect(current + animationState);
}
