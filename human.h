#ifndef HUMAN_H
#define HUMAN_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class Human : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Human(const QPixmap pixmap, int width = 50, int height = 100, QObject *parent = nullptr);
    ~Human();

    bool processCollidings(QList<QGraphicsItem *> collidins);
    void moveToBed(QPointF doorPos, QPointF bedPos);
    bool isInRoom();
    void setInRoom();
    int speed();
    void setSpeed(int speed);
    QPixmap getPixmap();

    QRectF boundingRect() const;

signals:
    void nearTheBed();
    void nearTheDoor();

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

    bool m_inRoom = false;
    int m_speed = 12;
    int m_pixmapWidth, m_pixmapHeight;
    QPixmap m_pixmap;
    QPointF m_posBeforeCollision;
    QVector<QTimer*> m_movingTimers;
};

#endif // HUMAN_H
