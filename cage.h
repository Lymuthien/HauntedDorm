#ifndef CAGE_H
#define CAGE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class Cage : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Cage(const QPixmap pixmap, QObject *parent = nullptr);

    enum BuildingType {
        UninitializedType,
        DoorType,
        BedType,
        HookahType,
        ShellyType,
        Ps4Type,
        DotaType
    };

    QRectF boundingRect() const;
    virtual void upgrade();
    BuildingType getType();
    void setType(BuildingType type);
    QString getTypeString();
    QPixmap getPixmap();

protected:
    QPixmap _pixmap;

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
    BuildingType _type;
};

#endif // CAGE_H
