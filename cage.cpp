#include "cage.h"
#include <QPainter>

Cage::Cage(const QPixmap pixmap, int* _currentMoney, int* _currentEnergy, QObject *parent)
    : QObject{parent}, QGraphicsItem(), _pixmap(pixmap), m_currentMoney(_currentMoney), m_currentEnergy(_currentEnergy)
{}

void Cage::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawPixmap(QRect(0, 0, _pixmap.width(), _pixmap.height()), _pixmap);
}

QRectF Cage::boundingRect() const
{
    return QRectF(0, 0, _pixmap.width(), _pixmap.height());
}

Cage::BuildingType Cage::getType() {
    return _type;
}

QString Cage::getTypeString() {
    switch(_type) {
    case UninitializedType:
        return "Uninitialized";
    case DoorType:
        return "Door";
    case BedType:
        return "Bed";
    case HookahType:
        return "Hookah";
    case ShellyType:
        return "Shelly";
    case Ps4Type:
        return "PS4";
    case DotaType:
        return "Dota";
    default:
        return "Unknown";
    }
}

QPixmap Cage::getPixmap() {
    return _pixmap;
}


void Cage::setType(BuildingType type) {
    _type = type;
}

void Cage::upgrade() {
    *m_currentMoney -= _moneyCost * 2;
    *m_currentEnergy -= _energyCost * 2;
    _moneyCost *= 2;
    _energyCost *= 2;
}


int Cage::getMoneyCost() {
    return _moneyCost;
}

void Cage::setMoneyCost(int cost) {
    _moneyCost = cost;
}

int Cage::getEnergyCost() {
    return _energyCost;
}

void Cage::setEnergyCost(int cost) {
    _energyCost = cost;
}

int Cage::getCurrentMoney() {
    return *m_currentMoney;
}

void Cage::setCurrentMoney(int _money) {
    *m_currentMoney = _money;
}

int Cage::getCurrentEnergy() {
    return *m_currentEnergy;
}

void Cage::setCurrentEnergy(int _energy) {
    *m_currentEnergy = _energy;
}
