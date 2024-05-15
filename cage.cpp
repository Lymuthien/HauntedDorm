#include "cage.h"
#include <QPainter>

Cage::Cage(const QPixmap pixmap, QObject *parent)
    : QObject{parent}, QGraphicsItem(), _pixmap(pixmap)
{}

void Cage::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    painter->drawPixmap(QRect(0, 0, _pixmap.width(), _pixmap.height()), _pixmap);
}

QRectF Cage::boundingRect() const
{
    return QRectF(0, 0, _pixmap.width(), _pixmap.height());
}

void Cage::upgrade() {}

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
