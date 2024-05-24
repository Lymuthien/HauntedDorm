#include "bed.h"

Bed::Bed(QPixmap pixmap, int* money, int* energy, QObject *parent)
    : Cage(pixmap, money, energy)
{
    setType(BedType);
    setMoneyCost(13);
}

Bed::~Bed() {
    delete m_form;
}

bool Bed::upgrade() {
    if (Cage::upgrade())
        m_moneyPerSec *= 2;
    return true;
}

void Bed::takeTheBed(QPixmap pixmap) {
    _pixmap = pixmap;
    update();
}

void Bed::clicked() {
    if (m_form == nullptr)
        m_form = new UpgrateForm(this);
    m_form->show();
}

int Bed::moneyPerSec() {
    return m_moneyPerSec;
}
