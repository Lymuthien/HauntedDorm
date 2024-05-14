#include "map.h"
#include "ghost.h"
#include "ui_map.h"
#include "cage.h"
#include "human.h"

#include <QGraphicsProxyWidget>
#include <QRandomGenerator>
#include <QTimer>

Map::Map(QWidget *parent)
    : QWidget(parent), ui(new Ui::Map), humanAndDoorTimer(new QTimer(this)), _scene(new QGraphicsScene)
    , _human (new Human(QPixmap(":/images/resourses/images/pngwing.com.png")))
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

    _human->setPos(57*15, 57*9);
    _scene->addItem(_human);

    ui->timeBeforeGhost->setTime(ui->timeBeforeGhost->time().addSecs(-1));

    connect(ui->settingsBtn, &QPushButton::clicked, this, &Map::settingsBtnClicked);
    connect(ui->settingsBtn, &QPushButton::clicked, this, &Map::btnClicked);
}

void Map::buildWalls() {
    for (int i = 0; i < (WALL_COUNT_WIDTH + WALL_COUNT_HEIGHT) * 2 ; ++i)
        _walls.append(new Cage(QPixmap(":/images/resourses/images/wall.jpg")));

    for (int i = 0, j = 0; i < WALL_COUNT_WIDTH; ++i) {
        if (i == WALL_COUNT_WIDTH / 3 || i == WALL_COUNT_WIDTH * 2 / 3)
            continue;
        _walls[j*2]->setPos(57 * i, 0);
        _walls[j*2 + 1]->setPos(57 * i, 1080-57);
        ++j;
    }

    for (int i = 0; i < WALL_COUNT_HEIGHT; ++i) {
        _walls[WALL_COUNT_WIDTH * 2 + i * 2]->setPos(0, 57 * i);
        _walls[WALL_COUNT_WIDTH * 2 + i * 2 + 1]->setPos(1920-57, 57 * i);
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
                //тут будет смена спрайта кровати
            });
            _rooms[i*3+j]->createInteractBtns(this);
        }
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
    for (int i = 0; i < 6; ++i)
        delete _rooms[i];
    delete ui;
}

void Map::openDoorInRoom() {
    for (int i = 0; i < 6; ++i) {
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

void Map::initGhost() {
    Ghost* g = new Ghost(QPixmap(":/images/resourses/images/pngwing.com.png"));
    _scene->addItem(g);
    g->setPos(57*9, 57*15);
}

void Map::on_timeBeforeGhost_timeChanged(const QTime &time)
{
    if (!time.second()) {
        initGhost();
        return;
    }
    QTimer* t = new QTimer();
    connect(t, &QTimer::timeout, this, [=]() { ui->timeBeforeGhost->setTime(time.addSecs(-1)); t->stop(); delete t;});
    t->start(1000);
}

