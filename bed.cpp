#include "bed.h"

Bed::Bed(QPixmap pixmap, QObject *parent) : Cage(pixmap) {
    setType(BedType);
}

void Bed::upgrade() {
    _moneyPerSec *= 2;
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
