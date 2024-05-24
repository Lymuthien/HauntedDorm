#include "human.h"
#include "cage.h"
#include "qgraphicsscene.h"

#include <QPainter>
#include <QTimer>

Human::Human(const QPixmap pixmap, int width, int height, QObject *parent)
    : QObject{parent}, QGraphicsItem(), m_pixmapWidth(width), m_pixmapHeight(height), m_pixmap(pixmap)
{}

Human::~Human() {
    for (int i = 0; i < m_movingTimers.count(); ++i) {
        m_movingTimers[i]->stop();
        m_movingTimers[i]->deleteLater();
    }
}

void Human::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
    QPointF currentPos = pos();
    QList<QGraphicsItem *> colliding = scene()->collidingItems(this);

    if (processCollidings(colliding) == false)
        setPos(m_posBeforeCollision);
    else
        m_posBeforeCollision = currentPos;
    
    painter->drawPixmap(QRect(0, 0, m_pixmapWidth, m_pixmapHeight), m_pixmap);
}

QPixmap Human::getPixmap() {
    return m_pixmap;
}

QRectF Human::boundingRect() const
{
    return QRectF(0, 0, m_pixmapWidth, m_pixmapHeight);
}

void Human::moveToBed(QPointF doorPos, QPointF bedPos) {
    for (int i = 0; i < 3; ++i) {
        m_movingTimers.append(new QTimer());
        m_movingTimers[i]->setInterval(35);
    }

    int flag = 1;

    flag = x()>doorPos.x() ? -1 : 1;
    connect(m_movingTimers[0], &QTimer::timeout, this, [=]() {
        if (x() - doorPos.x() < 6 && x() > doorPos.x()) {
            m_movingTimers[0]->stop();
            m_movingTimers[1]->start();
        }
        setX(x() + 3 * flag);
    });
    flag = y()>bedPos.y() ? -1 : 1;
    connect(m_movingTimers[1], &QTimer::timeout, this, [=]() {
        if (abs(y() - doorPos.y()) <= 57*2) emit nearTheDoor();
        if (y() == bedPos.y() || (doorPos.x() == bedPos.x() && abs(y() - bedPos.y()) <= 57*2 + 2)) {
            m_movingTimers[1]->stop();
            m_movingTimers[2]->start();
        }
        setY(y() + 3 * flag);
    });
    flag = doorPos.x()>bedPos.x() ? -1 : 1;
    connect(m_movingTimers[2], &QTimer::timeout, this, [=]() {
        if (abs(x() - bedPos.x()) <= 60) {
            m_movingTimers[2]->stop();
            emit nearTheBed();
        }
        setX(x() + 3 * flag);
    });
    m_movingTimers[0]->start();
}

int Human::speed() {
    return m_speed;
}

void Human::setInRoom() {
    m_inRoom = true;
}

bool Human::isInRoom() {
    return m_inRoom;
}

void Human::setSpeed(int speed) {
    m_speed = speed;
}

bool Human::processCollidings(QList<QGraphicsItem *> collidins) {
    bool can_move = true;
    for (QGraphicsItem* item : collidins) {
        if (dynamic_cast<Cage*> (item))
            can_move = false;
    }
    return can_move;
}

