#ifndef GHOST_H
#define GHOST_H

#include <QObject>
#include "human.h"
#include "qtimer.h"

class Ghost : public Human
{
    Q_OBJECT
public:
    explicit Ghost(QPixmap pixmap, QVector<QPoint> hillPoints, int width = 50, int height = 100, QObject *parent = nullptr);

    Human* findPeopleWithoutRoom(QVector<Human*> humans);
    void findRandomRoom();
    int getHp();
    void setHp (int hp);
    void upgrade();
    int getMaxHp();

signals:
    void moved();

private:
    void goToHillZone();
    void goToPoint(QPointF point);

    int _hp = 512;
    int _maxHp = 512;
    QTimer* hillTimer;
    QVector<QPoint> _hillPoints;
};

#endif // GHOST_H
