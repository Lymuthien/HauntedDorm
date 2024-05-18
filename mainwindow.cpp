#include "mainwindow.h"

#include <QPalette>
#include <QFile>
#include <QScreen>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowIcon(QIcon(":images/resourses/images/icon.jpg"));
    setGeometry(QApplication::primaryScreen()->geometry());
    setFixedSize(size());
    this->setFullScreen(0);
}

void MainWindow::setFullScreen(bool value)
{
    if (value) showFullScreen();
    else showNormal();
}

