#include "menu.h"
#include "ui_menu.h"

#include <QMessageBox>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

Menu::Menu(QPixmap* skins, QWidget *parent) : QWidget(parent), ui(new Ui::Menu), m_skins(skins) {
    ui->setupUi(this);

    QPalette palette = this->palette();
    this->setAutoFillBackground(true);
    palette.setBrush(QPalette::Window, QBrush
                     (QPixmap(":/bg/resourses/images/menu-bg.jpg").scaled(QSize(WINDOW_WIDTH, WINDOW_HEIGHT), Qt::IgnoreAspectRatio)));
    this->setPalette(palette);

    connect(ui->settingsBtn, &QPushButton::clicked, this, &Menu::settingsBtnClicked);
    connect(ui->settingsBtn, &QPushButton::clicked, this, &Menu::btnClicked);
    connect(ui->startBtn, &QPushButton::clicked, this, &Menu::startBtnClicked);
    connect(ui->startBtn, &QPushButton::clicked, this, &Menu::btnClicked);
}

void Menu::setCoinsLabel(QString str) {
    ui->label->setText(str);
}

Menu::~Menu() {
    delete ui;
}

void Menu::on_infoBtn_clicked() {
    emit btnClicked();
    QMessageBox::information(nullptr, "Информация об игре", "   Вы попадаете в общежитие, заполненное призраками. Ваша задача - выжить. Развивайтесь, прокачивайте оружие и здания, делайте все, чтобы убить призрака.\n"
                                                            "   В начале игры найдите свободную комнату и лягте спать. Как только это произошло, на ваш временный баланс начисляются монеты, доход зависит от уровня кровати.\n"
                                                            "   На пустых клетках пола в выбранной комнате вы можете строить и улучшать различные здания за монеты и энергию. Здания могут приносить доход (монеты и энергия), "
                                                            "атаковать призрака, а также выполнять различные функции.\n"
                                                            "   Призрак атакует случайную комнату среди людей и наносит урон по двери. Для защиты своевременно ремонтируйте дверь в комнату. Если вдруг вы не заняли комнату"
                                                            "или призрак сломал вашу дверь - игра окончена...");
}

void Menu::setSkin(QPixmap skin) {
    ui->skinImg->setPixmap(skin);
}

QPixmap Menu::getSkin() {
    return ui->skinImg->pixmap(Qt::ReturnByValueConstant());
}

void Menu::on_skin1Btn_clicked() {
    ui->skinImg->setPixmap(m_skins[0]);
}

void Menu::on_skin2Btn_clicked() {
    ui->skinImg->setPixmap(m_skins[1]);
}

void Menu::on_skin3Btn_clicked() {
    ui->skinImg->setPixmap(m_skins[2]);
}

void Menu::on_skin4Btn_clicked() {
    ui->skinImg->setPixmap(m_skins[3]);
}

