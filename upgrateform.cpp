#include "upgrateform.h"
#include "ui_upgrateform.h"

UpgrateForm::UpgrateForm(Cage* cage, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::upgrateForm), _cage(cage)
{
    ui->setupUi(this);
    setFixedSize(this->size());
    setWindowTitle("");
    setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMinimizeButtonHint & ~Qt::WindowMaximizeButtonHint);


}

UpgrateForm::~UpgrateForm()
{
    delete ui;
}
