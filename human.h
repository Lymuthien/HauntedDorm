#ifndef HUMAN_H
#define HUMAN_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class Human : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Human(const QPixmap pixmap, int width = 50, int height = 50, QObject *parent = nullptr);

    bool processCollidings(QList<QGraphicsItem *> collidins);
    void moveToBed(QPointF doorPos, QPointF bedPos);
    bool isInRoom();
    void setInRoom();
    QPixmap getPixmap();

    int getSpeed();
    void setSpeed(int speed);

    QRectF boundingRect() const;

signals:
    void nearTheBed();
    void nearTheDoor();

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

    int _speed = 12;
    bool _inRoom = false;
    QPointF _posBeforeCollision;
    QPixmap _pixmap;
    int _pixmapWidth, _pixmapHeight;
    QVector<QTimer*> _movingTimers;
};

#endif // HUMAN_H
