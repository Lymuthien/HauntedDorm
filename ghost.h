#ifndef GHOST_H
#define GHOST_H

#include <QObject>
#include "human.h"
#include "qtimer.h"
#include "room.h"

class Ghost : public Human
{
    Q_OBJECT
public:
    explicit Ghost(QPixmap pixmap, QVector<Room *>* rooms, QVector<QPoint> hillPoints, int width = 50, int height = 100, QObject *parent = nullptr);

    void findRandomRoom(QVector<Room *>* room, int roomNum = 0);
    int getHp();
    void setHp (int hp);
    void upgrade();
    int getMaxHp();
    int getDamage();

signals:
    void moved();

private:
    void goToHillZone();
    void goToPoint(QPointF point);

    int _hp = 512;
    int _maxHp = 512;
    int _damage = 2;
    QTimer* hillTimer;
    QTimer* findRoomTimer;
    QVector<QPoint> _hillPoints;
    QTimer* toXTimer = nullptr;
    QTimer* toYTimer = nullptr;
    QVector<Room*>* rooms;
};

#endif // GHOST_H
