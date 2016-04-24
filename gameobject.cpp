#include "gameobject.h"

GameObject::GameObject(Grid map)
{
}
void GameObject::setPos(int x, int y)
{
    this->x = x;
    this->y = y;
}
void GameObject::setGridPos(int column, int row)
{
    this->column = column;
    this->row = row;
    x = column * map.boxSize + map.boxSize / 2;
    y = row * map.boxSize + map.boxSize / 2;
}
