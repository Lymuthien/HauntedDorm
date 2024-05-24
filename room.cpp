#include "room.h"
#include "cage.h"

#include <QRandomGenerator>
#include <QTimer>
#include <QPushButton>
#include <QStyle>
#include <QGraphicsSceneMouseEvent>

Room::Room(bool doorUp, QObject* parent)
    : QObject{parent}, QGraphicsItemGroup(), m_openDoorTimer(new QTimer(this))
    , m_closeDoorTimer(new QTimer(this)), m_gameCycleTimer(new QTimer(this)), m_botCycleTimer(new QTimer(this))
    , m_bed(new Bed(QPixmap(":/images/resourses/images/bed.png"), &m_money, &m_energy))
    , m_door(new Door(QPixmap(":/images/resourses/images/door.jpg"), &m_money, &m_energy))
{
    for (int i = 0; i < 14; ++i) {
        m_interactFloor.append(new FloorCage(QPixmap(":/images/resourses/images/addBuilding-cage.png"), &m_money, &m_energy));
        connect(m_interactFloor[i], &FloorCage::attackGhost, this, &Room::attackGhost);
        connect(m_interactFloor[i], &FloorCage::addFunction, this, &Room::addFunction);
    }

    int roomNumber = QRandomGenerator::global()->bounded(1, 5);

    if (roomNumber == 1) buildRoom1(doorUp);
    else if (roomNumber == 2) buildRoom2(doorUp);
    else if (roomNumber == 3) buildRoom3(doorUp);
    else if (roomNumber == 4) buildRoom4(doorUp);

    m_openDoorTimer->setInterval(30);
    m_closeDoorTimer->setInterval(30);
    connect(m_openDoorTimer, &QTimer::timeout, this, [=]() { moveDoor(true); });
    connect(m_closeDoorTimer, &QTimer::timeout, this, [=]() { moveDoor(false); });

    m_gameCycleTimer->setInterval(1000);
    connect(m_gameCycleTimer, &QTimer::timeout, this, &Room::initCycle);
    m_botCycleTimer->setInterval(2000);
    connect(m_botCycleTimer, &QTimer::timeout, this, &Room::initBotCycle);

    for (int i = 0; i < 14; ++i)
        m_interactFloor[i]->setVisible(false);

    addAllItems();
    connect(m_door, &Door::destroyed, this, [=]() {
        m_door = nullptr;
        if (!m_deleted) delete this;
    });
}

Room::~Room() {
    m_deleted = true;
    m_closeDoorTimer->stop();
    delete m_closeDoorTimer;
    m_openDoorTimer->stop();
    delete m_openDoorTimer;
    m_gameCycleTimer->stop();
    delete m_gameCycleTimer;
    m_botCycleTimer->stop();
    delete m_botCycleTimer;
    delete m_sleepBtn;
    for (int i = 0; i < m_interactBtns.count(); ++i)
        delete m_interactBtns[i];
    for (int i = 0; i < m_interactFloor.count(); ++i)
        delete m_interactFloor[i];
    for (int i = 0; i < m_floor.count(); ++i)
        delete m_floor[i];
    for (int i = 0; i < m_walls.count(); ++i)
        delete m_walls[i];
    delete m_bed;
    delete m_door;
}

void Room::addFunction(Cage::BuildingType _type) {
    if (_type == Cage::HookahType)
        emit ghostM25();
    else if (_type == Cage::DotaType)
        emit ghostM25();
    else if (_type == Cage::HammerType)
        emit ghostAtt1();
    else if (_type == Cage::SixBybeType)
        ;
}

void Room::attackGhost(FloorCage* _cage) {
    emit attackGhostT(_cage->pos() + pos(), _cage->damagePerSec());
}

void Room::createSleepButton(QWidget* w) {
    m_sleepBtn = new QPushButton("СПАТЬ", w);
    connect(m_sleepBtn, &QPushButton::clicked, this, [=]() {
        emit sleepBtnClicked();
        m_sleepBtn->hide();
        setFree(false);
        createInteractBtns(w);
        showInteractingCages();
    });
    m_sleepBtn->setGeometry(m_bed->x()+this->x()-42, m_bed->y()+this->y()+57*2, 85, 25);
}

void Room::createInteractBtns(QWidget* w) {
    for (int i = 0; i < 14; ++i) {
        m_interactBtns.append(new QPushButton("+", w));
        m_interactBtns[i]->setStyleSheet("QPushButton { background: rgba(213, 213, 214, 0.2); font: 25px; border: 10px white; color: white; }"
                              "QPushButton:hover { background: rgba(213, 213, 214, 0.1); } QPushButton:pressed { background: rgba(190, 190, 191, 0.5); }");
        connect(m_interactBtns[i], &QPushButton::clicked, m_interactFloor[i], &FloorCage::clicked);
        m_interactBtns[i]->setGeometry(m_interactFloor[i]->x() + this->x() + 13, m_interactFloor[i]->y()+this->y() + 13, 30, 30);
    }
    for (int i = 0; i < 2; ++i) {
        m_interactBtns.append(new QPushButton("*", w));
        m_interactBtns[i+14]->setStyleSheet("QPushButton { background: rgba(221, 180, 226, 0.2); font: 25px; border: 10px white; color: white; }"
                                         "QPushButton:hover { background: rgba(221, 180, 226, 0.1); } QPushButton:pressed { background: rgba(167, 113, 173, 0.5); }");
    }
    connect(m_interactBtns[14], &QPushButton::clicked, m_bed, &Bed::clicked);
    connect(m_interactBtns[15], &QPushButton::clicked, m_door, &Door::clicked);
    m_interactBtns[14]->setGeometry(m_bed->x() + this->x() + 15, m_bed->y()+this->y() + 64, 30, 31);
    m_interactBtns[15]->setGeometry(m_door->x() + this->x() + 15, m_door->y()+this->y() + 23, 30, 31);
    for (int i = 0; i < 16; ++i) {
        m_interactBtns[i]->hide();
    }
}

void Room::showInteractingCages() {
    for (int i = 0; i < m_interactFloor.count(); ++i) {
        m_interactFloor[i]->setVisible(true);
        m_interactBtns[i]->show();
    }
    for (int i = 0; i < 2; ++i)
        m_interactBtns[14+i]->show();
}

void Room::setHuman(Human* human, bool bot) {
    m_human = human;
    m_human->setPos(x()+m_bed->x(), y()+m_bed->y());
    QGraphicsPixmapItem* h = new QGraphicsPixmapItem(m_human->getPixmap().scaled(50, 50));
    h->setPos(m_bed->pos() + this->pos() + QPointF(3.5, 3.5));
    addToGroup(h);
    m_human->setPos(-57, -57);
    m_human->setInRoom();
    if (bot) m_botCycleTimer->start();
    m_gameCycleTimer->start();
    setFree(false);
}

void Room::initCycle() {
    for (int i = 0; i < 14; ++i) {
        m_money += m_interactFloor[i]->moneyPerSec();
        m_energy += m_interactFloor[i]->energyPerSec();
    }
    m_money += m_bed->moneyPerSec();
    emit coinsChanged(m_money, m_energy);
}

void Room::initBotCycle() {
    int a = binarySearch(m_interactFloor, m_bed->y());
    for (int i = 0; i < 5; ++i) {
        if (m_bed->level() == i) m_bed->upgrade(); //26
        if (m_bed->level() == 1) {
            m_interactFloor[a]->setBuilding(Cage::ShellyType); // 8
            m_interactFloor[1]->setBuilding(Cage::ShellyType); // 8
            m_interactFloor[13]->setBuilding(Cage::ShellyType); // 8
            m_interactFloor[12]->setBuilding(Cage::ShellyType); // 8
        }
        if (m_door->level() == i) m_door->upgrade(); // 50
        if (m_bed->level() == i + 1) m_bed->upgrade(); //52
        if (m_interactFloor[0]->level() == i) m_interactFloor[0]->upgrade();
        if (m_interactFloor[1]->level() == i) m_interactFloor[1]->upgrade();
        if (m_door->level() == i + 1) m_door->upgrade(); // 100
        if (m_bed->level() == i + 2) m_bed->upgrade(); //104
        m_interactFloor[i + 2]->setBuilding(Cage::Ps4Type); // 200
        if (m_interactFloor[i + 2]->getType() == Cage::Ps4Type) {
            if (m_interactFloor[13]->level() == i) m_interactFloor[13]->upgrade();
            if (m_interactFloor[12]->level() == i) m_interactFloor[12]->upgrade();
            int n = QRandomGenerator::global()->bounded(4);
            m_interactFloor[11 - i]->setBuilding(Cage::BuildingType(n));
    }
    }
}

int Room::binarySearch(const QVector<FloorCage*> arr, const int y) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid]->y() == y) {
            return mid;
        } else if (arr[mid]->y() < y) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    if (right < 0) {
        return 0;
    } else if (left >= static_cast<int>(arr.size())) {
        return arr.size()-1;
    } else {
        return std::abs(arr[left]->y() - y) < std::abs(arr[right]->y() - y) ? left : right;
    }
}


void Room::setFree(bool status) {
    m_free = status;
    if (!status) startClosingDoor();
}

bool Room::isFree() {
    return m_free;
}

QPushButton* Room::sleepBtn() {
    return m_sleepBtn;
}

QVector<FloorCage*> Room::getInteractFloor() {
    return m_interactFloor;
}

Door* Room::door() {
    return m_door;
}

Bed* Room::bed() {
    return m_bed;
}

void Room::startOpeningDoor() {
    m_closeDoorTimer->stop();
    m_openDoorTimer->start();
}

void Room::startClosingDoor() {
    m_openDoorTimer->stop();
    m_closeDoorTimer->start();
}

void Room::moveDoor(bool open) {
    if (open)
        if(abs(m_beginDoorPos.x()-m_door->pos().x()) == 57)
            m_openDoorTimer->stop();
        else
            m_door->setPos(m_door->pos().x() - 3, m_door->pos().y());
    else
        if(abs(m_beginDoorPos.x()-m_door->pos().x()) == 0)
        m_closeDoorTimer->stop();
        else
        m_door->setPos(m_door->pos().x() + 3, m_door->pos().y());
}

void Room::setDoorCoordinates(bool doorUp, QPointF pos1, QPointF pos2) {
    if (doorUp)
    {
        m_floor[m_floor.count() - 1]->setPos(pos1);
        m_door->setPos(pos1);
    } else {
        m_floor[m_floor.count() - 1]->setPos(pos2);
        m_door->setPos(pos2);
    }
    m_beginDoorPos = m_door->pos();
}

void Room::addAllItems() {
    for (int i = 0; i < m_floor.count(); ++i)
        addToGroup(m_floor[i]);
    addToGroup(m_bed);
    addToGroup(m_door);
    for (int i = 0; i < m_wallCount; ++i)
        addToGroup(m_walls[i]);
    for (int i = 0; i < m_interactFloor.count(); ++i)
        addToGroup(m_interactFloor[i]);
}

void Room::addFloor(int maxI, int maxJ) {
    m_floor.append(new QGraphicsPixmapItem(QPixmap(":/images/resourses/images/floor-room-cage.jpg")));
    for (int i = 0; i < maxI; ++i)
        for (int j = 0; j < maxJ; ++j) {
            m_floor.append(new QGraphicsPixmapItem(QPixmap(":/images/resourses/images/floor-room-cage.jpg")));
            m_floor[i*maxJ + j]->setPos(57*(1+j),57*(1+i));
        }
}

void Room::buildRoom1(bool doorUp, int flag) {
    for (int i = 0; i < 6; ++i)
        m_interactFloor[i]->setPos(57*(1+i),57);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j)
            m_interactFloor[6+i*3+j]->setPos(57*(1+j),57*(2+i));
    for (int i = 0; i < 2; ++i)
        m_interactFloor[12+i]->setPos(57*(1+i),57*4);

    for (int i = 0; i < 21; ++i)
        m_floor.append(new QGraphicsPixmapItem(QPixmap(":/images/resourses/images/floor-room-cage.jpg")));
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 6; ++j)
            m_floor[i*6 + j]->setPos(57*(1+j),57*(1+i));
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 4; ++j)
            m_floor[12 + i*4 + j]->setPos(57*(1+j),57*(3+i));

    for (int i = 0; i < 24; ++i)
        m_walls.append(new Cage(QPixmap(":/images/resourses/images/room-wall.jpg")));

    for (int i = 0; i < 6; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(0, 57*i);
    flag = doorUp ? 0 : -1;
    for (int i = 0; i < 3 + flag; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*(i - flag + 1), 57*5);
    for (int i = 0; i < 3; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*(i+3), 57*4);
    for (int i = 0; i < 2; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*5, 57*(3-i));
    for (int i = 0; i < 2; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*(6+i), 57*2);
    for (int i = 0; i < 2; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*7, 57*(1-i));
    flag = doorUp ? -1 : 0;
    for (int i = 0; i < 6 + flag; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*(6-i), 0);

    m_bed->setPos(57*4, 57*2);
    setDoorCoordinates(doorUp, QPointF(57, 0), QPointF(57, 57*5));
}

void Room::buildRoom2(bool doorUp, int flag) {
    addFloor(3, 6);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 5; ++j)
            m_interactFloor[i*5+j]->setPos(57*(2+j), 57*(1+i));
    for (int i = 0; i < 4; ++i)
        m_interactFloor[10+i]->setPos(57*(3+i), 57*3);

    for (int i = 0; i < 22; ++i)
        m_walls.append(new Cage(QPixmap(":/images/resourses/images/room-wall.jpg")));

    for (int i = 0; i < 4; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(0, 57*i);
    for (int i = 0; i < 2; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*(i+1), 57*3);
    flag = doorUp ? 0 : -2;
    for (int i = 0; i < 6 + flag; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*(i+2), 57*4);
    flag = doorUp ? 0 : +1;
    for (int i = 0; i < 4 + flag; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*7, 57*(3 + flag - i));
    flag = doorUp ? -1 : 0;
    for (int i = 0; i < 6 + flag; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*(6 + flag - i), 0);

    m_bed->setPos(57, 57);
    setDoorCoordinates(doorUp, QPointF(57*6, 0), QPointF(57*6, 57*4));
}

void Room::buildRoom3(bool doorUp, int flag) {
    addFloor(3, 6);
    for (int i = 0; i < 4; ++i)
        m_interactFloor[i]->setPos(57*(2+i), 57);
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 5; ++j)
            m_interactFloor[4+i*5+j]->setPos(57*(1+j), 57*(2+i));

    for (int i = 0; i < 22; ++i)
        m_walls.append(new Cage(QPixmap(":/images/resourses/images/room-wall.jpg")));

    for (int i = 0; i < 4; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(0, 57*(i+1));
    flag = doorUp ? 0 : -1;
    for (int i = 0; i < 7 + flag; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*(i - flag + 1), 57*4);
    for (int i = 0; i < 3; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*7, 57*(3-i));
    for (int i = 0; i < 2; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*6, 57*(1-i));
    flag = doorUp ? -1 : 0;
    for (int i = 0; i < 5 + flag; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*(5 + flag - i), 0);
    m_walls[m_wallCount]->setPos(57, 57);
    ++m_wallCount;

    m_bed->setPos(57*6, 57*2);
    setDoorCoordinates(doorUp, QPointF(57*5, 0), QPointF(57, 57*4));
}

void Room::buildRoom4(bool doorUp, int flag) {
    addFloor(4, 4);
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 3; ++j)
            m_interactFloor[i*3+j]->setPos(57*(1+j), 57*(1+i));
    for (int i = 0; i < 2; ++i)
        m_interactFloor[12+i]->setPos(57*4, 57*(3+i));

    for (int i = 0; i < 20; ++i)
        m_walls.append(new Cage(QPixmap(":/images/resourses/images/room-wall.jpg")));

    for (int i = 0; i < 6; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(0, 57*i);
    flag = doorUp ? 0 : -1;
    for (int i = 0; i < 4 + flag; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*(i + 1), 57*5);
    for (int i = 0; i < 6; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*5, 57*(5-i));
    flag = doorUp ? -1 : 0;
    for (int i = 0; i < 4 + flag; ++i, ++m_wallCount)
        m_walls[m_wallCount]->setPos(57*(4 - i), 0);

    m_bed->setPos(57*4, 57);
    setDoorCoordinates(doorUp, QPointF(57, 0), QPointF(57*4, 57*5));
}
