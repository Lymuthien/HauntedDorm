#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPushButton>

#include "room.h"
#include "human.h"

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

public:
    explicit Map(QWidget *parent = nullptr);
    ~Map();

signals:
    void settingsBtnClicked();
    void btnClicked();

private slots:
    void keyPressEvent(QKeyEvent* event);

private:
    void buildWalls();
    void buildRooms();
    void openDoorInRoom();

    Ui::Map *ui;
    
    const int WALL_COUNT_WIDTH = 33;
    const int WALL_COUNT_HEIGHT = 19;

    int humanRoom = 0;
    QTimer* humanAndDoorTimer;
    QVector<Cage*> _walls;
    QGraphicsScene* _scene;
    QVector<Room*> _rooms;
    Human* _human;
};

#endif // MAP_H
