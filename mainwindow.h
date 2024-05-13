#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QVBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setFullScreen(bool value);

signals:

private:
    bool _isFullScreen = false;

private slots:
    //void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
