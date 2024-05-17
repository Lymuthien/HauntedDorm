#include "upgrateform.h"
#include "ui_upgrateform.h"

UpgrateForm::UpgrateForm(Cage* cage, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::upgrateForm), m_cage(cage)
{
    ui->setupUi(this);
    setFixedSize(this->size());
    setWindowTitle("");
    setWindowFlags((this->windowFlags() | Qt::CustomizeWindowHint) & ~Qt::WindowMinimizeButtonHint & ~Qt::WindowMaximizeButtonHint);
    updateText();
}

void UpgrateForm::updateText() {
    ui->buildingName->setText(m_cage->getTypeString());
    ui->buildingImage->setPixmap(m_cage->getPixmap());

    if (m_cage->getType() == Cage::DotaType || m_cage->getType() == Cage::HookahType || m_cage->getType() == Cage::HammerType
        || m_cage->getType() == Cage::SixBybeType) {
        ui->upgradeBtn->hide();
        ui->label->hide();
    }
    else {
        ui->upgradeBtn->setText(QString::number(m_cage->moneyCost() * 2) + "m, " + QString::number(m_cage->energyCost() * 2) + "e");
        ui->upgradeBtn->show();
        ui->label->show();
    }

    if (m_cage->getType() == Cage::BedType || m_cage->getType() == Cage::DoorType) {
        ui->sellBtn->hide();
        ui->label_3->hide();
    }
    else
        ui->sellBtn->setText(QString::number(m_cage->moneyCost() * 0.75) + "m, " + QString::number(m_cage->energyCost() * 0.75) + "e");
}


UpgrateForm::~UpgrateForm()
{
    delete ui;
}

void UpgrateForm::on_upgradeBtn_clicked()
{
    m_cage->upgrade();
    updateText();
    hide();
}

void UpgrateForm::on_sellBtn_clicked() {
    m_cage->deleteBuilding();
    hide();
}

