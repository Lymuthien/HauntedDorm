#include "map.h"
#include "ui_map.h"

#include <QGraphicsProxyWidget>
#include <QRandomGenerator>
#include <QTimer>

Map::Map(QPixmap skin, QPixmap* skins, QWidget *parent)
    : QWidget(parent), ui(new Ui::Map), m_skins(skins), m_humanAndDoorTimer(new QTimer(this))
    , m_ghostAndDoorTimer(new QTimer(this)), m_scene(new QGraphicsScene)
{    
    ui->setupUi(this);
    ui->graphicsView->setScene(m_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    m_human = new Human(skin);

    buildWalls();
    buildRooms();
    initHumanBots();

    m_humanAndDoorTimer->setInterval(200);
    connect(m_humanAndDoorTimer, &QTimer::timeout, this, &Map::openDoorInRoom);
    m_humanAndDoorTimer->start();

    m_ghostAndDoorTimer->setInterval(1000);
    connect(m_ghostAndDoorTimer, &QTimer::timeout, this, &Map::hitDoorInRoom);

    m_human->setPos(57*15, 57*9);
    m_scene->addItem(m_human);

    ui->timeBeforeGhost->setTime(ui->timeBeforeGhost->time().addSecs(-1));

    connect(ui->settingsBtn, &QPushButton::clicked, this, &Map::settingsBtnClicked);
    connect(ui->settingsBtn, &QPushButton::clicked, this, &Map::btnClicked);

    ui->gameTime->hide();
    ui->doorHp->hide();
    ui->ghostHp->hide();
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

void Map::initHumanBots() {
    for(int i = 0; i < 3; ++i) {
        int skin = QRandomGenerator::global()->bounded(4);
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
                room->setHuman(m_human);
                ui->doorHp->setGeometry(room->door()->x() + room->x() + 3,
                                        room->door()->y() + room->y() - 16, 51, 14);
                ui->doorHp->setMaximum(room->door()->getMaxHp());
                ui->doorHp->show();
                connect(room, &Room::coinsChanged, this, &Map::setCoins);
                connect(room->door(), &Door::hpChanged, this, [=]() { ui->doorHp->setValue(room->door()->getHp());} );
                connect(room, &Room::destroyed, this, [=]() {emit gameOver(false); });
            });
            connect(room, &Room::destroyed, this, [=]() {removeRoom(room);});
        }
}

void Map::setCoins(int money, int energy) {
    ui->moneyCount->setText(QString::number(money));
    ui->energyCount->setText(QString::number(energy));
}

void Map::removeRoom(Room* room) {
    int i = m_rooms.indexOf(room);
    m_rooms[i] = nullptr;
    m_rooms.remove(i);
}

void Map::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
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

Map::~Map()
{
    for (int i = 0; i < m_rooms.count(); ++i)
        delete m_rooms[i];
    delete ui;
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
            m_rooms[i]->door()->setHp(m_rooms[i]->door()->getHp() - m_ghost->getDamage());
            emit doorHitted();
        }
    }
}

void Map::initGhost() {
    m_ghost = new Ghost(QPixmap(":/images/resourses/images/ghost.png"), &m_rooms, m_ghostHillZone, 50, 50);
    m_scene->addItem(m_ghost);
    m_ghost->setPos(57*11, 57*9);
    connect(m_ghost, &Ghost::moved, this, &Map::moveGhostHp);
    m_ghostAndDoorTimer->start();
}

void Map::moveGhostHp() {
    ui->ghostHp->setGeometry(m_ghost->x(), m_ghost->y() - 16, 51, 14);
    ui->ghostHp->show();
}

void Map::on_timeBeforeGhost_timeChanged(const QTime &time)
{
    if (!time.second()) {
        //if (!_human->isInRoom()) emit gameOver(false);
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
    t->start(1000);
}


void Map::on_gameTime_timeChanged(const QTime &time)
{
    QTimer* t = new QTimer();
    connect(t, &QTimer::timeout, this, [=]() { ui->gameTime->setTime(time.addSecs(1)); t->stop(); delete t;});
    t->start(1000);
}
