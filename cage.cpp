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

Cage::BuildingType Cage::getType()
{
    return _type;
}

int Cage::level()
{
    return m_level;
}

void Cage::deleteBuilding()
{
    m_level = 0;
    m_moneyCost = 0;
    m_energyCost = 0;
}

QString Cage::getTypeString()
{
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

QPixmap Cage::getPixmap()
{
    return _pixmap;
}

void Cage::setType(BuildingType type)
{
    _type = type;
}

bool Cage::upgrade()
{
    if (currentMoney() >= moneyCost() * 2 && currentEnergy() >= energyCost() *  2)
    {
        *m_currentMoney -= m_moneyCost * 2;
        *m_currentEnergy -= m_energyCost * 2;
        m_moneyCost *= 2;
        m_energyCost *= 2;
        m_level++;
        return true;
    }
    return false;
}

int Cage::moneyCost()
{
    return m_moneyCost;
}

void Cage::setMoneyCost(int cost)
{
    m_moneyCost = cost;
}

int Cage::energyCost()
{
    return m_energyCost;
}

void Cage::setEnergyCost(int cost)
{
    m_energyCost = cost;
}

int Cage::currentMoney()
{
    return *m_currentMoney;
}

void Cage::setCurrentMoney(int _money)
{
    *m_currentMoney = _money;
}

int Cage::currentEnergy()
{
    return *m_currentEnergy;
}

void Cage::setCurrentEnergy(int _energy)
{
    *m_currentEnergy = _energy;
}
