#include "gamescene.h"
#include <QRectF>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "pacman.h"
#include "ghost.h"

GameScene::TileType GameScene::tileMap[GameScene::MATRIX_WIDTH][GameScene::MATRIX_HEIGHT];
QPixmap* GameScene::SPRITE_SHEET = 0;

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent)
{
    this->setSceneRect(0, 0, WIDTH, HEIGHT);
    Pacman* pacman = new Pacman (9, 15);
    addItem(pacman);
    pacman->grabKeyboard();
    entities.append(pacman);
    connect (pacman, SIGNAL(inNewTile(QPoint,Entity*)), this, SLOT(teleport(QPoint,Entity*)));
    connect (pacman, SIGNAL(inNewTile(QPoint,Entity*)), this, SLOT(pelletEaten(QPoint)));

    Ghost* mutant = new Ghost(9, 7);
    addItem(mutant);
    entities.append(mutant);
    connect (mutant, SIGNAL(getPacmanPosition(QPoint&)),
             this, SLOT(givePacmanPosition(QPoint&)));
    connect (mutant, SIGNAL(inNewTile(QPoint,Entity*)), this, SLOT(teleport(QPoint,Entity*)));
    connect (mutant, SIGNAL(nearPacman()), this, SLOT(pacmanEaten()));

    QFile level ("://level.txt");
    if (!level.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }
    QTextStream stream (&level);
    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
        QString inputLine = stream.readLine();
        QStringList numbers = inputLine.split(' ');
        for (int x = 0; x < MATRIX_WIDTH; ++x) {
            int current = numbers.at(x).toInt();
            switch (current) {
            case 0:
                tileMap[x][y] = FREE;
                break;
            case 1:
                tileMap[x][y] = WALL;
                break;
            case 2:
                tileMap[x][y] = PELLET;
                break;
            case 3:
                tileMap[x][y] = ENERGYZER;
                break;
            case 4:
                tileMap[x][y] = TUNNEL;
                break;
            }
        }
    }
}
GameScene::~GameScene()
{
}
QRectF GameScene::getRectForTile(int x, int y) const
{
    //Возвращаем прямоугольник тайла с номером (x, y) в матрице
    return QRectF(x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}
//void GameScene::setTile(int x, int y, const QPixmap &pixmap)
//{
//    //Создаёт или заменяет тайл с координатами (x, y) на изображение.
//    if (x >= 0 && x < MATRIX_WIDTH && y >= 0 && y < MATRIX_HEIGHT) {
//        this->tileMap[x][y] = pixmap;
//        this->invalidate(this->rectForTile(x, y), BackgroundLayer);
//    }
//}
void GameScene::drawBackground(QPainter *painter, const QRectF &exposed)
{
    painter->setPen(Qt::NoPen);
    // Рисуем все тайлы, которые пересекаются с данной областью
    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
        for (int x = 0; x < MATRIX_WIDTH; ++x) {
            QRectF rect = getRectForTile(x, y);
            if (exposed.intersects(rect)) {
                switch (tileMap[x][y])
                {
                case WALL:
                    painter->setBrush(QColor (84, 96, 212));
                    painter->drawRect(rect);
                    break;
                case FREE:
                    painter->setBrush(Qt::black);
                    painter->drawRect(rect);
                    break;
                case PELLET:
                    painter->setBrush(Qt::black);
                    painter->drawRect(rect);
                    painter->setBrush(Qt::white);
                    painter->drawEllipse(rect.center(), 2, 2);
                    break;
                case ENERGYZER:
                    painter->setBrush(Qt::black);
                    painter->drawRect(rect);
                    painter->setBrush(Qt::white);
                    painter->drawEllipse(rect.center(), 4, 4);
                    break;
                case TUNNEL:
                    //Do nothing
                    break;
                }
//              painter->drawPixmap(rect.topLeft(), tileMap[x][y]);
            }
        }
    }
}

int GameScene::getTileSize()
{
    return TILE_SIZE;
}

void GameScene::initializeSpriteSheet()
{
    SPRITE_SHEET = new QPixmap ("://images/sprites.gif");
}

void GameScene::givePacmanPosition(QPoint &position)
{
    position = entities[0]->getTileCoordinates();
}

void GameScene::teleport(const QPoint position, Entity* sender)
{
    bool yCheck = position.y() == 9;

    if (yCheck) {
        int xCoordinate = position.x();
        if (xCoordinate == 0) {
            sender->setTileCoordinates(QPoint(18, 9));
        }
        else if (xCoordinate == 18) {
            sender->setTileCoordinates(QPoint(0, 9));
        }
    }
}

void GameScene::pelletEaten(const QPoint position)
{
    int x = position.x(),
        y = position.y();
    if (tileMap[x][y] == PELLET
        || tileMap[x][y] == ENERGYZER) {
        tileMap[x][y] = FREE;
        invalidate(this->getRectForTile(x, y), BackgroundLayer);
    }
}

void GameScene::drawForeground(QPainter *painter, const QRectF &exposed)
{
    painter->setPen(Qt::NoPen);
    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
        for (int x = 0; x < MATRIX_WIDTH; ++x) {
            QRectF rect = getRectForTile(x, y);
            if (exposed.intersects(rect)) {
                if (tileMap[x][y] == TUNNEL)
                {
                    painter->setBrush(QColor (84, 96, 212));
                    painter->drawRect(rect);
                }
            }
        }
    }
}

void GameScene::pacmanEaten()
{
    qDebug()<<"Какая прелесть, вас съели!";
}
