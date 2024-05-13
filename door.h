#ifndef DOOR_H
#define DOOR_H

#include "cage.h"

class Door : public Cage
{
public:
    explicit Door(QPixmap pixmap, QObject *parent = nullptr);
    void upgrade();
    void changePixmap(QPixmap pixmap);
    int getMaxHp();
    int getHp();
    void setHp(int hp);

private slots:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int _maxHp = 512;
    int _hp = 512;
};

#endif // DOOR_H
