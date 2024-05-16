#ifndef DOOR_H
#define DOOR_H

#include <QObject>
#include "cage.h"
#include "upgrateform.h"

class Door : public Cage
{
    Q_OBJECT
public:
    explicit Door(QPixmap pixmap, int *money, int *energy, QObject *parent = nullptr);
    void upgrade();
    void changePixmap(QPixmap pixmap);
    int getMaxHp();
    int getHp();
    void setHp(int hp);
    void clicked();
    void createProgressBar(QWidget* w);

signals:
    void hpChanged();

private:
    int _maxHp = 512;
    int _hp = 512;
    UpgrateForm* _form = nullptr;
};

#endif // DOOR_H
