#ifndef ROOM_H
#define ROOM_H

#include <QObject>
#include "cage.h"
#include "bed.h"
#include "door.h"
#include "floorcage.h"
#include "human.h"

#include <QVector>
#include <QGraphicsItem>
#include <QPushButton>

class Room : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    explicit Room(bool doorUp, QObject *parent = nullptr);
    ~Room();

    void setFree(bool status);
    bool isFree();
    void setHuman(Human* human);
    Door* getDoor();
    Bed* getBed();
    QPushButton* getSleepBtn();
    void startOpeningDoor();
    void startClosingDoor();
    void showSleepBtn(bool show);
    void createSleepButton(QWidget* w);
    QVector<FloorCage*> getInteractFloor();

signals:
    void sleepBtnClicked();

private:
    void moveDoor(bool open);
    void createInteractBtns(QWidget* w);
    void setDoorCoordinates(bool doorUp, QPointF pos1, QPointF pos2);
    void addFloor(int maxI, int maxJ);
    void addAllItems();
    void showInteractingCages();
    void buildRoom1(bool doorUp, int flag = 0);
    void buildRoom2(bool doorUp, int flag = 0);
    void buildRoom3(bool doorUp, int flag = 0);
    void buildRoom4(bool doorUp, int flag = 0);

    QVector<FloorCage*> _interactFloor;
    QVector<QGraphicsPixmapItem*> _floor;
    QVector<Cage*> _walls;
    Bed* _bed;
    Door* _door;
    QTimer* _openDoorTimer;
    QTimer* _closeDoorTimer;
    int _wallCount = 0;
    bool _free = true;
    QPointF _beginDoorPos;
    QPushButton* _sleepBtn;
    QVector<QPushButton*> _interactBtns;
    Human* _human;
};

#endif // ROOM_H







