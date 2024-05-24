#include "floorcage.h"
#include <QTimer>

FloorCage::FloorCage(QPixmap pixmap, int* money, int* energy, QObject *parent)
    : Cage{pixmap, money, energy}
    , m_attackTimer(new QTimer)
    , m_emptyPixmap(pixmap)
{
    m_attackTimer->setInterval(1000);
    connect(m_attackTimer, &QTimer::timeout, this, [=]() {emit attackGhost(this);});
    setType(UninitializedType);
}

FloorCage::~FloorCage()
{
    m_attackTimer->stop();
    delete m_attackTimer;
    delete m_form;
    delete m_upgradeForm;
}

void FloorCage::setBuilding(BuildingType type)
{
    if (getType() != UninitializedType && type != UninitializedType) return;

    switch (type) {
    case UninitializedType:
        deleteBuilding();
        return;
    case HookahType:
        if (currentEnergy() > 256) {
            _pixmap = QPixmap(":/images/resourses/images/hookah.png");
            setEnergyCost(energyCost() + 256);
            setCurrentEnergy(currentEnergy() - 256);
            setType(type);
            emit addFunction(HookahType);
        }
        break;
    case ShellyType:
        if (currentMoney() > 8) {
            _pixmap = QPixmap(":/images/resourses/images/shelly.png");
            m_damagePerSec = 1;
            m_attackTimer->start();
            setMoneyCost(moneyCost() + 8);
            setCurrentMoney(currentMoney() - 8);
            setType(type);
        }
        break;
    case Ps4Type:
        if (currentMoney() > 200) {
            _pixmap = QPixmap(":/images/resourses/images/ps4.png");
            setMoneyCost(moneyCost() + 200);
            setCurrentMoney(currentMoney() - 200);
            setType(type);
        }
        break;
    case DotaType:
        if (currentEnergy() > 128) {
            _pixmap = QPixmap(":/images/resourses/images/dota2.png");
            setEnergyCost(energyCost() + 128);
            setCurrentEnergy(currentEnergy() - 128);
            setType(type);
            emit addFunction(DotaType);
        }
        break;
    case HammerType:
        if (currentEnergy() > 512) {
            _pixmap = QPixmap(":/images/resourses/images/hammer.png");
            setEnergyCost(energyCost() + 512);
            setCurrentEnergy(currentEnergy() - 512);
            setType(type);
            emit addFunction(HammerType);
        }
        break;
    case SixBybeType:
        if (currentEnergy() > 1024) {
            _pixmap = QPixmap(":/images/resourses/images/6-bybe.png");
            setEnergyCost(energyCost() + 1024);
            setCurrentEnergy(currentEnergy() - 1024);
            setType(type);
            emit addFunction(SixBybeType);
        }
        break;
    default:
        break;
    }

    update();
    if (m_upgradeForm != nullptr) m_upgradeForm->updateText();
    m_free = false;
    show();
}

void FloorCage::deleteBuilding()
{
    if (m_attackTimer->isActive())
        m_attackTimer->stop();
    m_moneyPerSec = 0;
    m_energyPerSec = 0;
    m_attackTimer->stop();
    setCurrentMoney(currentMoney() + moneyCost() * 0.75);
    setCurrentEnergy(currentEnergy() + energyCost() * 0.75);
    _pixmap = m_emptyPixmap;
    setType(UninitializedType);
    setVisible(m_visible);
    m_free = true;
    update();
    Cage::deleteBuilding();
}

void FloorCage::clicked()
{
    if (getType() == HookahType || getType() == DotaType || getType() == HammerType || getType() == SixBybeType)
        return;
    if (getType() == UninitializedType)
    {
        if (m_form == nullptr)
        {
            m_form = new AddBuildingForm(this);
            connect(m_form, &AddBuildingForm::addBuilding, this, &FloorCage::setBuilding);
        }
        m_form->show();
    }
    else
    {
        if (m_upgradeForm == nullptr)
            m_upgradeForm = new UpgrateForm(this);
        m_upgradeForm->show();
    }
}

bool FloorCage::visible()
{
    return m_visible;
}

void FloorCage::setVisible(bool visible)
{
    if (visible)
        show();
    else
        hide();
    m_visible = visible;
}

bool FloorCage::free()
{
    return m_free;
}

bool FloorCage::upgrade()
{
    if (Cage::upgrade())
    {
        m_moneyPerSec *= 2;
        m_energyPerSec *= 2;
        m_damagePerSec *= 2;
    }
    return true;
}

int FloorCage::moneyPerSec()
{
    return m_moneyPerSec;
}

int FloorCage::energyPerSec()
{
    return m_energyPerSec;
}

int FloorCage::damagePerSec()
{
    return m_damagePerSec;
}
