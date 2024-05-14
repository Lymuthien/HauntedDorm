#ifndef HAUNTEDDORMGAME_H
#define HAUNTEDDORMGAME_H

#include <QMap>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QOpenGLWidget>
#include <QObject>

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

    enum State {
        Uninitialized,
        SplashScreen,
        MenuState,
        Playing,
        Exiting
    };

private:
    void gameLoop();
    void setState (State s);
    State getState();
    void playMusic(bool value);
    void playSound(int number);

    void startGame();
    void showSettings();

    bool* getSettings();
    void setSettings(int number, bool value);

    MainWindow* _window;
    State _state = Uninitialized;
    QMap<State, int> _stateInstances;
    QMediaPlayer _music;
    int _coins = 0;

    QSoundEffect _sound[3];
    bool _settings[4] = {1, 1, 1, 0};

    Settings* SettingsForm;
    Menu* menu;
    Map* map = nullptr;

signals:
};

#endif // HAUNTEDDORMGAME_H