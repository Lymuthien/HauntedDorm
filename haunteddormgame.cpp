#include "haunteddormgame.h"
#include "mainwindow.h"
#include "map.h"

#include <QOpenGLWindow>
#include <QOpenGLFunctions>
#include <QApplication>
#include <QScreen>
#include <QUrl>
#include <QCoreApplication>
#include <QFile>

#define KEY "fdkfg68d54v"
HauntedDormGame::HauntedDormGame(QObject *parent)
    : QObject{parent}, m_window(new MainWindow), m_menu(new Menu(m_skins, m_skinsCode, &m_coins))
{
    readCache();

    m_music.setMedia(QUrl::fromUserInput("qrc:/music/resourses/music/bg-music.mp3"));
    m_music.setVolume(20);
    QObject::connect(&m_music, &QMediaPlayer::stateChanged, [&](QMediaPlayer::State state){
        if (state == QMediaPlayer::StoppedState && m_settings[0] == 1) {
                             m_music.setPosition(0);
                             m_music.play();
                         }});

    m_sound[0].setSource(QUrl::fromUserInput("qrc:/sounds/resourses/music/button-in-menu-pressed.wav"));
    m_sound[1].setSource(QUrl::fromUserInput("qrc:/sounds/resourses/music/hitting-door-sound.wav"));
    m_sound[2].setSource(QUrl::fromUserInput("qrc:/sounds/resourses/music/quite-pressing.wav"));

    m_menu->setCoinsLabel(QString::number(m_coins));
    connect(m_menu, &Menu::destroyed, this, &HauntedDormGame::saveCache);
    connect(m_menu, &Menu::destroyed, m_window, &MainWindow::close);
    connect(m_menu, &Menu::settingsBtnClicked, this, &HauntedDormGame::showSettings);
    connect(m_menu, &Menu::startBtnClicked, this, &HauntedDormGame::startGame);
    connect(m_menu, &Menu::btnClicked, this, [=]() {playSound(0);});
}

void HauntedDormGame::readCache()
{
    QFile cache("cache.txt");
    if (!cache.open(QIODevice::ReadOnly | QIODevice::Text)) return;
    QTextStream in(&cache);

    QStringList settingsCache = in.readLine().split(" ");
    for (int i = 0; i < 3; ++i)
        m_settings[i] = xorEncrypt(settingsCache[i]).toInt();

    m_coins = xorEncrypt(in.readLine()).toInt();

    int skinNum = xorEncrypt(in.readLine()).toInt();
    m_menu->setSkin(m_skins[skinNum]);

    QStringList skinsCache = in.readLine().split(" ");
    for (int i = 0; i < 12; ++i)
        m_skinsCode[i] = xorEncrypt(skinsCache[i]).toInt();
    m_menu->updateBtnText();

    cache.close();
}

QString HauntedDormGame::xorEncrypt(QString str)
{
    QString result;
    QString key = "fdkfg68d54v";
    int keyLength = key.length();
    for (int i = 0; i < str.length(); ++i)
    {
        QChar char1 = str.at(i);
        QChar char2 = key.at(i % keyLength);
        QChar encryptedChar = QChar(char1.unicode() ^ char2.unicode());
        result += encryptedChar;
    }
    return result;
};

void HauntedDormGame::saveCache()
{
    QFile cache("cache.txt");
    cache.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&cache);
    for (int i = 0; i < 3; ++i)
        out << xorEncrypt(QString::number(m_settings[i])) << ' ';
    out << '\n' << xorEncrypt(QString::number(m_coins)) << '\n';
    for (int i = 0; i < 12; ++i)
        if (m_skins[i] == m_menu->getSkin()) {
            out << xorEncrypt(QString::number(i)) << '\n';
            break;
        }
    for (int i = 0; i < 12; ++i)
        out << xorEncrypt(QString::number(m_skinsCode[i])) << ' ';
    cache.close();
}

void HauntedDormGame::Start()
{
    m_music.play();
    
    m_window->setCentralWidget(m_menu);
    m_window->show();
}

void HauntedDormGame::startGame()
{
    if (m_map == nullptr) {
        m_map = new Map(m_menu->getSkin(), m_skins);
        connect(m_map, &Map::settingsBtnClicked, this, &HauntedDormGame::showSettings);
        connect(m_map, &Map::btnClicked, this, [=]() {playSound(0);});
        connect(m_map, &Map::gameOver, this, &HauntedDormGame::setGameOver);
        connect(m_map, &Map::doorHitted, this, [=]() {playSound(1);});
    }
    m_window->takeCentralWidget();
    m_window->setCentralWidget(m_map);
    m_map->setFocus();
}

void HauntedDormGame::endGame(bool victory)
{
    m_window->takeCentralWidget();
    m_window->setCentralWidget(m_menu);
    m_menu->setCoinsLabel(QString::number(m_coins));
    saveCache();
    m_menu->setFocus();
    delete m_map;
    m_map = nullptr;
    m_window->show();
}

void HauntedDormGame::setGameOver(bool victory) {
    if (m_gameOver == nullptr) {
        m_map->close();
        m_window->hide();
        m_gameOver = new GameOver(victory);
        connect(m_gameOver, &GameOver::goToMenu, this, &HauntedDormGame::endGame);
    }
    if (victory) m_coins += 500;
    m_gameOver->show();
}

void HauntedDormGame::playMusic(bool value)
{
    if (value)
        m_music.play();
    else
        m_music.pause();
}

void HauntedDormGame::playSound(int number)
{
    if (m_settings[1])
        m_sound[number].play();
}

void HauntedDormGame::showSettings()
{
    if (m_settingsForm == nullptr) {
        m_settingsForm = new Settings(m_settings);
        connect(m_menu, &Menu::destroyed, m_settingsForm, &QWidget::close);
        connect(m_settingsForm, &Settings::musicOn, this, [=]() {playMusic(1);});
        connect(m_settingsForm, &Settings::musicOff, this, [=]() {playMusic(0);});
        connect(m_settingsForm, &Settings::fullScreenSet, m_window, [this]() {m_window->setFullScreen(1); });
        connect(m_settingsForm, &Settings::normalScreenSet, m_window, [this]() {m_window->setFullScreen(0); });
    }
    m_settingsForm->hide();
    m_settingsForm->show();
}
