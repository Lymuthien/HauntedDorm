#include "floorcage.h"

FloorCage::FloorCage(QPixmap pixmap, QObject *parent)
    : Cage{pixmap}, _emptyPixmap(pixmap)
{}

void FloorCage::setBuilding(BuildingType type)
{
    switch (type) {
    case Hookah:
        //_pixmap =
        //_cost +=
        break;
    case Turret:
        //_pixmap =
        //_cost +=
        break;
    case Bottle:
        //_pixmap =
        //_cost +=
        break;
    }
    this->update();
    _free = false;
    _visible = true;
}

void FloorCage::deleteBuilding()
{
    _moneyPerSec = 0;
    _energyPerSec = 0;
    _cost = 0;
    _pixmap = _emptyPixmap;
    _free = true;
    //извне ставится setVisible при вызове
}

void FloorCage::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (_free) //вызов меню постройки
        ;
    else
        //вызов меню улучшения
        ;
    QGraphicsItem::mousePressEvent(event);
}

bool FloorCage::isVisible()
{
    return _visible;
}

void FloorCage::setVisible(bool visible)
{
    if (visible)
        show();
    else
        hide();
    _visible = visible;
}

bool FloorCage::isFree()
{
    return _free;
}

void FloorCage::upgrade()
{

}

int FloorCage::getMoneyPerSec()
{
    return _moneyPerSec;
}

int FloorCage::getEnergyPerSec()
{
    return _energyPerSec;
}

int FloorCage::getCost()
{
    return _cost;
}
