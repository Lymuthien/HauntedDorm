#ifndef HUMAN_H
#define HUMAN_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class Human : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Human(const QPixmap pixmap, QObject *parent = nullptr);

    bool processCollidings(QList<QGraphicsItem *> collidins);
    void moveToBed(QPointF doorPos, QPointF bedPos);

    int getSpeed();

    QRectF boundingRect() const;

signals:
    void nearTheBed();
    void nearTheDoor();

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);

    int _money = 0;
    int _energy = 0;
    int _speed = 12;
    QPointF _posBeforeCollision;
    QPixmap _pixmap;
    QVector<QTimer*> _movingTimers;

};

#endif // HUMAN_H
