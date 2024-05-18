#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QWidget>

namespace Ui {
class GameOver;
}

class GameOver : public QWidget
{
    Q_OBJECT

public:
    explicit GameOver(bool victory, QWidget *parent = nullptr);
    ~GameOver();

signals:
    void goToMenu(bool victory);

private:
    Ui::GameOver *ui;
};

#endif // GAMEOVER_H
