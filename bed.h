#ifndef BED_H
#define BED_H

#include "cage.h"
#include "upgrateform.h"

class Bed : public Cage
{
    Q_OBJECT
public:
    explicit Bed(QPixmap pixmap, QObject *parent = nullptr);

    void upgrade();
    void takeTheBed(QPixmap pixmap);
    int getMoneyPerSec();
    void clicked();

private:
    int _moneyPerSec = 2;
    UpgrateForm* _form = nullptr;
};

#endif // BED_H
