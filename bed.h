#ifndef BED_H
#define BED_H

#include "cage.h"
#include "addbuildingform.h"

class Bed : public Cage
{
    Q_OBJECT
public:
    explicit Bed(QPixmap pixmap, QObject *parent = nullptr);

    void upgrade();
    void takeTheBed(QPixmap pixmap);
    bool isFree();
    int getMoneyPerSec();
    void clicked();

private:
    bool _free = true;
    int _moneyPerSec = 2;
};

#endif // BED_H
