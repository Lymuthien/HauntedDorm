#include "ghost.h"
#include "qtimer.h"


Ghost::Ghost(QPixmap pixmap, QVector<Room*>* rooms, QVector<QPoint> hillPoints, int width, int height, QObject *parent)
    : Human{pixmap, width, height}
    , m_hillTimer(new QTimer())
    , m_hillPoints(hillPoints)
    , m_rooms(rooms)
{
    setSpeed(6);
    m_hillTimer->setInterval(1000);
    connect(m_hillTimer, &QTimer::timeout, this, &Ghost::goToHillZone);
    m_hillTimer->start();
}

Ghost::~Ghost()
{
    m_hillTimer->stop();
    delete m_hillTimer;
    if (m_toXTimer != nullptr)
        m_toXTimer->stop();
    delete m_toXTimer;
    if (m_toYTimer != nullptr)
        m_toYTimer->stop();
    delete m_toYTimer;
}

int Ghost::hp()
{
    return m_hp;
}

void Ghost::setHp (int hp)
{
    m_hp = hp;
    emit hpChanged();
}

int Ghost::damage()
{
    return m_damage;
}

void Ghost::upgrade()
{
    m_maxHp *= 2;
    setHp(m_maxHp);
    m_damage *= 2;
    setSpeed(speed() + 3);
}

int Ghost::maxHp()
{
    return m_maxHp;
}

void Ghost::goToHillZone()
{
    QVector<Edge> edges;
    edges.append(Edge(1,0,x()));
    edges.append(Edge(1,2, 1920-x()));

    if (m_hp > m_maxHp * 0.3)
    {
        if (m_toXTimer == nullptr && m_toYTimer == nullptr)
            findRandomRoom(m_rooms);
        else if (m_toXTimer->isActive() || m_toYTimer->isActive())
            return;
        else
            findRandomRoom(m_rooms);
        return;
    }
    m_toXTimer->stop();
    m_toYTimer->stop();

    if ((y() == m_hillPoints[0].y()) && (x() == m_hillPoints[0].x() || x() == m_hillPoints[1].x()))
    {
        setHp(hp() + maxHp() * 0.05);
        if (m_hp > m_maxHp)
            m_hp = m_maxHp;
    }
    else
    {
        QVector<int> d = bellmanFord(edges, 3, 1);

        int nearX = x() + d[0] > d[2] ? d[2] : - d[0];
        int nearY = m_hillPoints[0].y();

        m_hillTimer->stop();
        m_toXTimer->stop();
        m_toYTimer->stop();
        goToPoint(QPointF(nearX, nearY));
    }
}

QVector<int> Ghost::bellmanFord(QVector<Edge>&edges, int numVertices, int source)
{
    QVector<int> distances (numVertices, 1000000000);
    distances[source] = 0;

    for (int i = 0; i < numVertices - 1; i++)
        for (const auto& edge : edges)
            if (distances[edge.source] < 1000000000)
                distances[edge.destination] = std::min(distances[edge.destination], distances[edge.source] + edge.weight);

    return distances;
}

void Ghost::setHitCount(int hitCount)
{
    m_hitCount = hitCount;
    if (m_hitCount == 100)
    {
        m_hitCount = 0;
        upgrade();
    }
}

int Ghost::hitCount()
{
    return m_hitCount;
}

void Ghost::goToPoint(QPointF point)
{
    if (x() == point.x() && y() == point.y())
        return;
    m_toXTimer = new QTimer();
    m_toYTimer = new QTimer();

    int flag = 1;
    if (x()>point.x())
        flag = -1;
    else
        flag = 1;

    connect(m_toXTimer, &QTimer::timeout, this, [=]() {
        if (x() == point.x()) {
            m_toXTimer->stop();
            m_toYTimer->start(36 / ((speed() / 3)));
        } else {
            setX(x() + 3 * flag);
            emit moved();
        }
    });
    if (y()>point.y())
        flag = -1;
    else
        flag = 1;
    connect(m_toYTimer, &QTimer::timeout, this, [=]() {
        if (y() == point.y()) {
            m_toYTimer->stop();
            goToPoint(QPointF(x(), 57*9));
        } else {
            setY(y() + 3 * flag);
            emit moved();
        }
    });
    if (y() == point.y())
        m_toXTimer->start(36 / ((speed() / 3)));
    else if (!m_hillTimer->isActive())
        m_toYTimer->start(36 / ((speed() / 3)));
    else
        m_toXTimer->start(36 / ((speed() / 3)));
}

void Ghost::findRandomRoom(QVector<Room*>* room, int roomNum) {
    QVector<Room*>& rooms = *room;

    heapSort(rooms);
    for (int i = 0; i < rooms.count(); ++i)
        if (!rooms[i]->isFree())
        {
            goToPoint(rooms[i]->door()->pos() + rooms[i]->pos());
            return;
        }
}


void Ghost::heapify(QVector<Room*> roms, int n, int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;
    if (left < n && roms[left]->door()->hp() > roms[largest]->door()->hp())
        largest = left;

    if (right < n && roms[right]->door()->hp() > roms[largest]->door()->hp())
        largest = right;

    if (largest != i)
    {
        std::swap(roms[i], roms[largest]);
        heapify(roms, n, largest);
    }
}

void Ghost::heapSort(QVector<Room*> roms)
{
    int n = roms.size();
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(roms, n, i);

    for (int i=n-1; i>=0; i--)
    {
        std::swap(roms[0], roms[i]);
        heapify(roms, i, 0);
    }
}
