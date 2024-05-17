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
    void playMusic(bool value);
    void playSound(int number);
    void startGame();
    void endGame();
    void showSettings();
    void setGameOver(bool victory);
    void readCache();

    MainWindow* m_window;
    QMediaPlayer m_music;
    int m_coins = 0;

    QSoundEffect m_sound[3];
    bool m_settings[4] = {1, 1, 0};

    Settings* m_settingsForm = nullptr;
    Menu* m_menu;
    Map* m_map = nullptr;
    GameOver* m_gameOver = nullptr;
    QPixmap m_skins[4] {QPixmap(":/skins/resourses/images/skins/german.png"),
                        QPixmap(":/skins/resourses/images/skins/katya.png"),
                        QPixmap(":/skins/resourses/images/skins/tanya.png"),
                        QPixmap(":/skins/resourses/images/skins/nikita.png")};
};

#endif // HAUNTEDDORMGAME_H
