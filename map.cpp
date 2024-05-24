#include "map.h"
#include "ui_map.h"

#include <QGraphicsProxyWidget>
#include <QRandomGenerator>
#include <QTimer>
#include <bits/stdc++.h>

Map::Map(QPixmap skin, QPixmap* skins, QWidget *parent)
    : QWidget(parent), ui(new Ui::Map)
    , m_human(new Human(skin)), m_skins(skins)
    , m_humanAndDoorTimer(new QTimer(this))
    , m_ghostAndDoorTimer(new QTimer(this))
    , m_bulletToGhostTimer(new QTimer(this))
    , m_scene(new QGraphicsScene)
{    
    ui->setupUi(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    buildWalls();
    buildRooms();
    initHumanBots();

    m_humanAndDoorTimer->setInterval(200);
    connect(m_humanAndDoorTimer, &QTimer::timeout, this, &Map::openDoorInRoom);
    m_humanAndDoorTimer->start();

    m_ghostAndDoorTimer->setInterval(1000);
    connect(m_ghostAndDoorTimer, &QTimer::timeout, this, &Map::hitDoorInRoom);

    m_bulletToGhostTimer->setInterval(50);
    ui->timeBeforeGhost->setTime(ui->timeBeforeGhost->time().addSecs(-1));

    m_human->setPos(57*15, 57*9);
    m_scene->addItem(m_human);

    connect(ui->settingsBtn, &QPushButton::clicked, this, &Map::settingsBtnClicked);
    connect(ui->settingsBtn, &QPushButton::clicked, this, &Map::btnClicked);

    ui->gameTime->hide();
    ui->doorHp->hide();
    ui->ghostHp->hide();
}

Map::~Map() {
    for (int i = 0; i < m_rooms.count();)
        delete m_rooms[i];
    delete m_human;
    m_humanAndDoorTimer->stop();
    delete m_humanAndDoorTimer;
    m_ghostAndDoorTimer->stop();
    delete m_ghostAndDoorTimer;
    m_bulletToGhostTimer->stop();
    delete m_bulletToGhostTimer;
    for (int i = 0; i < m_walls.count(); ++i)
        delete m_walls[i];
    for (int i = 0; i < m_humanBots.count(); ++i)
        delete m_humanBots[i];
    delete m_scene;
    delete ui;
}

void Map::buildWalls() {
    for (int i = 0; i < (WALL_COUNT_WIDTH + WALL_COUNT_HEIGHT) * 2 ; ++i)
        m_walls.append(new Cage(QPixmap(":/images/resourses/images/wall.jpg")));

    for (int i = 0; i < WALL_COUNT_WIDTH; ++i) {
        m_walls[i*2]->setPos(57 * i, 0);
        m_walls[i*2 + 1]->setPos(57 * i, 1080-57);
    }

    for (int i = 0, j = 0; i < WALL_COUNT_HEIGHT; ++i) {
        if (i == WALL_COUNT_HEIGHT / 2) {
            m_ghostHillZone.append(QPoint(0, 57*i));
            m_ghostHillZone.append(QPoint(1920-57, 57*i));
            continue;
        }
        m_walls[WALL_COUNT_WIDTH * 2 + j * 2]->setPos(0, 57 * i);
        m_walls[WALL_COUNT_WIDTH * 2 + j * 2 + 1]->setPos(1920-57, 57 * i);
        ++j;
    }

    for (int i = 0; i < (WALL_COUNT_WIDTH + WALL_COUNT_HEIGHT) * 2 ; ++i)
        m_scene->addItem(m_walls[i]);
}

void Map::buildRooms() {
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j) {
            m_rooms.append(new Room(i, this));
            Room* room = m_rooms[i*3+j];
            QPointF pos1(57 * (1 + QRandomGenerator::global()->bounded(0, 2)) + j * 11 * 57,
                         57 * (2 + 9 * i + QRandomGenerator::global()->bounded(0, 2)));
            room->setPos(pos1);
            m_scene->addItem(room);
            room->createSleepButton(this);
            connect(room, &Room::sleepBtnClicked, this, [=]() {
                m_human->setPos(57*15, 57*9);
                room->setHuman(m_human, false);
                ui->doorHp->setGeometry(room->door()->x() + room->x() + 3,
                                        room->door()->y() + room->y() - 16, 51, 14);
                ui->doorHp->setMaximum(room->door()->maxHp());
                ui->doorHp->show();
                connect(room, &Room::coinsChanged, this, &Map::setCoins);
                connect(room->door(), &Door::hpChanged, this, [=]() { ui->doorHp->setValue(room->door()->hp());} );
                connect(room, &Room::destroyed, this, [=]() {this->close();emit gameOver(false); });
                connect(room, &Room::ghostM25, this, [=]() {m_ghost->setSpeed(m_ghost->speed()*0.5);});
                connect(room, &Room::ghostAtt1, this, [=]() { m_ghost->setHp(m_ghost->hp()*0.99); });
            });
            connect(room, &Room::destroyed, this, [=]() {removeRoom(room);});
            connect(room, &Room::attackGhostT, this, &Map::attackGhost);
        }
}

void Map::removeRoom(Room* room) {
    int i = m_rooms.indexOf(room);
    m_rooms[i] = nullptr;
    m_rooms.remove(i);
}

void Map::initHumanBots() {
    long* nums = randNumbers(3);
    for(int i = 0; i < 3; ++i) {
        int skin = nums[i] % 8;
        m_humanBots.append(new Human(m_skins[skin]));
        m_humanBots[i]->setPos(57*15, 57*9);
        m_scene->addItem(m_humanBots[i]);
        int roomNum = QRandomGenerator::global()->bounded(0, 2) + i * 2;
        connect(m_humanBots[i], &Human::nearTheBed, this, [=]() { m_rooms[roomNum]->setHuman(m_humanBots[i]); });
        connect(m_humanBots[i], &Human::nearTheDoor, this, [=]() { m_rooms[roomNum]->startOpeningDoor(); });
        m_humanBots[i]->moveToBed(m_rooms[roomNum]->door()->pos() + m_rooms[roomNum]->pos(),
                                  m_rooms[roomNum]->bed()->pos() + m_rooms[roomNum]->pos());
    }
}

void Map::attackGhost(QPointF pos, int dmg) {
    if (QLineF(pos, m_ghost->pos()).length() < 57*6) {
        m_ghost->setHp(m_ghost->hp() - dmg);
        QGraphicsEllipseItem* bullet = new QGraphicsEllipseItem(0, 0, 10, 10);
        bullet->setPen(QPen(QColor(Qt::red)));
        bullet->setPos(pos);
        m_scene->addItem(bullet);
        QTimer* bulletToGhostTimer = new QTimer();
        bulletToGhostTimer->setInterval(50);
        connect(bulletToGhostTimer, &QTimer::timeout, this, [this, bullet, bulletToGhostTimer]() mutable {bulletLine(bullet, m_ghost->pos(), bulletToGhostTimer);});
        bulletToGhostTimer->start();
    }
}

void Map::initGhost() {
    m_ghost = new Ghost(QPixmap(":/images/resourses/images/ghost.png"), &m_rooms, m_ghostHillZone, 50, 50);
    m_scene->addItem(m_ghost);
    m_ghost->setPos(57*11, 57*9);
    connect(m_ghost, &Ghost::moved, this, &Map::moveGhostHp);
    connect(m_ghost, &Ghost::hpChanged, this, &Map::moveGhostHp);
    connect(m_ghost, &Ghost::destroyed, this, [=]() {gameOver(true);});
    m_ghostAndDoorTimer->start();
}

void Map::bulletLine(QGraphicsEllipseItem*& _bullet, QPointF _ghostPos, QTimer* _timer) {
    if (QLineF(_bullet->pos(), _ghostPos).length() < 5 ) {
        _timer->stop();
        _timer->deleteLater();
        delete _bullet;
        _bullet = nullptr;
        return;
    }
    _bullet->setPos((_bullet->pos() + _ghostPos) / 2);
}

void Map::setCoins(int money, int energy) {
    ui->moneyCount->setText(QString::number(money));
    ui->energyCount->setText(QString::number(energy));
}

void Map::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();

    if (key == Qt::Key_Up || key == Qt::Key_Down || key == Qt::Key_Left || key == Qt::Key_Right)
        return;

    int speedPer200ms = m_human->speed() / 5;

    if (key == Qt::Key_W)
        if (m_human->pos().y() < 0)
            return;
        else
            m_human->moveBy(0, -speedPer200ms);
    else if (key == Qt::Key_S)
        if (m_human->pos().y() > 1080)
            return;
        else
            m_human->moveBy(0, speedPer200ms);
    else if (key == Qt::Key_A)
        m_human->moveBy(-speedPer200ms, 0);
    else if (key == Qt::Key_D)
        m_human->moveBy(speedPer200ms, 0);

    QWidget::keyPressEvent(event);
}

void Map::openDoorInRoom() {
    for (int i = 0; i < m_rooms.count(); ++i) {
        if (m_rooms[i]->door()==nullptr) continue;
        if (m_rooms[i]->isFree()) {
            if (abs(m_human->y() - (m_rooms[i]->door()->y()+m_rooms[i]->y())) <= 57*2
                && abs(m_human->x() - (m_rooms[i]->door()->x()+m_rooms[i]->x())) <= 57*2)
                m_rooms[i]->startOpeningDoor();
            else
                m_rooms[i]->startClosingDoor();
            if (abs(m_human->y() - (m_rooms[i]->bed()->y()+m_rooms[i]->y())) <= 57
                && abs(m_human->x() - (m_rooms[i]->bed()->x()+m_rooms[i]->x())) <= 57 + 5)
                m_rooms[i]->sleepBtn()->show();
            else
                m_rooms[i]->sleepBtn()->hide();;
        }
    }
}

void Map::hitDoorInRoom() {
    for (int i = 0; i < m_rooms.count(); ++i) {
        if (abs(m_ghost->y() - (m_rooms[i]->door()->y()+m_rooms[i]->y())) <= 57
            && abs(m_ghost->x() - (m_rooms[i]->door()->x()+m_rooms[i]->x())) <= 57) {
            m_rooms[i]->door()->setHp(m_rooms[i]->door()->hp() - m_ghost->damage());
            m_ghost->setHitCount(m_ghost->hitCount() + 1);
            emit doorHitted();
        }
    }
}

void Map::moveGhostHp() {
    ui->ghostHp->setValue(m_ghost->hp());
    ui->ghostHp->setMaximum(m_ghost->maxHp());
    ui->ghostHp->setGeometry(m_ghost->x(), m_ghost->y() - 16, 51, 14);
    ui->ghostHp->show();
}

long* Map::randNumbers(int n) {
    int x0 = std::time(nullptr);
    long m = 4294967296;
    int a = 214013;
    int c = 2531011;
    long* nums = new long[n];
    nums[0] = x0;
    for (int i = 1; i < n; ++i) {
        nums[i] = (nums[i-1] * a + c);
        nums[i] %= m;
    }

    return nums;
}

void Map::on_timeBeforeGhost_timeChanged(const QTime &time)
{
    if (!time.second()) {
        if (!m_human->isInRoom()) {
            emit gameOver(false);
            return;
        }
        initGhost();
        ui->gameTime->show();
        ui->timeBeforeGhost->hide();
        ui->gameTime->setTime(ui->gameTime->time().addSecs(1));
        return;
    }
    if (time.second() == 10) {
        ui->timeBeforeGhost->setStyleSheet("font: 35px; color: rgb(234, 215, 217);");
    }
    QTimer* t = new QTimer();
    connect(t, &QTimer::timeout, this, [=]() { ui->timeBeforeGhost->setTime(time.addSecs(-1)); t->stop(); delete t;});
    t->start(1000); }

void Map::on_gameTime_timeChanged(const QTime &time)
{
    if (m_ghost->hp() <= 0) emit gameOver(true);
    QTimer* t = new QTimer();
    connect(t, &QTimer::timeout, this, [=]() { ui->gameTime->setTime(time.addSecs(1)); t->stop(); delete t;});
    t->start(1000);
}

void Map::on_pushButton_clicked()
{
    emit gameOver(false);
}
