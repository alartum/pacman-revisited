#ifndef GameObject_H
#define GameObject_H
#include "grid.h"
#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>

class GameObject
{
protected:
    float x;
    float y;
    int column;
    int row;
public:
    GameObject(Grid map);
    void setPos(int x = map.width / 2, int y = map.height / 2);
    void setGridPos(int column = map.columsCount / 2, int row = map.rowsCount / 2);
    virtual void paint (QPainter* painter) = 0;
    static Grid map;
};

#endif // GameObject_H
