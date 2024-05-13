#ifndef ADDBUILDINGFORM_H
#define ADDBUILDINGFORM_H

#include <QWidget>

namespace Ui {
class AddBuildingForm;
}

class AddBuildingForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddBuildingForm(QWidget *parent = nullptr);
    ~AddBuildingForm();

private:
    Ui::AddBuildingForm *ui;
};

#endif // ADDBUILDINGFORM_H
