#ifndef CAGE_H
#define CAGE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPixmap>

class Cage : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Cage(const QPixmap pixmap, QObject *parent = nullptr);
    QRectF boundingRect() const;
    virtual void upgrade();

protected:
    QPixmap _pixmap;

private:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*);
};

#endif // CAGE_H
