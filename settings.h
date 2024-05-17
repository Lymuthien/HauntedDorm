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
    void setIcons();

    Ui::Settings *ui;
    bool* m_settings;
};

#endif // SETTINGS_H
