#include "map.h"
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

    humanAndDoorTimer->setInterval(200);
    connect(humanAndDoorTimer, &QTimer::timeout, this, &Map::openDoorInRoom);
    humanAndDoorTimer->start();

    _human->setPos(57*15, 57*9-20);
    _scene->addItem(_human);

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

void Map::buildRooms() {
    for (int i = 0; i < 2; ++i)
        for (int j = 0; j < 3; ++j) {
            _rooms.append(new Room(i));
            _rooms[i * 3 + j]->setPos(57 * (1 + QRandomGenerator::global()->bounded(0, 2)) + j * 11 * 57,
                              57 * (2 + 9 * i + QRandomGenerator::global()->bounded(0, 2)));
            _scene->addItem(_rooms[i * 3 + j]);
            _rooms[i*3+j]->createSleepButton(this);
        }
}

void Map::keyPressEvent(QKeyEvent* event)
{
    int key = event->key();

    if (key == Qt::Key_W)
        if (_human->pos().y() < 0)
            return;
        else
            _human->moveBy(0, -3);
    else if (key == Qt::Key_S)
        if (_human->pos().y() > 1080)
            return;
        else
            _human->moveBy(0, 3);
    else if (key == Qt::Key_A)
        _human->moveBy(-3, 0);
    else if (key == Qt::Key_D)
        _human->moveBy(3, 0);

    QWidget::keyPressEvent(event);
}


Map::~Map()
{
    delete ui;
}

void Map::openDoorInRoom() {
    for (int i = 0; i < 6; ++i) {
        if (abs(_human->y() - (_rooms[i]->getDoor()->y()+_rooms[i]->y())) <= 57*2
            && abs(_human->x() - (_rooms[i]->getDoor()->x()+_rooms[i]->x())) <= 57*2)
            _rooms[i]->startOpeningDoor();
        else
            _rooms[i]->startClosingDoor();

        if (abs(_human->y() - (_rooms[i]->getBed()->y()+_rooms[i]->y())) <= 57
            && abs(_human->x() - (_rooms[i]->getBed()->x()+_rooms[i]->x())) <= 57 + 5)
            if (_rooms[i]->isFree())
                _rooms[i]->showSleepBtn(true);
            else
                _rooms[i]->showSleepBtn(false);
        else
            _rooms[i]->showSleepBtn(false);




    }
}



