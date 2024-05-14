#ifndef GHOST_H
#define GHOST_H

#include <QObject>
#include "human.h"

class Ghost : public Human
{
    Q_OBJECT
public:
    explicit Ghost(QPixmap pixmap, QObject *parent = nullptr);
};

#endif // GHOST_H
