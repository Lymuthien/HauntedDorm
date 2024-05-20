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
        HookahType,
        DotaType,
        HammerType,
        SixBybeType,
        UninitializedType,
        DoorType,
        BedType,
        ShellyType,
        Ps4Type
    };
    BuildingType getType();

    QRectF boundingRect() const;

    virtual bool upgrade();
    virtual void deleteBuilding();

    void setType(BuildingType type);
    QString getTypeString();
    QPixmap getPixmap();
    int moneyCost();
    void setMoneyCost(int cost);
    int energyCost();
    void setEnergyCost(int cost);
    int currentMoney();
    void setCurrentMoney(int _money);
    int currentEnergy();
    void setCurrentEnergy(int _energy);
    int level();

protected:
    QPixmap _pixmap;

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

    BuildingType _type;
    int m_moneyCost = 0, m_energyCost = 0, m_level = 0;
    int* m_currentMoney = nullptr;
    int* m_currentEnergy = nullptr;
};

#endif // CAGE_H
