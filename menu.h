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
    explicit Menu(QPixmap *skins, QWidget *parent = nullptr);
    ~Menu();

    void setCoinsLabel(QString str);
    void setSkin(QPixmap skin);
    QPixmap getSkin();

signals:
    void settingsBtnClicked();
    void startBtnClicked();
    void btnClicked();

private slots:
    void on_infoBtn_clicked();
    void on_skin1Btn_clicked();
    void on_skin2Btn_clicked();
    void on_skin3Btn_clicked();
    void on_skin4Btn_clicked();

private:
    Ui::Menu *ui;
    QPixmap* m_skins;
};

#endif // MENU_H
