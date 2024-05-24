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
    ~Ghost();

    void findRandomRoom(QVector<Room *>* room, int roomNum = 0);
    int hp();
    void setHp (int hp);
    void setHitCount(int hitCount);
    int hitCount();
    void upgrade();
    int maxHp();
    int damage();

signals:
    void moved();
    void hpChanged();

private:
    void goToHillZone();
    void goToPoint(QPointF point);
    void heapify(QVector<Room*> roms, int n, int i);
    void heapSort(QVector<Room*> roms);

    struct Edge {
        int source, destination, weight;
        Edge(int s, int d, int w) : source(s), destination(d), weight(w) {}
    };
    QVector<int> bellmanFord(QVector<Edge>&edges, int numVertices, int source);

    int m_hp = 12, m_maxHp = 12, m_damage = 4, m_hitCount = 0;
    QTimer* m_hillTimer;
    QVector<QPoint> m_hillPoints;
    QTimer* m_toXTimer = nullptr;
    QTimer* m_toYTimer = nullptr;
    QVector<Room*>* m_rooms;
};

#endif // GHOST_H
