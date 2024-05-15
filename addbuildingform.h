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

private:
    Ui::AddBuildingForm *ui;
    Cage* _cage;
};

#endif // ADDBUILDINGFORM_H
