#include "map.h"
#include "qdebug.h"
#include "ui_map.h"

#include <QGraphicsProxyWidget>
#include <QRandomGenerator>
#include <QTimer>

Map::Map(QWidget *parent)
    : QWidget(parent), ui(new Ui::Map), humanAndDoorTimer(new QTimer(this)), ghostAndDoorTimer(new QTimer(this))
    , _scene(new QGraphicsScene), _human (new Human(QPixmap(":/images/resourses/images/pngwing.com.png")))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->graphicsView->setDragMode(QGraphicsView::ScrollHandDrag);

    buildWalls();
    buildRooms();
    initHumanBots();

    humanAndDoorTimer->setInterval(200);
    connect(humanAndDoorTimer, &QTimer::timeout, this, &Map::openDoorInRoom);
    humanAndDoorTimer->start();

    ghostAndDoorTimer->setInterval(2000);
    connect(ghostAndDoorTimer, &QTimer::timeout, this, &Map::hitDoorInRoom);

    _human->setPos(57*15, 57*9);
    _scene->addItem(_human);

    ui->timeBeforeGhost->setTime(ui->timeBeforeGhost->time().addSecs(-1));

    connect(ui->settingsBtn, &QPushButton::clicked, this, &Map::settingsBtnClicked);
    connect(ui->settingsBtn, &QPushButton::clicked, this, &Map::btnClicked);

    ui->gameTime->hide();
    ui->doorHp->hide();
    ui->ghostHp->hide();
    //initGhost();
}

void Map::buildWalls() {
    for (int i = 0; i < (WALL_COUNT_WIDTH + WALL_COUNT_HEIGHT) * 2 ; ++i)
        _walls.append(new Cage(QPixmap(":/images/resourses/images/wall.jpg")));

    for (int i = 0; i < WALL_COUNT_WIDTH; ++i) {
        _walls[i*2]->setPos(57 * i, 0);
        _walls[i*2 + 1]->setPos(57 * i, 1080-57);
    }

    for (int i = 0, j = 0; i < WALL_COUNT_HEIGHT; ++i) {
        if (i == WALL_COUNT_HEIGHT / 2) {
            _ghostHillZone.append(QPoint(0, 57*i));
            _ghostHillZone.append(QPoint(1920-57, 57*i));
            continue;
        }
        _walls[WALL_COUNT_WIDTH * 2 + j * 2]->setPos(0, 57 * i);
        _walls[WALL_COUNT_WIDTH * 2 + j * 2 + 1]->setPos(1920-57, 57 * i);
        ++j;
    }

    for (int i = 0; i < (WALL_COUNT_WIDTH + WALL_COUNT_HEIGHT) * 2 ; ++i)
        _scene->addItem(_walls[i]);
}

void Map::initHumanBots() {
    for(int i = 0; i < 3; ++i) {
        _humanBots.append(new Human(QPixmap(":/images/resourses/images/pngwing.com.png")));
        _humanBots[i]->setPos(57*15, 57*9);
        _scene->addItem(_humanBots[i]);
        int roomNum = QRandomGenerator::global()->bounded(0, 2) + i * 2;
        connect(_humanBots[i], &Human::nearTheBed, this, [=]() { _rooms[roomNum]->setHuman(_humanBots[i]); });
        connect(_humanBots[i], &Human::nearTheDoor, this, [=]() { _rooms[roomNum]->startOpeningDoor(); });
        _humanBots[i]->moveToBed(_rooms[roomNum]->getDoor()->pos() + _rooms[roomNum]->pos(),
                                 _rooms[roomNum]->getBed()->pos() + _rooms[roomNum]->pos());
    }
}

void Map::buildRooms() {
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j) {
            _rooms.append(new Room(i, this));
            QPointF pos1(57 * (1 + QRandomGenerator::global()->bounded(0, 2)) + j * 11 * 57,
                         57 * (2 + 9 * i + QRandomGenerator::global()->bounded(0, 2)));
            _rooms[i * 3 + j]->setPos(pos1);
            _scene->addItem(_rooms[i * 3 + j]);
            _rooms[i*3+j]->createSleepButton(this);
            connect(_rooms[i*3+j], &Room::sleepBtnClicked, this, [=]() {
                _human->setPos(57*15, 57*9);
                _rooms[i*3+j]->setHuman(_human);
                ui->doorHp->setGeometry(_rooms[i*3+j]->getDoor()->x() + _rooms[i*3+j]->x() + 3,
                                        _rooms[i*3+j]->getDoor()->y() + _rooms[i*3+j]->y() - 16, 51, 14);
                ui->doorHp->setMaximum(_rooms[i*3+j]->getDoor()->getMaxHp());
                ui->doorHp->show();
                connect(_rooms[i*3+j]->getDoor(), &Door::hpChanged, this, [=]() { ui->doorHp->setValue(_rooms[i*3+j]->getDoor()->getHp());} );
                //тут будет смена спрайта кровати
            });
            Room* room = _rooms[i*3+j];
            connect(room, &Room::destroyed, this, [=]() {removeRoom(room);});
        }
}

void Map::removeRoom(Room* room) {
    int i = _rooms.indexOf(room);
    _rooms[i] = nullptr;
    _rooms.remove(i);
}

void Map::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();
    int speedPer200ms = _human->getSpeed() / 5;

    if (key == Qt::Key_W)
        if (_human->pos().y() < 0)
            return;
        else
            _human->moveBy(0, -speedPer200ms);
    else if (key == Qt::Key_S)
        if (_human->pos().y() > 1080)
            return;
        else
            _human->moveBy(0, speedPer200ms);
    else if (key == Qt::Key_A)
        _human->moveBy(-speedPer200ms, 0);
    else if (key == Qt::Key_D)
        _human->moveBy(speedPer200ms, 0);

    QWidget::keyPressEvent(event);
}

Map::~Map()
{
    for (int i = 0; i < _rooms.count(); ++i)
        delete _rooms[i];
    delete ui;
}

void Map::openDoorInRoom() {
    for (int i = 0; i < _rooms.count(); ++i) {
        if (_rooms[i]->getDoor()==nullptr) continue;
        if (_rooms[i]->isFree()) {
            if (abs(_human->y() - (_rooms[i]->getDoor()->y()+_rooms[i]->y())) <= 57*2
                && abs(_human->x() - (_rooms[i]->getDoor()->x()+_rooms[i]->x())) <= 57*2)
                _rooms[i]->startOpeningDoor();
            else
                _rooms[i]->startClosingDoor();
            if (abs(_human->y() - (_rooms[i]->getBed()->y()+_rooms[i]->y())) <= 57
                && abs(_human->x() - (_rooms[i]->getBed()->x()+_rooms[i]->x())) <= 57 + 5)
                    _rooms[i]->showSleepBtn(true);
            else
                _rooms[i]->showSleepBtn(false);
        }
    }
}

void Map::hitDoorInRoom() {
    for (int i = 0; i < _rooms.count(); ++i) {
        qDebug() << "roomN" << i << " pos: " << _rooms[i]->pos();
        if (abs(_ghost->y() - (_rooms[i]->getDoor()->y()+_rooms[i]->y())) <= 57
            && abs(_ghost->x() - (_rooms[i]->getDoor()->x()+_rooms[i]->x())) <= 57)
            _rooms[i]->getDoor()->setHp(_rooms[i]->getDoor()->getHp() - _ghost->getDamage()); }
}

void Map::initGhost() {
    _ghost = new Ghost(QPixmap(":/images/resourses/images/ghost.png"), &_rooms, _ghostHillZone, 50, 50);
    _scene->addItem(_ghost);
    _ghost->setPos(57*11, 57*9);
    connect(_ghost, &Ghost::moved, this, &Map::moveGhostHp);
    ghostAndDoorTimer->start();
}

void Map::moveGhostHp() {
    ui->ghostHp->setGeometry(_ghost->x(), _ghost->y() - 16, 51, 14);
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

