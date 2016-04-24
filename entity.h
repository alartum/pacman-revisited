/// ************************************************************
///*                    Entity [abstract]                       *
///* Абстрактный класс! Для работы необходимо описать:          *
///* 1)void updateState ();                                     *
///* 2)void moveFromCenter (qreal extraDistance);               *
///* Сущность, движущийся персонаж. Является одним из элементов *
///* игровой сцены.                                             *
/// ************************************************************
#ifndef ENTITY_H
#define ENTITY_H
#include <QPainter>
#include <QGraphicsItem>
#include <QObject>
#include <QList>
#include <QRectF>


class Entity : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    // Возможные направления движения.
    enum Direction {
        // Вверх
        UP,
        // Вниз
        RIGHT,
        // Налево
        LEFT,
        // Направо
        DOWN,
        // Стоим
        STOP,
        // Пусто, т.е. не определено. Надо для направления поворота и
        // потребованного поворота.
        EMPTY};
    explicit Entity(int tileX = 0, int tileY = 0, qreal speed = 3, QGraphicsItem * parent = 0);

    //! ИНТЕРФЕЙСЫ
    void setMovingDirection (Entity::Direction direction);
    void setTileCoordinates (QPoint coordinates);
    void setSpriteRect (QRect spriteRect);
    Entity::Direction getMovingDirection();
    Entity::Direction getTurnDirection();
    qreal getSpeed();
    QPoint getTileCoordinates();
    QPointF getCenterPoint();

    static int getSize ();
protected:
    //! ПЕРЕМЕЩЕНИЕ

    // Обычное обновление данных, выполняем каждый тик, независимо ни от чего.
    virtual void normalUpdate() = 0;
    // Обновляем данные сущности при нахождении в центре.
    virtual void updateIfInCenter () = 0;
    // Берём информацию о проходимости тайла, лежащего от нас в направлении
    // direction
    bool getTileInfo (Entity::Direction direction);
    // Взять координаты тайла, находящегося в направлении direction
    // от текущего.
    QPoint getNextTileCoordinates (Direction direction);
    // Проверяем, является ли направление direction противоположным
    // к movingDirection
    bool isReversedDirection(Direction direction);

    //! СПРАЙТЫ

    // Левая верхняя вершина прямоугольника, в котором заключён
    // первый спрайт
    QPoint spritesStartPoint;
    // Количество спрайтов (подразумевается, что они выстроены в линию.
    int spritesNumber;
    // Взять прямоугольник спрайта с номером number. Опять же, предполагается,
    // что они стоят в одной линии.
    void setSpriteRect (int number);
private:
    // Прямоугольник, в котором содержится спрайт на данный момент времени.
    // Спрайт берётся из изображения spriteSheet сцены.
    QRect spriteRect;
    // Сторона квадарата, в котором рисуется персонаж
    static const int SIZE;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                       QWidget *widget);
    //! ПЕРЕМЕЩЕНИЕ

    // Центр текущего тайла.
    QPointF centerPoint;
    // Расстояние до центра текущего тайла.
    qreal distanceToCenter;
    // Направление движения сущности.
    Entity::Direction movingDirection;
    // Скорость движения.
    qreal speed;
    // Координаты в тайлах.
    QPoint tileCoordinates;
    // Рядом ли с центром мы находимся.
    bool isNearCenter;
    // Пройден ли центр текущего тайла. Если это так,
    // то не будем пытаться менять направление
    bool isCenterPassed;
    bool isInTunnel;

    // Проверяем свою позицию относительно центров тайлов.
    bool checkCenter();
    // Непосредственно двигаемся (пытаемся повернуть, если необходимо)
    void performMovement ();
    // Считаем расстояние до центра текущего тайла.
    void computeDistanceToCenter();
    // Обновить тайл, в котором находимся.
    void updateTileCoordinates();
    // Обновить центральную точку.
    void updateCenterPoint();
    // Если необходимо, обновляем информацию о текущем тайле.
    void updateTile();
    // Двигаем сущность в соответствии с направлением и скоростью
    void move ();
    // Берём информацию о проходимости тайла с позицией position.
    bool getTileInfo (QPoint position);
    // Двигаем сущность в соответствии с направлением и расстоянием.
    void move (qreal distance);
    void advance(int step);
signals:
    void inNewTile (const QPoint newTile, Entity* sender);
};

#endif // ENTITY_H
