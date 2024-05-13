#include "cage.h"
#include <QPainter>

Cage::Cage(const QPixmap pixmap, QObject *parent)
    : QObject{parent}, QGraphicsItem(), _pixmap(pixmap)
{}

void Cage::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawPixmap(QRect(0, 0, _pixmap.width(), _pixmap.height()), _pixmap);
}

QRectF Cage::boundingRect() const
{
    return QRectF(0, 0, _pixmap.width(), _pixmap.height());
}

void Cage::upgrade() {}
