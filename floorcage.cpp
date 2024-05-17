#include "floorcage.h"

FloorCage::FloorCage(QPixmap pixmap, int* money, int* energy, QObject *parent)
    : Cage{pixmap, money, energy}, m_emptyPixmap(pixmap) {
    setType(UninitializedType);
}

void FloorCage::setBuilding(BuildingType type) {
    if (getType() != UninitializedType && type != UninitializedType) return;
    switch (type) {
    case UninitializedType:
        deleteBuilding();
        return;
    case HookahType:
        if (getCurrentEnergy() > 256) {
            _pixmap = QPixmap(":/images/resourses/images/hookah.png");
            setEnergyCost(getEnergyCost() + 256);
            setCurrentEnergy(getCurrentEnergy() - 256);
            setType(type);
        }
        break;
    case ShellyType:
        if (getCurrentMoney() > 8) {
            _pixmap = QPixmap(":/images/resourses/images/shelly.png");
            setMoneyCost(getMoneyCost() + 8);
            setCurrentMoney(getCurrentMoney() - 8);
            setType(type);
        }
        break;
    case Ps4Type:
        if (getCurrentMoney() > 200) {
            _pixmap = QPixmap(":/images/resourses/images/ps4.png");
            setMoneyCost(getMoneyCost() + 200);
            setCurrentMoney(getCurrentMoney() - 200);
            setType(type);
        }
        break;
    case DotaType:
        if (getCurrentEnergy() > 128) {
            _pixmap = QPixmap(":/images/resourses/images/dota.png");
            setEnergyCost(getEnergyCost() + 128);
            setCurrentEnergy(getCurrentEnergy() - 128);
            setType(type);
        }
        break;
    case HammerType:
        if (getCurrentEnergy() > 512) {
            _pixmap = QPixmap(":/images/resourses/images/hammer.png");
            setEnergyCost(getEnergyCost() + 512);
            setCurrentEnergy(getCurrentEnergy() - 512);
            setType(type);
        }
        break;
    case SixBybeType:
        if (getCurrentEnergy() > 1024) {
            _pixmap = QPixmap(":/images/resourses/images/6-bybe.png");
            setEnergyCost(getEnergyCost() + 1024);
            setCurrentEnergy(getCurrentEnergy() - 1024);
            setType(type);
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

void FloorCage::deleteBuilding() {
    m_moneyPerSec = 0;
    m_energyPerSec = 0;
    setCurrentMoney(getCurrentMoney() + getMoneyCost() * 0.75);
    setCurrentEnergy(getCurrentEnergy() + getEnergyCost() * 0.75);
    setMoneyCost(0);
    setEnergyCost(0);
    _pixmap = m_emptyPixmap;
    update();
    setType(UninitializedType);
    setVisible(m_visible);
    m_free = true;
}

void FloorCage::clicked() {
    if (getType() == UninitializedType) {
        if (m_form == nullptr) {
            m_form = new AddBuildingForm(this);
            connect(m_form, &AddBuildingForm::addBuilding, this, &FloorCage::setBuilding);
        }
        m_form->show();
    }
    else {
        if (m_upgradeForm == nullptr)
            m_upgradeForm = new UpgrateForm(this);
        m_upgradeForm->show();
    }

}

bool FloorCage::visible() {
    return m_visible;
}

void FloorCage::setVisible(bool visible) {
    if (visible)
        show();
    else
        hide();
    m_visible = visible;
}

bool FloorCage::free() {
    return m_free;
}

void FloorCage::upgrade()
{
    m_moneyPerSec *= 2;
    m_energyPerSec *= 2;
    Cage::upgrade();

}

int FloorCage::getMoneyPerSec() {
    return m_moneyPerSec;
}

int FloorCage::getEnergyPerSec() {
    return m_energyPerSec;
}
