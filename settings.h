#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(bool* settings, QWidget *parent = nullptr);
    ~Settings();

signals:
    void musicOn();
    void musicOff();
    void soundOn();
    void soundOff();
    void fullScreenSet();
    void normalScreenSet();

private slots:
    void on_musicModeButton_clicked();
    void on_soundModeButton_clicked();
    void on_screenModeButton_stateChanged(int arg1);

private:
    Ui::Settings *ui;
    bool* _settings;
    void setIcons();
};

#endif // SETTINGS_H
