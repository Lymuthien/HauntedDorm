#include "ghost.h"
#include "qtimer.h"


Ghost::Ghost(QPixmap pixmap, QVector<QPoint> hillPoints, int width, int height, QObject *parent)
    : Human{pixmap, width, height}, hillTimer(new QTimer()), _hillPoints(hillPoints)
{
    setSpeed(6);
    hillTimer->setInterval(1000);
    connect(hillTimer, &QTimer::timeout, this, &Ghost::goToHillZone);
    hillTimer->start();
}

Human *Ghost::findPeopleWithoutRoom(QVector<Human*> humans) {
    for (int i = 0; i < humans.count(); ++i)
        if (!humans[i]->isInRoom())
            return humans[i];
    return nullptr;
}

int Ghost::getHp() {
    return _hp;
}

void Ghost::setHp (int hp) {
    _hp = hp;
}

void Ghost::upgrade() {
    _maxHp *= 2;
    _hp = _maxHp;
    setSpeed(getSpeed() + 3);
}

int Ghost::getMaxHp() {
    return _maxHp;
}

void Ghost::goToHillZone() {
    if (_hp > _maxHp * 0.2) return;
    if ((y() == _hillPoints[0].y() || y() == _hillPoints[1].y()) &&
        (x() == _hillPoints[0].x() || x() == _hillPoints[2].x())) {
        _hp += _maxHp * 0.1;
        if (_hp > _maxHp)
            _hp = _maxHp;
    } else {
        int nearX = abs(_hillPoints[0].x() - x()) > abs(_hillPoints[2].x() - x()) ?
                        _hillPoints[2].x() : _hillPoints[0].x();
        int nearY = abs(_hillPoints[0].y() - y()) > abs(_hillPoints[1].y() - y()) ?
                        _hillPoints[1].y() : _hillPoints[0].y();
        hillTimer->stop();
        goToPoint(QPointF(nearX, nearY));
    }
}

void Ghost::goToPoint(QPointF point) {
    QTimer* toXTimer = new QTimer();
    QTimer* toYTimer = new QTimer();
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
            hillTimer->start();
        } else {
            setY(y() + 3 * flag);
            emit moved();
        }
    });
    toXTimer->start();
}
