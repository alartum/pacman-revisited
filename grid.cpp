#include "grid.h"

Grid::Grid()
{
    for (int i = 0; i < columsCount; i ++)
        for (int j = 0; j < rowsCount; j ++)
            table[j][i] = dead;
}
Grid::Grid(Space spaceType)
{
    for (int i = 0; i < columsCount; i ++)
        for (int j = 0; j < rowsCount; j ++)
            table[j][i] = spaceType;
}
void Grid::draw(QPainter *painter, Qt::GlobalColor deadColor, Qt::GlobalColor legalColor)
{
    const int halfBoxSize = boxSize / 2;
    for (int i = 0; i < rowsCount; i ++)
    {
        for (int j = 0; j < columsCount; j ++)
        {
            if (table[i][j] == dead)
            {
                painter->setBrush(deadColor);
                painter->drawRect(boxSize * j, boxSize * i, boxSize, boxSize);
            }
            else
            {
                painter->setBrush(legalColor);
                painter->drawRect(boxSize * j, boxSize * i, boxSize, boxSize);
                QPen *pen = new QPen (Qt::darkGreen);
                pen->setWidth(3);
                painter->setPen(*pen);
                if (table[i + 1][j] == legal)
                {
                    painter->drawLine(boxSize * j + halfBoxSize, boxSize * i + halfBoxSize, boxSize * j + halfBoxSize, boxSize * (i + 1));
                }
                if (table[i - 1][j] == legal)
                {
                    painter->drawLine(boxSize * j + halfBoxSize, boxSize * i, boxSize * j + halfBoxSize, boxSize * (i + 1) - halfBoxSize);
                }
                if (table[i][j + 1] == legal)
                {
                    painter->drawLine(boxSize * j + halfBoxSize, boxSize * i + halfBoxSize, boxSize * (j + 1), boxSize * i + halfBoxSize);
                }
                if (table[i][j - 1] == legal)
                {
                    painter->drawLine(boxSize * j, boxSize * i + halfBoxSize, boxSize * (j + 1) - halfBoxSize, boxSize * i + halfBoxSize);

                }
                delete pen;
            }
            painter->setPen(Qt::black);
        }
    }
}
void Grid::setExample()
{
    //центр: 14;18

    for (int i = 11; i <= 17; i ++)
       table[18][i] = legal;
    for (int i = 15; i <= 21; i ++)
       table[i][14] = legal;
}
