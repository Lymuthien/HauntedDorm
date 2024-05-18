#ifndef FLOORCAGE_H
#define FLOORCAGE_H

#include <QObject>
#include "cage.h"
#include "addbuildingform.h"
#include "upgrateform.h"

class FloorCage : public Cage
{
    Q_OBJECT
public:
    explicit FloorCage(QPixmap pixmap, int *money, int *energy, QObject *parent = nullptr);
    ~FloorCage();

    void setBuilding(BuildingType type);
    void deleteBuilding();
    bool visible();
    void setVisible(bool visible);
    bool free();
    bool upgrade();
    int moneyPerSec();
    int energyPerSec();
    int damagePerSec();
    void clicked();

signals:
    void attackGhost(FloorCage* _cage);
    void addFunction(BuildingType _type);

private:
    QTimer* m_attackTimer;
    AddBuildingForm* m_form = nullptr;
    UpgrateForm* m_upgradeForm = nullptr;
    QPixmap m_emptyPixmap;
    bool m_free = true, m_visible = false;
    int m_moneyPerSec = 0, m_energyPerSec = 0, m_damagePerSec = 0;
};

#endif // FLOORCAGE_H


