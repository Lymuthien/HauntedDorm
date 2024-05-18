#include "door.h"

Door::Door(QPixmap pixmap, int *money, int *energy, QObject *parent) : Cage{pixmap, money, energy} {
    setType(DoorType);
    setMoneyCost(25);
}

bool Door::upgrade() {
    if (Cage::upgrade()) {
        _maxHp *= 2;
        _hp = _maxHp;
        emit hpChanged();
    }
    return true;
}

void Door::changePixmap(QPixmap pixmap) {
    _pixmap = pixmap;
    this->update();
}

void Door::clicked() {
    if (_form == nullptr)
        _form = new UpgrateForm(this);
    _form->show();
}

int Door::getMaxHp() {
    return _maxHp;
}

int Door::getHp() {
    return _hp;
}

void Door::setHp(int hp) {
    _hp = hp;
    if (_hp <= 0) {
        delete this;
        return;
    }
    emit hpChanged();
}
