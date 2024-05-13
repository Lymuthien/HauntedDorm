#include "room.h"
#include "cage.h"

#include <QRandomGenerator>
#include <QTimer>
#include <QPushButton>
#include <QStyle>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

Room::Room(bool doorUp, QObject* parent)
    : QObject{parent}, QGraphicsItemGroup(), _bed(new Bed(QPixmap(":/images/resourses/images/bed.png")))
    , _door(new Door(QPixmap(":/images/resourses/images/door.jpg"))), openDoorTimer(new QTimer(this)), closeDoorTimer(new QTimer(this))
{
    for (int i = 0; i < 14; ++i)
        _interactFloor.append(new FloorCage(QPixmap(":/images/resourses/images/addBuilding-cage.png")));

    int roomNumber = QRandomGenerator::global()->bounded(1, 5);

    if (roomNumber == 1) buildRoom1(doorUp);
    else if (roomNumber == 2) buildRoom2(doorUp);
    else if (roomNumber == 3) buildRoom3(doorUp);
    else if (roomNumber == 4) buildRoom4(doorUp);

    openDoorTimer->setInterval(30);
    closeDoorTimer->setInterval(30);
    connect(openDoorTimer, &QTimer::timeout, this, [=]() { moveDoor(true); });
    connect(closeDoorTimer, &QTimer::timeout, this, [=]() { moveDoor(false); });

    for (int i = 0; i < 14; ++i)
        _interactFloor[i]->setVisible(false);

    addAllItems();
}

void Room::createSleepButton(QWidget* w) {
    sleepBtn = new QPushButton("СПАТЬ", w);
    connect(sleepBtn, &QPushButton::clicked, this, [=]() {
        emit sleepBtnClicked();
        setFree(false);
        createInteractBtns(w);
        showInteractingCages();
    });
    sleepBtn->setGeometry(_bed->x()+this->x()-42, _bed->y()+this->y()+57*2, 85, 25);
}

void Room::createInteractBtns(QWidget* w) {
    for (int i = 0; i < _interactFloor.count(); ++i) {
        _interactBtns.append(new QPushButton("+", w));
        _interactBtns[i]->setStyleSheet("QPushButton { background: rgba(213, 213, 214, 0.2);"
                              "font: 25px; border: 10px white; color: white; }"
                              "QPushButton:hover { background: rgba(213, 213, 214, 0.1); }"
                              "QPushButton:pressed { background: rgba(190, 190, 191, 0.5); }");
        connect(_interactBtns[i], &QPushButton::clicked, _interactFloor[i], &FloorCage::clicked);
        _interactBtns[i]->setGeometry(_interactFloor[i]->x() + this->x() + 13, _interactFloor[i]->y()+this->y() + 13, 30, 30);
        _interactBtns[i]->hide();
    }
}


void Room::showInteractingCages() {
    for (int i = 0; i < _interactFloor.count(); ++i) {
        _interactFloor[i]->setVisible(true);
        _interactBtns[i]->show();
    }
}

void Room::setFree(bool status) {
    _free = status;
}

bool Room::isFree() {
    return _free;
}

QPushButton* Room::getSleepBtn() {
    return sleepBtn;
}

QVector<FloorCage*> Room::getInteractFloor() {
    return _interactFloor;
}

Door* Room::getDoor() {
    return _door;
}

Bed* Room::getBed() {
    return _bed;
}

void Room::startOpeningDoor() {
    closeDoorTimer->stop();
    openDoorTimer->start();
}

void Room::startClosingDoor() {
    openDoorTimer->stop();
    closeDoorTimer->start();
}

void Room::showSleepBtn(bool show) {
    if (show)
        sleepBtn->show();
    else
        sleepBtn->hide();
}

void Room::moveDoor(bool open) {
    if (open)
        if(abs(beginDoorPos.x()-_door->pos().x()) == 57)
            openDoorTimer->stop();
        else
            _door->setPos(_door->pos().x() - 3, _door->pos().y());
    else
        if(abs(beginDoorPos.x()-_door->pos().x()) == 0)
            closeDoorTimer->stop();
        else
            _door->setPos(_door->pos().x() + 3, _door->pos().y());
}

void Room::setDoorCoordinates(bool doorUp, QPointF pos1, QPointF pos2) {
    if (doorUp)
    {
        _floor[_floor.count() - 1]->setPos(pos1);
        _door->setPos(pos1);
    } else {
        _floor[_floor.count() - 1]->setPos(pos2);
        _door->setPos(pos2);
    }
    beginDoorPos = _door->pos();
}

void Room::addAllItems() {
    for (int i = 0; i < _floor.count(); ++i)
        addToGroup(_floor[i]);
    addToGroup(_bed);
    addToGroup(_door);
    for (int i = 0; i < _wallCount; ++i)
        addToGroup(_walls[i]);
    for (int i = 0; i < _interactFloor.count(); ++i)
        addToGroup(_interactFloor[i]);
}

void Room::addFloor(int maxI, int maxJ) {
    _floor.append(new QGraphicsPixmapItem(QPixmap(":/images/resourses/images/floor-room-cage.jpg")));
    for (int i = 0; i < maxI; ++i)
        for (int j = 0; j < maxJ; ++j) {
            _floor.append(new QGraphicsPixmapItem(QPixmap(":/images/resourses/images/floor-room-cage.jpg")));
            _floor[i*maxJ + j]->setPos(57*(1+j),57*(1+i));
        }
}

void Room::buildRoom1(bool doorUp, int flag) {
    for (int i = 0; i < 6; ++i)
        _interactFloor[i]->setPos(57*(1+i),57);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            _interactFloor[6+i*3+j]->setPos(57*(1+j),57*(2+i));
    for (int i = 0; i < 2; ++i)
        _interactFloor[12+i]->setPos(57*(1+i),57*4);

    for (int i = 0; i < 21; ++i)
        _floor.append(new QGraphicsPixmapItem(QPixmap(":/images/resourses/images/floor-room-cage.jpg")));
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 6; ++j)
            _floor[i*6 + j]->setPos(57*(1+j),57*(1+i));
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 4; ++j)
            _floor[12 + i*4 + j]->setPos(57*(1+j),57*(3+i));

    for (int i = 0; i < 24; ++i)
        _walls.append(new Cage(QPixmap(":/images/resourses/images/room-wall.jpg")));

    for (int i = 0; i < 6; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(0, 57*i);
    flag = doorUp ? 0 : -1;
    for (int i = 0; i < 3 + flag; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*(i - flag + 1), 57*5);
    for (int i = 0; i < 3; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*(i+3), 57*4);
    for (int i = 0; i < 2; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*5, 57*(3-i));
    for (int i = 0; i < 2; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*(6+i), 57*2);
    for (int i = 0; i < 2; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*7, 57*(1-i));
    flag = doorUp ? -1 : 0;
    for (int i = 0; i < 6 + flag; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*(6-i), 0);

    _bed->setPos(57*4, 57*2);
    setDoorCoordinates(doorUp, QPointF(57, 0), QPointF(57, 57*5));
}

void Room::buildRoom2(bool doorUp, int flag) {
    addFloor(3, 6);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 5; ++j)
            _interactFloor[i*5+j]->setPos(57*(2+j), 57*(1+i));
    for (int i = 0; i < 4; ++i)
        _interactFloor[10+i]->setPos(57*(3+i), 57*3);

    for (int i = 0; i < 22; ++i)
        _walls.append(new Cage(QPixmap(":/images/resourses/images/room-wall.jpg")));

    for (int i = 0; i < 4; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(0, 57*i);
    for (int i = 0; i < 2; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*(i+1), 57*3);
    flag = doorUp ? 0 : -2;
    for (int i = 0; i < 6 + flag; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*(i+2), 57*4);
    flag = doorUp ? 0 : +1;
    for (int i = 0; i < 4 + flag; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*7, 57*(3 + flag - i));
    flag = doorUp ? -1 : 0;
    for (int i = 0; i < 6 + flag; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*(6 + flag - i), 0);

    _bed->setPos(57, 57);
    setDoorCoordinates(doorUp, QPointF(57*6, 0), QPointF(57*6, 57*4));
}

void Room::buildRoom3(bool doorUp, int flag) {
    addFloor(3, 6);
    for (int i = 0; i < 4; ++i)
        _interactFloor[i]->setPos(57*(2+i), 57);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 5; ++j)
            _interactFloor[4+i*5+j]->setPos(57*(1+j), 57*(2+i));

    for (int i = 0; i < 22; ++i)
        _walls.append(new Cage(QPixmap(":/images/resourses/images/room-wall.jpg")));

    for (int i = 0; i < 4; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(0, 57*(i+1));
    flag = doorUp ? 0 : -1;
    for (int i = 0; i < 7 + flag; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*(i - flag + 1), 57*4);
    for (int i = 0; i < 3; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*7, 57*(3-i));
    for (int i = 0; i < 2; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*6, 57*(1-i));
    flag = doorUp ? -1 : 0;
    for (int i = 0; i < 5 + flag; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*(5 + flag - i), 0);
    _walls[_wallCount]->setPos(57, 57);
    ++_wallCount;

    _bed->setPos(57*6, 57*2);
    setDoorCoordinates(doorUp, QPointF(57*5, 0), QPointF(57, 57*4));
}

void Room::buildRoom4(bool doorUp, int flag) {
    addFloor(4, 4);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            _interactFloor[i*3+j]->setPos(57*(1+j), 57*(1+i));
    for (int i = 0; i < 2; ++i)
        _interactFloor[12+i]->setPos(57*4, 57*(3+i));

    for (int i = 0; i < 20; ++i)
        _walls.append(new Cage(QPixmap(":/images/resourses/images/room-wall.jpg")));

    for (int i = 0; i < 6; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(0, 57*i);
    flag = doorUp ? 0 : -1;
    for (int i = 0; i < 4 + flag; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*(i + 1), 57*5);
    for (int i = 0; i < 6; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*5, 57*(5-i));
    flag = doorUp ? -1 : 0;
    for (int i = 0; i < 4 + flag; ++i, ++_wallCount)
        _walls[_wallCount]->setPos(57*(4 - i), 0);

    _bed->setPos(57*4, 57);
    setDoorCoordinates(doorUp, QPointF(57, 0), QPointF(57*4, 57*5));
}

