#ifndef UPGRATEFORM_H
#define UPGRATEFORM_H

#include <QWidget>
#include "cage.h"

namespace Ui {
class upgrateForm;
}

class UpgrateForm : public QWidget
{
    Q_OBJECT

public:
    explicit UpgrateForm(Cage* cage, QWidget *parent = nullptr);
    ~UpgrateForm();

private:
    Ui::upgrateForm *ui;
    Cage* _cage;
};

#endif // UPGRATEFORM_H
