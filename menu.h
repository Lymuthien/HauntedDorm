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
    explicit Menu(QPixmap *skins, bool* skinsCode, int *coins, QWidget *parent = nullptr);
    ~Menu();

    void setCoinsLabel(QString str);
    void updateBtnText();
    void setSkin(QPixmap skin);
    QPixmap getSkin();

signals:
    void settingsBtnClicked();
    void startBtnClicked();
    void btnClicked();

private slots:
    void on_infoBtn_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_13_clicked();
    void on_pushButton_14_clicked();
    void on_pushButton_16_clicked();
    void on_pushButton_15_clicked();
    void on_skin1Btn_clicked();
    void on_skin2Btn_clicked();
    void on_skin3Btn_clicked();
    void on_skin4Btn_clicked();

    void on_pushButton_clicked();

private:

    Ui::Menu *ui;
    QPixmap* m_skins;
    int* m_coins;
    bool* m_skinsCode;
};

#endif // MENU_H
