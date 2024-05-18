#ifndef ADDBUILDINGFORM_H
#define ADDBUILDINGFORM_H

#include <QWidget>
#include "cage.h"

namespace Ui {
class AddBuildingForm;
}

class AddBuildingForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddBuildingForm(Cage* cage, QWidget *parent = nullptr);
    ~AddBuildingForm();

signals:
    void addBuilding(Cage::BuildingType type);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();

private:
    Ui::AddBuildingForm *ui;
    Cage* m_cage;
};

#endif // ADDBUILDINGFORM_H
