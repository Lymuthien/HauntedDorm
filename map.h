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
    explicit Map(QPixmap skin, QPixmap *skins, QWidget *parent = nullptr);
    ~Map();

signals:
    void settingsBtnClicked();
    void btnClicked();
    void doorHitted();
    void gameOver(bool victory);

private slots:
    void keyPressEvent(QKeyEvent* event);
    void on_timeBeforeGhost_timeChanged(const QTime &time);
    void on_gameTime_timeChanged(const QTime &time);

    void on_pushButton_clicked();

private:
    void buildWalls();
    void buildRooms();
    void openDoorInRoom();
    void hitDoorInRoom();
    void initHumanBots();
    void initGhost();
    void attackGhost(QPointF pos, int dmg);
    void moveGhostHp();
    void endGame();
    long* randNumbers(int n);
    void removeRoom(Room *room);
    void setCoins(int money, int energy);
    void bulletLine(QGraphicsEllipseItem *&_bullet, QPointF _ghostPos, QTimer *_timer);

    Ui::Map *ui;
    
    const int WALL_COUNT_WIDTH = 33;
    const int WALL_COUNT_HEIGHT = 19;

    Human* m_human;
    Ghost* m_ghost;
    QPixmap* m_skins;
    QTimer* m_humanAndDoorTimer;
    QTimer* m_ghostAndDoorTimer;
    QTimer* m_bulletToGhostTimer;
    QVector<QPoint> m_ghostHillZone;
    QGraphicsScene* m_scene;
    QVector<Cage*> m_walls;
    QVector<Room*> m_rooms;
    QVector<Human*> m_humanBots;
};

#endif // MAP_H
