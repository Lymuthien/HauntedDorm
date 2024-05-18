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
    ~Door();

    bool upgrade();
    void changePixmap(QPixmap pixmap);
    int maxHp();
    int hp();
    void setHp(int hp);
    void clicked();

signals:
    void hpChanged();

private:
    int m_maxHp = 512;
    int m_hp = 512;
    UpgrateForm* m_form = nullptr;
};

#endif // DOOR_H
