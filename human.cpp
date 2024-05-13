#include "human.h"
#include "cage.h"
#include "qgraphicsscene.h"

#include <QPainter>

Human::Human(const QPixmap pixmap, QObject *parent)
    : QObject{parent}, QGraphicsItem(), _pixmap(pixmap)
{}

void Human::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QPointF currentPos = pos();
    QList<QGraphicsItem *> colliding = scene()->collidingItems(this);

    if (processCollidings(colliding) == false)
        setPos(_posBeforeCollision);
    else
        _posBeforeCollision = currentPos;

    painter->drawPixmap(QRect(0, 0, 50, 100), _pixmap);
}

QRectF Human::boundingRect() const
{
    return QRectF(0, 0, 50, 100);
}

bool Human::processCollidings(QList<QGraphicsItem *> collidins) {
    bool can_move = true;
    for (QGraphicsItem* item : collidins) {
        if (dynamic_cast<Cage*> (item))
            can_move = false;
    }
    return can_move;
}

