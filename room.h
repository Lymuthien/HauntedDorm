#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include "cage.h"
#include "bed.h"
#include "door.h"
#include "floorcage.h"

#include <QVector>
#include <QGraphicsItem>
#include <QPushButton>

class Room : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit Room(bool doorUp, QObject *parent = nullptr);

    void setFree(bool status);
    bool isFree();
    Door* getDoor();
    Bed* getBed();
    QPushButton* getSleepBtn();
    void startOpeningDoor();
    void startClosingDoor();
    void showSleepBtn(bool show);
    void createSleepButton(QWidget* w);

signals:

private:
    void moveDoor(bool open);
    void setDoorCoordinates(bool doorUp, QPointF pos1, QPointF pos2);
    void addFloor(int maxI, int maxJ);
    void addAllItems();
    void showInteractingCages();
    void buildRoom1(bool doorUp, int flag = 0);
    void buildRoom2(bool doorUp, int flag = 0);
    void buildRoom3(bool doorUp, int flag = 0);
    void buildRoom4(bool doorUp, int flag = 0);


    QVector<QGraphicsPixmapItem*> _floor;
    QVector<Cage*> _walls;
    QVector<FloorCage*> _interactFloor;
    Bed* _bed;
    Door* _door;
    QTimer* openDoorTimer;
    QTimer* closeDoorTimer;
    int _wallCount = 0;
    bool _free = true;
    QPointF beginDoorPos;
    QPushButton* sleepBtn;
};

#endif // ROOM_H







