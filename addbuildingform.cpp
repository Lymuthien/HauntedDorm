#include "addbuildingform.h"
#include "ui_addbuildingform.h"

AddBuildingForm::AddBuildingForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AddBuildingForm)
{
    ui->setupUi(this);
}

AddBuildingForm::~AddBuildingForm()
{
    delete ui;
}
