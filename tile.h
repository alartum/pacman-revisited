#ifndef TILE_H
#define TILE_H

class Tile
{
public:
    Tile();
    // Тип линии тайла
    enum Line
    {
        // Отсутствует (пустой тайл)
        NONE,
        // Одиночная линия
        SINGLE,
        // Двойная линия
        DOUBLE,
        // Квадратная линия (двойная с острыми краями)
        SQUARE
    };

    // Тип тайла
    enum Type
    {
        // Пустой тайл
        EMPTY,
        // Стена
        WALL,
        // Клетка, в которой возможен поворот
        CHANGEBOX,
        // Выход из комнаты привидений
        GATE
    };

    // Предмет, содержащийся в тайле
    enum TileItem
    {
        // Пусто
        NOTHING,
        // Горошина
        PELLET,
        // Энерджайзер
        POWERUP,
        // Вкусное
        FRUIT
    };
};

#endif // TILE_H
