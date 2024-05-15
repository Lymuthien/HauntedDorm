#include "addbuildingform.h"
#include "ui_addbuildingform.h"

AddBuildingForm::AddBuildingForm(Cage* cage, int* money, int* energy, QWidget *parent)
    : QWidget(parent), ui(new Ui::AddBuildingForm), _cage(cage), currentMoney(money), currentEnergy(energy) {
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("Добавить здание");
    this->setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMinimizeButtonHint & ~Qt::WindowMaximizeButtonHint);
}

AddBuildingForm::~AddBuildingForm() {
    delete ui;
}

void AddBuildingForm::on_pushButton_clicked()
{
    if (*currentMoney > -1) {
        emit addBuilding(Cage::ShellyType);
        this->hide();
    }
}

void AddBuildingForm::on_pushButton_2_clicked()
{
    if (*currentMoney > 200) {
        emit addBuilding(Cage::Ps4Type);
        this->hide();
    }
}

void AddBuildingForm::on_pushButton_7_clicked()
{
    if (*currentEnergy > 1024) {
        emit addBuilding(Cage::SixBybeType);
        this->hide();
    }
}

void AddBuildingForm::on_pushButton_4_clicked()
{
    if (*currentMoney > 256) {
        emit addBuilding(Cage::HookahType);
        this->hide();
    }
}

void AddBuildingForm::on_pushButton_3_clicked()
{
    if (*currentEnergy > 128) {
        emit addBuilding(Cage::DotaType);
        this->hide();
    }
}

void AddBuildingForm::on_pushButton_5_clicked()
{
    if (*currentMoney > 512) {
        emit addBuilding(Cage::HammerType);
        this->hide();
    }
}

