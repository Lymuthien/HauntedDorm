#ifndef FLOORCAGE_H
#define FLOORCAGE_H

#include "cage.h"
#include "addbuildingform.h"
#include "upgrateform.h"

class FloorCage : public Cage
{
public:
    explicit FloorCage(QPixmap pixmap, int *money, int *energy, QObject *parent = nullptr);

    void setBuilding(BuildingType type);
    void deleteBuilding();
    bool visible();
    void setVisible(bool visible);
    bool free();
    void upgrade();
    int getMoneyPerSec();
    int getEnergyPerSec();
    void clicked();

private:
    AddBuildingForm* m_form = nullptr;
    UpgrateForm* m_upgradeForm = nullptr;
    QPixmap m_emptyPixmap;
    bool m_free = true, m_visible = false;
    int m_moneyPerSec = 0, m_energyPerSec = 0;
};

#endif // FLOORCAGE_H
