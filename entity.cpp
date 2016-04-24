#include "entity.h"
#include "gamescene.h"
#include <QDebug>
#include <math.h>
#include <QElapsedTimer>

const int Entity::SIZE = GameScene::TILE_SIZE;

Entity::Entity(int tileX, int tileY, qreal speed, QGraphicsItem * parent) :
    QGraphicsItem (parent)
{
    movingDirection = STOP;
    this->tileCoordinates.rx() = tileX;
    this->tileCoordinates.ry() = tileY;
    this->setPos((tileCoordinates.rx() + 0.5) * GameScene::TILE_SIZE,
                 (tileCoordinates.ry() + 0.5) * GameScene::TILE_SIZE);
    centerPoint = pos();
    isCenterPassed = true;
    isNearCenter = true;
    distanceToCenter = 0;
    this->speed = speed;
    spriteRect.setTopLeft(QPoint(0, 0));
    spriteRect.setBottomRight(QPoint(SIZE, SIZE));
    isInTunnel = false;
}

void Entity::move(qreal distance)
{
    if (distance == 0)
        return;
    switch (movingDirection)
    {
    case LEFT:
        moveBy(-distance, 0);
        break;
    case RIGHT:
        moveBy(distance, 0);
        break;
    case UP:
        moveBy(0, -distance);
        break;
    case DOWN:
        moveBy(0, distance);
        break;
    case STOP:
        break;
    default:
        qDebug()<<"Entity::move(): Wrong moving direction! Perhaps, it isn't initialized?";
    }
}

void Entity::move()
{
    if (speed == 0)
        return;
    switch (movingDirection)
    {
    case LEFT:
        moveBy(-speed, 0);
        break;
    case RIGHT:
        moveBy(speed, 0);
        break;
    case UP:
        moveBy(0, -speed);
        break;
    case DOWN:
        moveBy(0, speed);
        break;
    case STOP:
        break;
    default:
        qDebug()<<"Entity::move(): Wrong moving direction! Perhaps, it isn't initialized?";
    }
}

QRectF Entity::boundingRect() const
{
    return QRectF(-SIZE / 2 - 2, -SIZE / 2 - 2, SIZE + 4, SIZE + 4);
}

void Entity::advance(int step)
{
    // Первая фаза:
    if (step == 0) {
        if (movingDirection != STOP) {
            // Обновляем данные о тайле, в котором находимся,
            // в том числе, рядом ли мы с центром
            updateTile();
        }
        // Обычное обновление, выполняемое каждый игровой тик.
        // Сюда можно запихнуть, например, обработку клавиш.
            normalUpdate();
        // Если мы стоим, на этом обновление заканчивается.
    }
    // Вторая фаза:
    else {
        // Если стоим, то не перемещаемся.
        if (movingDirection == STOP)
            return;
        // Если мы не стоим, то производим движение.
        performMovement();
    }
}

bool Entity::checkCenter()
{
    // Если скорость больше, чем расстояние до центра тайла, т.е
    // за один следующий ход мы перешагнём центр, то мы рядом с центром.
    bool isNearCenter = speed > distanceToCenter;

    return isNearCenter;
}

void Entity::performMovement ()
{
    // Если рядом с центром, пытаемся повернуть.
    if (isNearCenter && !isCenterPassed) {
        // Встаём на центр тайла.
        setPos(centerPoint);
        // Теперь мы уже прошли центр.
        isCenterPassed = true;
        updateIfInCenter ();
        // "Лишнее" расстояние, которое остаётся пройти после того,
        // как мы дошли до центра
        int extraDistance = speed - distanceToCenter;

        // Двигаемся в новом направлении на расстояние extraDistance
        move(extraDistance);
    }
    else {
        // Если не рядом с центром или уже его прошли,
        // то можем смело двигаться вперёд.
        move();
    }
}

void Entity::computeDistanceToCenter ()
{
    // Считаем расстояние до центра через манхетеновую длину.
    // Т.к. у точек либо x, либо y координаты одинаковы, используем
    // "упрощённую" формулу (одинаковое сократится, разное останется)
    distanceToCenter = abs (pos().manhattanLength() - centerPoint.manhattanLength());
}

void Entity::updateTileCoordinates()
{
    switch (movingDirection)
    {
    case LEFT:
        tileCoordinates.rx()--;
        break;
    case RIGHT:
        tileCoordinates.rx()++;
        break;
    case UP:
        tileCoordinates.ry()--;
        break;
    case DOWN:
        tileCoordinates.ry()++;
        break;
    case STOP:
        break;
    default:
        qDebug()<<"Entity::updateTile(): Wrong moving direction! Perhaps, it isn't initialized?";
    }
}

void Entity::updateCenterPoint()
{
    // Просто устанавливаем координаты нового центра.
    centerPoint.setX((tileCoordinates.rx() + 0.5) * GameScene::TILE_SIZE);
    centerPoint.setY((tileCoordinates.ry() + 0.5) * GameScene::TILE_SIZE);
}

QPoint Entity::getNextTileCoordinates(Entity::Direction direction)
{
    // Координаты нового тайла в матрице.
    QPoint newTileCoordinates;

    // За основу берём текущие координаты.
    newTileCoordinates.rx() = tileCoordinates.x();
    newTileCoordinates.ry() = tileCoordinates.y();
    // И изменяем их в зависимости от направления.
    switch (direction)
    {
    case LEFT:
        newTileCoordinates.rx()--;
        break;
    case RIGHT:
        newTileCoordinates.rx()++;
        break;
    case UP:
        newTileCoordinates.ry()--;
        break;
    case DOWN:
        newTileCoordinates.ry()++;
        break;
    default:
        qDebug()<<"Entity::getNextTileCoordinates(): Wrong moving direction! Perhaps, it isn't initialized or == STOP";
    }
    return newTileCoordinates;
}

void Entity::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //Not using them
    (void)option;
    (void)widget;

    painter->drawPixmap(boundingRect().topLeft() + QPointF (2, 2), *GameScene::SPRITE_SHEET, spriteRect);
}

Entity::Direction Entity::getMovingDirection()
{
    return movingDirection;
}

qreal Entity::getSpeed()
{
    return speed;
}

QPoint Entity::getTileCoordinates()
{
    return tileCoordinates;
}

QPointF Entity::getCenterPoint()
{
    return centerPoint;
}

void Entity::updateTile()
{
    // Считаем новое расстояние до центра.
    computeDistanceToCenter();
    // Половинка стороны тайла.
    int halfTileSize = GameScene::TILE_SIZE / 2;
    // Если вышли за пределы данного тайла.
    if (distanceToCenter >= halfTileSize) {
        // Обновляем координаты текущего тайла.
        updateTileCoordinates();
        // Обновляем центр данного тайла.
        updateCenterPoint();
        // Центр нового тайла мы пока не проходили.
        isCenterPassed = false;
        emit inNewTile(tileCoordinates, this);
    }
    // Проверяем, находимся ли мы рядом с центром.
    isNearCenter = checkCenter();
}

bool Entity::getTileInfo (QPoint position)
{
    if (position.x() < 0 || position.x() >= GameScene::MATRIX_WIDTH
            || position.y() < 0 || position.y() >= GameScene::MATRIX_HEIGHT) {
        return false;
    }
    else if (GameScene::tileMap[position.x()][position.y()] == GameScene::WALL) {
        return false;
    }
    else {
        return true;
    }
}

bool Entity::getTileInfo (Entity::Direction direction)
{
    // Находим позицию данного тайла.
    QPoint tilePosition = getNextTileCoordinates(direction);

    // Возвращаем данные о тайле с данной позицией.
    return getTileInfo(tilePosition);
}

bool Entity::isReversedDirection (Entity::Direction direction)
{
    // "Сумма" направлений движения (сумма их номеров)
    int summ = movingDirection + direction;
    // Если она равна 3 (UP[0] + DOWN[3] или RIGHT[1] + LEFT [2]),
    if (summ == 3)
        //то направления противоположны.
        return true;
    else
        return false;
}

void Entity::setMovingDirection (Entity::Direction direction) {
    if (direction == EMPTY) {
        qDebug()<<"Entity::setMovingDirection(): EMPTY direction was passed!";
        return;
    }
    // В направлении, противоположном данному, мы ещё центр не проходили.
    if (isReversedDirection(direction)) {
        isCenterPassed = false;
    }
    // Новое направление движения.
    movingDirection = direction;
}

void Entity::setTileCoordinates (QPoint coordinates)
{
    tileCoordinates = coordinates;
    updateCenterPoint();
    setPos(QPointF (centerPoint));
}

int Entity::getSize ()
{
    return SIZE;
}

void Entity::setSpriteRect (QRect spriteRect)
{
    this->spriteRect = spriteRect;
}

void Entity::setSpriteRect(int number)
{
    QRect result(spritesStartPoint.x(), spritesStartPoint.y(), SIZE, SIZE);

    result.moveLeft(spritesStartPoint.x() + (number - 1) * SIZE);
    spriteRect = result;
}
