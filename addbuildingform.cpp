#include "addbuildingform.h"
#include "ui_addbuildingform.h"

AddBuildingForm::AddBuildingForm(Cage* cage, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddBuildingForm)
    , m_cage(cage)
{
    ui->setupUi(this);

    setFixedSize(this->size());
    setWindowTitle("Добавить здание");
    setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMinimizeButtonHint & ~Qt::WindowMaximizeButtonHint);
}

AddBuildingForm::~AddBuildingForm() {
    delete ui;
}

void AddBuildingForm::on_pushButton_clicked() {
    emit addBuilding(Cage::ShellyType);
    hide();
}

void AddBuildingForm::on_pushButton_2_clicked() {
    emit addBuilding(Cage::Ps4Type);
    hide();
}

void AddBuildingForm::on_pushButton_7_clicked() {
    emit addBuilding(Cage::SixBybeType);
    hide();
}

void AddBuildingForm::on_pushButton_4_clicked() {
    emit addBuilding(Cage::HookahType);
    hide();
}

void AddBuildingForm::on_pushButton_3_clicked()
{
    emit addBuilding(Cage::DotaType);
    hide();
}

void AddBuildingForm::on_pushButton_5_clicked() {
    emit addBuilding(Cage::HammerType);
    hide();
}
