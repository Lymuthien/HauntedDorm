#ifndef HUMAN_H
#define HUMAN_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

#include "room.h"

class Human : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Human(const QPixmap pixmap, QObject *parent = nullptr);

    void Move(int x, int y);
    bool processCollidings(QList<QGraphicsItem *> collidins);

    QRectF boundingRect() const;

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

    int _money = 0;
    int _energy = 0;
    Room* _room;
    QPointF _posBeforeCollision;
    QPixmap _pixmap;

};

#endif // HUMAN_H
