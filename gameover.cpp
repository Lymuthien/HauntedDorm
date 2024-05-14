#include "gameover.h"
#include "ui_gameover.h"

GameOver::GameOver(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::GameOver)
{
    ui->setupUi(this);
}

GameOver::~GameOver()
{
    delete ui;
}
