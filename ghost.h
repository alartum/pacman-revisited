#ifndef GHOST_H
#define GHOST_H

#include"entity.h"
#include <QObject>

class Ghost : public Entity
{
    Q_OBJECT
public:
    Ghost(int tileX = 0, int tileY = 0, qreal speed = 3, QGraphicsItem * parent = 0);
private:
    // Целевая точка (тайл)
    QPoint aimPoint;

//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
//               QWidget *widget);
    void updateIfInCenter();
    void normalUpdate();
    void updateAnimationState ();
    void updateSpriteRect ();
    // Считаем квадрат расстояния между тайлами
    double computeSquareDistance (QPoint fromTile, QPoint toTile);
    QList<QPair<Entity::Direction, double> > getAvailableDirections ();
    Entity::Direction findBestDirection (QList<QPair<Entity::Direction, double> > directions);
    int animationState;
signals:
    void getPacmanPosition(QPoint &position);
    void nearPacman ();
};

#endif // GHOST_H
