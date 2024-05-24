#include "door.h"

Door::Door(QPixmap pixmap, int *money, int *energy, QObject *parent)
    : Cage{pixmap, money, energy}
{
    setType(DoorType);
    setMoneyCost(25);
}

Door::~Door()
{
    delete m_form;
}

bool Door::upgrade()
{
    if (Cage::upgrade())
    {
        m_maxHp *= 2;
        m_hp = m_maxHp;
        emit hpChanged();
    }

    return true;
}

void Door::changePixmap(QPixmap pixmap)
{
    _pixmap = pixmap;
    update();
}

void Door::clicked()
{
    if (m_form == nullptr)
        m_form = new UpgrateForm(this);

    m_form->show();
}

int Door::maxHp()
{
    return m_maxHp;
}

int Door::hp()
{
    return m_hp;
}

void Door::setHp(int hp)
{
    m_hp = hp;
    if (m_hp <= 0)
    {
        delete this;
        return;
    }

    emit hpChanged();
}
