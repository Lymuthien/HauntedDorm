#ifndef BED_H
#define BED_H

#include "cage.h"
#include "upgrateform.h"

class Bed : public Cage
{
    Q_OBJECT
public:
    explicit Bed(QPixmap pixmap, int *money, int *energy, QObject *parent = nullptr);
    ~Bed();

    bool upgrade();
    void takeTheBed(QPixmap pixmap);
    int moneyPerSec();
    void clicked();

private:
    int m_moneyPerSec = 1;
    UpgrateForm* m_form = nullptr;
};

#endif // BED_H
