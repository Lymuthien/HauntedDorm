#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QPushButton>

#include "ghost.h"
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
    void on_timeBeforeGhost_timeChanged(const QTime &time);

    void on_gameTime_timeChanged(const QTime &time);

private:
    void buildWalls();
    void buildRooms();
    void openDoorInRoom();
    void initHumanBots();
    void initGhost();
    void moveGhostHp();

    Ui::Map *ui;
    
    const int WALL_COUNT_WIDTH = 33;
    const int WALL_COUNT_HEIGHT = 19;

    QTimer* humanAndDoorTimer;
    QVector<Cage*> _walls;
    QGraphicsScene* _scene;
    QVector<Room*> _rooms;
    Human* _human;
    QVector<Human*> _humanBots;
    Ghost* _ghost;
    QVector<QPoint> _ghostHillZone;
};

#endif // MAP_H
