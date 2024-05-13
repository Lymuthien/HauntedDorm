#ifndef MENU_H
#define MENU_H

#include <QWidget>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

    void SetCoinsLbl(QString str);

signals:
    void settingsBtnClicked();
    void startBtnClicked();
    void btnClicked();

private slots:
    void on_infoBtn_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
