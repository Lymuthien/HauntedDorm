#include "door.h"

Door::Door(QPixmap pixmap, QObject *parent) : Cage{pixmap} {
    setType(DoorType);
}

void Door::upgrade() {
    _maxHp *= 2;
    _hp = _maxHp;
    emit hpChanged();
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
