#include "addbuildingform.h"
#include "ui_addbuildingform.h"

AddBuildingForm::AddBuildingForm(Cage* cage, QWidget *parent)
    : QWidget(parent), ui(new Ui::AddBuildingForm), _cage(cage){
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("Добавить здание");
    this->setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMinimizeButtonHint & ~Qt::WindowMaximizeButtonHint);
}

AddBuildingForm::~AddBuildingForm() {
    delete ui;
}

void AddBuildingForm::on_pushButton_clicked() {
    emit addBuilding(Cage::ShellyType);
    this->hide();
}

void AddBuildingForm::on_pushButton_2_clicked() {
    emit addBuilding(Cage::Ps4Type);
    this->hide();
}

void AddBuildingForm::on_pushButton_7_clicked() {
    emit addBuilding(Cage::SixBybeType);
    this->hide();
}

void AddBuildingForm::on_pushButton_4_clicked() {
    emit addBuilding(Cage::HookahType);
    this->hide();
}

void AddBuildingForm::on_pushButton_3_clicked()
{
    emit addBuilding(Cage::DotaType);
    this->hide();
}

void AddBuildingForm::on_pushButton_5_clicked() {
    emit addBuilding(Cage::HammerType);
    this->hide();
}
