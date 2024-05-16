#ifndef CAGE_H
#define CAGE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class Cage : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Cage(const QPixmap pixmap, int* _currentMoney = nullptr, int* _currentEnergy = nullptr, QObject *parent = nullptr);

    enum BuildingType {
        UninitializedType,
        DoorType,
        BedType,
        HookahType,
        ShellyType,
        Ps4Type,
        DotaType,
        HammerType,
        SixBybeType
    };

    QRectF boundingRect() const;
    virtual void upgrade();
    BuildingType getType();
    void setType(BuildingType type);
    QString getTypeString();
    QPixmap getPixmap();
    int getMoneyCost();
    void setMoneyCost(int cost);
    int getEnergyCost();
    void setEnergyCost(int cost);
    int getCurrentMoney();
    void setCurrentMoney(int _money);
    int getCurrentEnergy();
    void setCurrentEnergy(int _energy);

protected:
    QPixmap _pixmap;

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
    BuildingType _type;
    int _moneyCost = 0;
    int _energyCost = 0;
    int* m_currentMoney = nullptr;
    int* m_currentEnergy = nullptr;
};

#endif // CAGE_H
