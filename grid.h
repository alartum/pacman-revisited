#ifndef GRID_H
#define GRID_H
#include <QPainter>

class Grid
{
public:
    enum Space {dead, legal};
    static const int columsCount = 28;
    static const int rowsCount = 36;
    static const int boxSize = 20;
    static const int width = columsCount * boxSize;
    static const int height = rowsCount * boxSize;
    Space table[rowsCount][columsCount];

    Grid ();
    Grid (Space spaceType);
    void draw(QPainter *painter, Qt::GlobalColor deadColor, Qt::GlobalColor legalColor);
    void setExample();
};

#endif // GRID_H
