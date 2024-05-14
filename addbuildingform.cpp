#include "addbuildingform.h"
#include "ui_addbuildingform.h"

AddBuildingForm::AddBuildingForm(Cage* cage, QWidget *parent)
    : QWidget(parent), ui(new Ui::AddBuildingForm), _cage(cage)
{
    ui->setupUi(this);
    this->setFixedSize(this->size());
    this->setWindowTitle("Добавить здание");
    this->setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMinimizeButtonHint & ~Qt::WindowMaximizeButtonHint);
}

AddBuildingForm::~AddBuildingForm()
{
    delete ui;
}
