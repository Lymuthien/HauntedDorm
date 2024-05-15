#include "settings.h"
#include "ui_settings.h"

#include <QFile>
#include <QIcon>

#define WINDOW_WIDTH 512
#define WINDOW_HEIGHT 512

Settings::Settings(bool* settings, QWidget *parent)
    : QWidget(parent), ui(new Ui::Settings), _settings(settings)
{
    ui->setupUi(this);
    setFixedSize(this->size());
    setIcons();
    setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMinimizeButtonHint & ~Qt::WindowMaximizeButtonHint);
}

Settings::~Settings()
{
    delete ui;
}

void Settings::setIcons()
{
    if (_settings[0])
        ui->musicModeButton->setIcon(QIcon::fromTheme("audio-volume-high"));
    else
        ui->musicModeButton->setIcon(QIcon::fromTheme("audio-volume-muted"));

    if (_settings[1])
        ui->soundModeButton->setIcon(QIcon::fromTheme("audio-volume-high"));
    else
        ui->soundModeButton->setIcon(QIcon::fromTheme("audio-volume-muted"));

    if (_settings[2])
        ui->screenModeButton->setChecked(true);
    else
        ui->screenModeButton->setChecked(false);
}

void Settings::on_musicModeButton_clicked()
{
    if (_settings[0]) {
        _settings[0] = 0;
        emit musicOff();
    } else {
        _settings[0] = 1;
        emit musicOn();
    }
    setIcons();
}


void Settings::on_soundModeButton_clicked()
{
    if (_settings[1]) {
        _settings[1] = 0;
        emit soundOff();
    } else
    {
        _settings[1] = 1;
        emit soundOn();
    }
    setIcons();
}

void Settings::on_screenModeButton_stateChanged(int arg1)
{
    if (_settings[2]) {
        _settings[2] = 0;
        emit normalScreenSet();
    } else {
        _settings[2] = 1;
        emit fullScreenSet();
    }
}

