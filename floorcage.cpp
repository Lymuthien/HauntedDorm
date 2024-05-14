#include "floorcage.h"

FloorCage::FloorCage(QPixmap pixmap, QObject *parent)
    : Cage{pixmap}, _emptyPixmap(pixmap)
{
    setType(UninitializedType);
}

void FloorCage::setBuilding(BuildingType type)
{
    switch (type) {
    case HookahType:
        //_pixmap =
        //_cost +=
        break;
    case TurretType:
        //_pixmap =
        //_cost +=
        break;
    case Cage::UninitializedType:
    case Cage::DoorType:
    case Cage::BedType:
    case Cage::Ps4Type:
    case Cage::DotaType:
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
    setType(UninitializedType);
    _free = true;
}


void FloorCage::clicked()
{
    if (_free) {
        if (_form == nullptr)
            _form = new AddBuildingForm(this);
        _form->show();
    }
    else {
        if (_upgradeForm == nullptr)
            _upgradeForm = new UpgrateForm(this);
        _upgradeForm->show();
    }

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
