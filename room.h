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
    Door* door();
    Bed* bed();
    QPushButton* sleepBtn();
    void startOpeningDoor();
    void startClosingDoor();
    void createSleepButton(QWidget* w);
    QVector<FloorCage*> getInteractFloor();

signals:
    void sleepBtnClicked();
    void coinsChanged(int money, int energy);

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
    void initCycle();

    bool m_free = true;
    int m_money = 0, m_energy = 0, m_wallCount = 0;
    QPointF m_beginDoorPos;
    QTimer* m_openDoorTimer;
    QTimer* m_closeDoorTimer;
    QTimer* m_gameCycleTimer;
    QPushButton* m_sleepBtn;
    QVector<QPushButton*> m_interactBtns;
    QVector<FloorCage*> m_interactFloor;
    QVector<QGraphicsPixmapItem*> m_floor;
    QVector<Cage*> m_walls;
    Bed* m_bed;
    Door* m_door;
    Human* m_human;
};

#endif // ROOM_H







