#include "bed.h"

Bed::Bed(QPixmap pixmap, QObject *parent)
    : Cage(pixmap)
{}

void Bed::upgrade()
{
    /* окно улучшения ->show
     * соблюдение условий прокачки во внешнем классе*/
}

bool Bed::isFree()
{
    return _free;
}

void Bed::takeTheBed(QPixmap pixmap)
{
    _pixmap = pixmap;
    _free = false;
    this->update();
}

void Bed::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //вызов меню улучшения
    QGraphicsItem::mousePressEvent(event);
}

int Bed::getMoneyPerSec()
{
    return _moneyPerSec;
}
