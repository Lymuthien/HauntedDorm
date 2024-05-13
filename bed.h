#ifndef BED_H
#define BED_H

#include "cage.h"

class Bed : public Cage
{
    Q_OBJECT
public:
    explicit Bed(QPixmap pixmap, QObject *parent = nullptr);

    void upgrade();
    void takeTheBed(QPixmap pixmap);
    bool isFree();
    int getMoneyPerSec();

private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool _free = true;
    int _moneyPerSec = 2;
};

#endif // BED_H
