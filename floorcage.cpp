#include "floorcage.h"

FloorCage::FloorCage(QPixmap pixmap, int* money, int* energy, QObject *parent) : Cage{pixmap},
    _emptyPixmap(pixmap), humanMoney(money), humanEnergy(energy) {
    setType(UninitializedType);
}

void FloorCage::setBuilding(BuildingType type) {
    setType(type);
    switch (type) {
    case UninitializedType:
        deleteBuilding();
        return;
    case HookahType:
        _pixmap = QPixmap(":/images/resourses/images/hookah.png");
        _energyCost += 256;
        break;
    case ShellyType:
        _pixmap = QPixmap(":/images/resourses/images/shelly.png");
        _cost += 8;
        break;
    case Ps4Type:
        _pixmap = QPixmap(":/images/resourses/images/ps4.png");
        _cost += 200;
        break;
    case DotaType:
        _pixmap = QPixmap(":/images/resourses/images/dota.png");
        _energyCost += 128;
        break;
    case HammerType:
        _pixmap = QPixmap(":/images/resourses/images/hammer.png");
        _energyCost += 512;
        break;
    case SixBybeType:
        _pixmap = QPixmap(":/images/resourses/images/6-bybe.png");
        _energyCost += 1024;
        break;
    default:
        break;
    }

    update();
    _free = false;
    show();
}

void FloorCage::deleteBuilding() {
    _moneyPerSec = 0;
    _energyPerSec = 0;
    *humanMoney += _cost * 0.75;
    *humanEnergy += _energyCost * 0.75;
    _cost = 0;
    _energyCost = 0;
    _pixmap = _emptyPixmap;
    update();
    setType(UninitializedType);
    setVisible(_visible);
    _free = true;

}

void FloorCage::clicked() {
    if (_free) {
        if (_form == nullptr) {
            _form = new AddBuildingForm(this, humanMoney, humanEnergy);
            connect(_form, &AddBuildingForm::addBuilding, this, &FloorCage::setBuilding);
        }
        _form->show();
    }
    else {
        if (_upgradeForm == nullptr)
            _upgradeForm = new UpgrateForm(this);
        _upgradeForm->show();
    }

}

bool FloorCage::isVisible() {
    return _visible;
}

void FloorCage::setVisible(bool visible) {
    if (visible)
        show();
    else
        hide();
    _visible = visible;
}

bool FloorCage::isFree() {
    return _free;
}

void FloorCage::upgrade()
{
    int buffCost = _cost;
    if (_moneyPerSec) {
        _moneyPerSec *= 2;
        _cost += buffCost;
    }
    if (_energyPerSec) {
        _energyPerSec *= 0;
        _cost += buffCost;
    }
}

int FloorCage::getMoneyPerSec() {
    return _moneyPerSec;
}

int FloorCage::getEnergyPerSec() {
    return _energyPerSec;
}

int FloorCage::getCost() {
    return _cost;
}
