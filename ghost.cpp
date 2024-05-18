#include "ghost.h"
#include "qrandom.h"
#include "qtimer.h"


Ghost::Ghost(QPixmap pixmap, QVector<Room*>* rooms, QVector<QPoint> hillPoints, int width, int height, QObject *parent)
    : Human{pixmap, width, height}, m_hillTimer(new QTimer()), m_hillPoints(hillPoints), m_rooms(rooms)
{
    setSpeed(6);
    m_hillTimer->setInterval(1000);
    connect(m_hillTimer, &QTimer::timeout, this, &Ghost::goToHillZone);
    m_hillTimer->start();
}

Ghost::~Ghost() {
    m_hillTimer->stop();
    delete m_hillTimer;
    if (m_toXTimer != nullptr) m_toXTimer->stop();
    delete m_toXTimer;
    if (m_toYTimer != nullptr) m_toYTimer->stop();
    delete m_toYTimer;
}

int Ghost::hp() {
    return m_hp;
}

void Ghost::setHp (int hp) {
    m_hp = hp;
    emit hpChanged();
}

int Ghost::damage() {
    return m_damage;
}

void Ghost::upgrade() {
    m_maxHp *= 2;
    setHp(m_maxHp);
    m_damage *= 2;
}

int Ghost::maxHp() {
    return m_maxHp;
}

void Ghost::goToHillZone() {
    if (m_hp > m_maxHp * 0.3) {
        if (m_toXTimer == nullptr && m_toYTimer == nullptr) findRandomRoom(m_rooms);
        else if (m_toXTimer->isActive() || m_toYTimer->isActive()) return;
        else findRandomRoom(m_rooms);
        return;
    }
    m_toXTimer->stop();
    m_toYTimer->stop();

    if ((y() == m_hillPoints[0].y()) && (x() == m_hillPoints[0].x() || x() == m_hillPoints[1].x())) {
        setHp(hp() + maxHp() * 0.05);
        if (m_hp > m_maxHp)
            m_hp = m_maxHp;
    } else {
        int nearX = abs(m_hillPoints[0].x() - x()) > abs(m_hillPoints[1].x() - x()) ?
                        m_hillPoints[1].x() : m_hillPoints[0].x();
        int nearY = m_hillPoints[0].y();
        m_hillTimer->stop();
        m_toXTimer->stop();
        m_toYTimer->stop();
        goToPoint(QPointF(nearX, nearY));
    }
}

void Ghost::setHitCount(int hitCount) {
    m_hitCount = hitCount;
    if (m_hitCount == 100) {
        m_hitCount = 0;
        upgrade();
    }
}

int Ghost::hitCount() {
    return m_hitCount;
}

void Ghost::goToPoint(QPointF point) {
    if (x() == point.x() && y() == point.y()) return;
    m_toXTimer = new QTimer();
    m_toYTimer = new QTimer();

    int flag = 1;
    if (x()>point.x()) flag = -1;
    else flag = 1;
    //if hilltimer !isactive
    connect(m_toXTimer, &QTimer::timeout, this, [=]() {
        if (x() == point.x()) {
            m_toXTimer->stop();
            m_toYTimer->start(36 / ((speed() / 3)));
        } else {
            setX(x() + 3 * flag);
            emit moved();
        }
    });
    if (y()>point.y()) flag = -1;
    else flag = 1;
    connect(m_toYTimer, &QTimer::timeout, this, [=]() {
        if (y() == point.y()) {
            m_toYTimer->stop();
            goToPoint(QPointF(x(), 57*9));
            m_hillTimer->start();
        } else {
            setY(y() + 3 * flag);
            emit moved();
        }
    });
    if (y() == point.y()) m_toXTimer->start(36 / ((speed() / 3)));
    else if (!m_hillTimer->isActive()) m_toYTimer->start(36 / ((speed() / 3)));
    else m_toXTimer->start(36 / ((speed() / 3)));
}

void Ghost::findRandomRoom(QVector<Room*>* room, int roomNum) {
    QVector<Room*>& rooms = *room;
    while ((roomNum = QRandomGenerator::global()->bounded(rooms.count())))
        if (rooms[roomNum] != nullptr)
            if (!rooms[roomNum]->isFree())
                if (rooms[roomNum]->door() != nullptr) {
                    goToPoint(rooms[roomNum]->door()->pos() + rooms[roomNum]->pos());
                    break;
                }
}
