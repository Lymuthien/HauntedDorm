#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(bool victory, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameOver)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle(" ");
    this->setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMinimizeButtonHint & ~Qt::WindowMaximizeButtonHint);

    if (victory)
    {
        ui->loseLbl->hide();
        ui->gameOverLbl->setStyleSheet("color: #a7db81;");
        ui->pushButton->setStyleSheet("background: rgba(167, 219, 129, 0.5);"
                                      "color: black;");
    }
    else
    {
        ui->victoryLbl->hide();
        ui->gameOverLbl->setStyleSheet("color: rgb(156, 138, 141);");
    }
    connect(ui->pushButton, &QPushButton::clicked, this, [=]() {emit goToMenu(victory); hide();});
}

GameOver::~GameOver()
{
    delete ui;
}


