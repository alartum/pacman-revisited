// ************************************************************
//*                    GameScene                               *
//* Игровая сцена, осуществляющее управление всеми элементами  *
//* игры. Содержит карту тайлов (матрицу), которая управляется *
//* через данный класс.                                        *
// ************************************************************
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <QList>
#include "entity.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum TileType {
        FREE,
        WALL,
        PELLET,
        ENERGYZER,
        TUNNEL
    };
     explicit GameScene(QObject *parent = 0);
    ~GameScene();
    static int getTileSize();
    static void initializeSpriteSheet();
protected:
    // Нарисовать задний фон, состоящий из тайлов.
    void drawBackground(QPainter *painter, const QRectF &exposed);
    void drawForeground(QPainter *painter, const QRectF &rect);
private:
    friend class Entity;
//    friend class Ghost;
    // Количество строк в матрице (высота).
    static const int MATRIX_HEIGHT = 21;
    // Количество столбцов в матрице (ширина).
    static const int MATRIX_WIDTH = 19;
    // Размер стороны тайла.
    static const int TILE_SIZE = 16;
    // Высота игровой сцены.
    static const int HEIGHT = MATRIX_HEIGHT * TILE_SIZE;
    // Ширина игровой сцены.
    static const int WIDTH = MATRIX_WIDTH * TILE_SIZE;
    // Карта тайлов (матричное представление игровой сцены)
    static TileType tileMap[MATRIX_WIDTH][MATRIX_HEIGHT];
    // Массив игровых сущностей. [0] = Pacman
    QList<Entity*> entities;
    static QPixmap* SPRITE_SHEET;

    //void setTile(int x, int y, const QPixmap &pixmap);
    // Взять прямоугольник, занимаемый тайлом с координатами (x, y) в матрице.
    QRectF getRectForTile(int x, int y) const;
private slots:
    void givePacmanPosition(QPoint &position);
    void teleport (const QPoint position, Entity* sender);
    void pelletEaten (const QPoint position);
    void pacmanEaten();
};

#endif // GAMESCENE_H
