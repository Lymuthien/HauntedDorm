#include "human.h"
#include "cage.h"
#include "qgraphicsscene.h"

#include <QPainter>
#include <QTimer>

Human::Human(const QPixmap pixmap, int width, int height, QObject *parent)
    : QObject{parent}, QGraphicsItem(), _pixmap(pixmap), _pixmapWidth(width), _pixmapHeight(height)
{}

void Human::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QPointF currentPos = pos();
    QList<QGraphicsItem *> colliding = scene()->collidingItems(this);

    if (processCollidings(colliding) == false)
        setPos(_posBeforeCollision);
    else
        _posBeforeCollision = currentPos;

    painter->drawPixmap(QRect(0, 0, _pixmapWidth, _pixmapHeight), _pixmap);
}

QPixmap Human::getPixmap() {
    return _pixmap;
}

QRectF Human::boundingRect() const
{
    return QRectF(0, 0, _pixmapWidth, _pixmapHeight);
}

void Human::moveToBed(QPointF doorPos, QPointF bedPos) {
    for (int i = 0; i < 3; ++i) {
        _movingTimers.append(new QTimer());
        _movingTimers[i]->setInterval(35);
    }

    int flag = 1;

    if (x()>doorPos.x()) flag = -1;
    else flag = 1;
    connect(_movingTimers[0], &QTimer::timeout, this, [=]() {
        if (x() - doorPos.x() < 6 && x() > doorPos.x()) {
            _movingTimers[0]->stop();
            _movingTimers[1]->start();
        }
        setX(x() + 3 * flag);
    });
    if (y()>bedPos.y()) flag = -1;
    else flag = 1;
    connect(_movingTimers[1], &QTimer::timeout, this, [=]() {
        if (abs(y() - doorPos.y()) <= 57*2) emit nearTheDoor();
        if (y() == bedPos.y() || (doorPos.x() == bedPos.x() && abs(y() - bedPos.y()) <= 57*2 + 2)) {
            _movingTimers[1]->stop();
            _movingTimers[2]->start();
        }
        setY(y() + 3 * flag);
    });
    if (doorPos.x()>bedPos.x()) flag = -1;
    else flag = 1;
    connect(_movingTimers[2], &QTimer::timeout, this, [=]() {
        if (abs(x() - bedPos.x()) <= 60) {
            _movingTimers[2]->stop();
            emit nearTheBed();
        }
        setX(x() + 3 * flag);
    });
    _movingTimers[0]->start();
}

int Human::getSpeed() {
    return _speed;
}

void Human::setInRoom() {
    _inRoom = true;
}

bool Human::isInRoom() {
    return _inRoom;
}

void Human::setSpeed(int speed) {
    _speed = speed;
}


bool Human::processCollidings(QList<QGraphicsItem *> collidins) {
    bool can_move = true;
    for (QGraphicsItem* item : collidins) {
        if (dynamic_cast<Cage*> (item))
            can_move = false;
    }
    return can_move;
}

