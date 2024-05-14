#include "door.h"

Door::Door(QPixmap pixmap, QObject *parent)
    : Cage{pixmap}
{
    setType(DoorType);
}

void Door::upgrade()
{
    _maxHp *= 2;
    _hp = _maxHp;
}

void Door::changePixmap(QPixmap pixmap)
{
    _pixmap = pixmap;
    this->update();
}

void Door::clicked()
{
    //вызов меню улучшения
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
