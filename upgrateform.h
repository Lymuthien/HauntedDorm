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
    void updateText();

private slots:
    void on_upgradeBtn_clicked();

    void on_sellBtn_clicked();

private:
    Ui::upgrateForm *ui;
    Cage* m_cage;
};

#endif // UPGRATEFORM_H
