#include "door.h"

Door::Door(QPixmap pixmap, QObject *parent)
    : Cage{pixmap}
{}

void Door::upgrade()
{
    /* maxHp =
    */
    _hp = _maxHp;
}

void Door::changePixmap(QPixmap pixmap)
{
    _pixmap = pixmap;
    this->update();
}


void Door::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //вызов меню улучшения
    QGraphicsItem::mousePressEvent(event);
}

int Door::getMaxHp()
{
    return _maxHp;
}

int Door::getHp()
{
    return _hp;
}

void Door::setHp(int hp)
{
    _hp = hp;
}
