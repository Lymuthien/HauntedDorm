#include "haunteddormgame.h"
#include "mainwindow.h"
#include "map.h"

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QApplication>
#include <QScreen>
#include <QUrl>
#include <QCoreApplication>

HauntedDormGame::HauntedDormGame(QObject *parent)
    : QObject{parent}, _window(new MainWindow), SettingsForm(new Settings(_settings)), menu(new Menu)
{
    _music.setMedia(QUrl::fromUserInput("qrc:/music/resourses/music/bg-music.mp3"));
    _music.setVolume(20);
    QObject::connect(&_music, &QMediaPlayer::stateChanged, [&](QMediaPlayer::State state)
                     {
                         if (state == QMediaPlayer::StoppedState && _settings[0] == 1)
                         {
                             _music.setPosition(0);
                             _music.play();
                         }
                     });

    connect(SettingsForm, &Settings::musicOn, this, [=]() {playMusic(1);});
    connect(SettingsForm, &Settings::musicOff, this, [=]() {playMusic(0);});
    connect(SettingsForm, &Settings::fullScreenSet, _window, [this]() {_window->setFullScreen(1); });
    connect(SettingsForm, &Settings::normalScreenSet, _window, [this]() {_window->setFullScreen(0); });

    _sound[0].setSource(QUrl::fromUserInput("qrc:/sounds/resourses/music/button-in-menu-pressed.wav"));
    _sound[1].setSource(QUrl::fromUserInput("qrc:/sounds/resourses/music/hitting-door-sound.wav"));
    _sound[2].setSource(QUrl::fromUserInput("qrc:/sounds/resourses/music/quite-pressing.wav"));

    menu->SetCoinsLbl(QString::number(_coins));
    connect(menu, &Menu::settingsBtnClicked, this, &HauntedDormGame::showSettings);
    connect(menu, &Menu::startBtnClicked, this, &HauntedDormGame::startGame);
    connect(menu, &Menu::btnClicked, this, [=]() {playSound(0);});

    connect(map, &Map::settingsBtnClicked, this, &HauntedDormGame::showSettings);
    connect(map, &Map::btnClicked, this, [=]() {playSound(0);});
}

void HauntedDormGame::Start()
{
    if (_state != Uninitialized) return;

    _stateInstances[Playing];
    _stateInstances[SplashScreen];
    _stateInstances[MenuState];

    _state = MenuState;
    _music.play();

    //gameLoop();

    _window->setCentralWidget(menu);
    _window->show();
}


void HauntedDormGame::gameLoop()
{
    while (_state != Exiting)
    {

    }

}

void HauntedDormGame::startGame()
{
    _state = Playing;
    if (map == nullptr)
        map = new Map();
    _window->setCentralWidget(map);
}

void HauntedDormGame::setState(State s)
{
    _state = s;
}

HauntedDormGame::State HauntedDormGame::getState()
{
    return _state;
}

void HauntedDormGame::playMusic(bool value)
{
    if (value)
        _music.play();
    else
        _music.pause();
}

void HauntedDormGame::playSound(int number)
{
    if (_settings[1])
        _sound[number].play();
}

bool* HauntedDormGame::getSettings()
{
    return _settings;
}

void HauntedDormGame::setSettings(int number, bool value)
{
    _settings[number] = value;
}

void HauntedDormGame::showSettings()
{
    SettingsForm->hide();
    SettingsForm->show();
}




