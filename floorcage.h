#ifndef FLOORCAGE_H
#define FLOORCAGE_H

#include "cage.h"
#include "addbuildingform.h"
#include "upgrateform.h"

class FloorCage : public Cage
{
public:
    explicit FloorCage(QPixmap pixmap, QObject *parent = nullptr);

    void setBuilding(BuildingType type);
    void deleteBuilding();
    bool isVisible();
    void setVisible(bool visible);
    bool isFree();
    void upgrade();
    int getMoneyPerSec();
    int getEnergyPerSec();
    int getCost();
    void clicked();

private:
    AddBuildingForm* _form = nullptr;
    UpgrateForm* _upgradeForm = nullptr;
    QPixmap _emptyPixmap;
    bool _free = true;
    bool _visible = false;
    int _moneyPerSec = 0;
    int _energyPerSec = 0;
    int _cost = 0;
};

#endif // FLOORCAGE_H