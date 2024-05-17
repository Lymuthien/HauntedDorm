#include "bed.h"

Bed::Bed(QPixmap pixmap, int* money, int* energy, QObject *parent) : Cage(pixmap, money, energy) {
    setType(BedType);
    setMoneyCost(13);
}

void Bed::upgrade() {
    _moneyPerSec *= 2;
    Cage::upgrade();
}

void Bed::takeTheBed(QPixmap pixmap) {
    _pixmap = pixmap;
    this->update();
}

void Bed::clicked() {
    if (_form == nullptr)
        _form = new UpgrateForm(this);
    _form->show();
}

int Bed::getMoneyPerSec() {
    return _moneyPerSec;
}
