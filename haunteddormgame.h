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
    void endGame(bool victory);
    void showSettings();
    void setGameOver(bool victory);
    void readCache();
    void saveCache();
    QString xorEncrypt(QString str);

    MainWindow* m_window;
    QMediaPlayer m_music;
    int m_coins = 0;

    QSoundEffect m_sound[3];
    bool m_settings[4] = {1, 1, 0};
    bool m_skinsCode[12] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0};

    Settings* m_settingsForm = nullptr;
    Menu* m_menu;
    Map* m_map = nullptr;
    GameOver* m_gameOver = nullptr;
    QPixmap m_skins[12] {QPixmap(":/skins/resourses/images/skins/skin-1.png"),
                        QPixmap(":/skins/resourses/images/skins/skin-2.png"),
                        QPixmap(":/skins/resourses/images/skins/skin-3.png"),
                        QPixmap(":/skins/resourses/images/skins/skin-4.png"),
                        QPixmap(":/skins/resourses/images/skins/skin-5.png"),
                        QPixmap(":/skins/resourses/images/skins/skin-6.png"),
                        QPixmap(":/skins/resourses/images/skins/skin-7.png"),
                        QPixmap(":/skins/resourses/images/skins/skin-8.png"),
                        QPixmap(":/skins/resourses/images/skins/german.png"),
                        QPixmap(":/skins/resourses/images/skins/katya.png"),
                        QPixmap(":/skins/resourses/images/skins/nikita.png"),
                        QPixmap(":/skins/resourses/images/skins/tanya.png")};
};

#endif // HAUNTEDDORMGAME_H
