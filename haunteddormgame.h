#ifndef HAUNTEDDORMGAME_H
#define HAUNTEDDORMGAME_H

#include <QMap>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QOpenGLWidget>
#include <QObject>

#include "gameover.h"
#include "mainwindow.h"
#include "settings.h"
#include "menu.h"
#include "map.h"

class HauntedDormGame : public QObject
{
    Q_OBJECT
public:
    explicit HauntedDormGame(QObject *parent = nullptr);
    void Start();

private:
    void gameLoop();
    void playMusic(bool value);
    void playSound(int number);

    void startGame();
    void endGame();
    void showSettings();
    void setGameOver(bool victory);

    bool* getSettings();
    void setSettings(int number, bool value);

    void readCache();

    MainWindow* _window;
    QMediaPlayer _music;
    int _coins = 0;

    QSoundEffect _sound[3];
    bool _settings[4] = {1, 1, 0};

    Settings* SettingsForm = nullptr;
    Menu* menu;
    Map* map = nullptr;
    GameOver* gameOver = nullptr;
    QPixmap skins[4] {QPixmap(":/skins/resourses/images/skins/german.png"),
                           QPixmap(":/skins/resourses/images/skins/katya.png"),
                           QPixmap(":/skins/resourses/images/skins/tanya.png"),
                           QPixmap(":/skins/resourses/images/skins/nikita.png")};

signals:
};

#endif // HAUNTEDDORMGAME_H
