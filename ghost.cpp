#include "ghost.h"
#include "qrandom.h"
#include "qtimer.h"


Ghost::Ghost(QPixmap pixmap, QVector<Room*>* rooms, QVector<QPoint> hillPoints, int width, int height, QObject *parent)
    : Human{pixmap, width, height}, hillTimer(new QTimer()), findRoomTimer(new QTimer()), _hillPoints(hillPoints), rooms(rooms)
{
    setSpeed(6);
    hillTimer->setInterval(1000);
    connect(hillTimer, &QTimer::timeout, this, &Ghost::goToHillZone);
    hillTimer->start();
}

int Ghost::getHp() {
    return _hp;
}

void Ghost::setHp (int hp) {
    _hp = hp;
}

int Ghost::getDamage() {
    return _damage;
}

void Ghost::upgrade() {
    _maxHp *= 2;
    _hp = _maxHp;
    _damage *= 2;
    setSpeed(getSpeed() + 3);
}

int Ghost::getMaxHp() {
    return _maxHp;
}

void Ghost::goToHillZone() {
    if (_hp > _maxHp * 0.2) {
        if (toXTimer == nullptr && toYTimer == nullptr) findRandomRoom(rooms);
        else if (toXTimer->isActive() || toYTimer->isActive()) return;
        else findRandomRoom(rooms);
        return;
    }

    if ((y() == _hillPoints[0].y()) && (x() == _hillPoints[0].x() || x() == _hillPoints[1].x())) {
        _hp += _maxHp * 0.1;
        if (_hp > _maxHp)
            _hp = _maxHp;
    } else {
        int nearX = abs(_hillPoints[0].x() - x()) > abs(_hillPoints[1].x() - x()) ?
                        _hillPoints[1].x() : _hillPoints[0].x();
        int nearY = _hillPoints[0].y();
        hillTimer->stop();
        goToPoint(QPointF(nearX, nearY));
    }
}

void Ghost::goToPoint(QPointF point) {
    if (x() == point.x() && y() == point.y()) return;
    toXTimer = new QTimer();
    toYTimer = new QTimer();
    toXTimer->setInterval(36 / ((getSpeed() / 3)));
    toYTimer->setInterval(36 / ((getSpeed() / 3)));

    int flag = 1;
    if (x()>point.x()) flag = -1;
    else flag = 1;
    connect(toXTimer, &QTimer::timeout, this, [=]() {
        if (x() == point.x()) {
            toXTimer->stop();
            toYTimer->start();
        } else {
            setX(x() + 3 * flag);
            emit moved();
        }
    });
    if (y()>point.y()) flag = -1;
    else flag = 1;
    connect(toYTimer, &QTimer::timeout, this, [=]() {
        if (y() == point.y()) {
            toYTimer->stop();
            goToPoint(QPointF(x(), 57*9));
            hillTimer->start();
        } else {
            setY(y() + 3 * flag);
            emit moved();
        }
    });
    toXTimer->start();
}

void Ghost::findRandomRoom(QVector<Room*>* room, int roomNum) {
    QVector<Room*>& rooms = *room;
    while ((roomNum = QRandomGenerator::global()->bounded(rooms.count())))
        if (rooms[roomNum] != nullptr)
            if (!rooms[roomNum]->isFree())
                if (rooms[roomNum]->getDoor() != nullptr) {
                    goToPoint(rooms[roomNum]->getDoor()->pos() + rooms[roomNum]->pos());
                    break;
                }
}
