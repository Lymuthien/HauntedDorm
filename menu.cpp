#include "menu.h"
#include "ui_menu.h"

#include <QMessageBox>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

Menu::Menu(QPixmap* skins, bool* skinsCode, int* coins, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Menu)
    , m_skins(skins)
    , m_coins(coins)
    , m_skinsCode(skinsCode)
{
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

void Menu::updateBtnText() {
    if (m_skinsCode[1]) ui->pushButton_10->setText("");
    if (m_skinsCode[2]) ui->pushButton_12->setText("");
    if (m_skinsCode[3]) ui->pushButton_5->setText("");
    if (m_skinsCode[4]) ui->pushButton_13->setText("");
    if (m_skinsCode[5]) ui->pushButton_14->setText("");
    if (m_skinsCode[6]) ui->pushButton_16->setText("");
    if (m_skinsCode[7]) ui->pushButton_15->setText("");
    if (m_skinsCode[8]) ui->skin1Btn->setText("");
    if (m_skinsCode[9]) ui->skin2Btn->setText("");
    if (m_skinsCode[10]) ui->skin3Btn->setText("");
    if (m_skinsCode[11]) ui->skin4Btn->setText("");
}

void Menu::setCoinsLabel(QString str) {
    ui->label->setText(str);
    *m_coins = str.toInt();
}

Menu::~Menu() {
    delete ui;
}

void Menu::on_infoBtn_clicked() {
    emit btnClicked();
    QMessageBox::information(nullptr, "Информация об игре",
        "   Вы попадаете в общежитие, заполненное призраками. Ваша задача - выжить. Развивайтесь, прокачивайте оружие и здания, делайте все, чтобы убить призрака.\n"
        "   В начале игры найдите свободную комнату и лягте спать. Как только это произошло, на ваш временный баланс начисляются монеты, доход зависит от уровня кровати.\n"
        "   На пустых клетках пола в выбранной комнате вы можете строить и улучшать различные здания за монеты и энергию. Здания могут приносить доход (монеты и энергия), "
        "атаковать призрака, а также выполнять различные функции.\n"
        "   Вы не можете удалить особые здания.\n"
        "   Призрак атакует случайную комнату среди людей и наносит урон по двери. Если вдруг вы не заняли комнату или призрак сломал вашу дверь - игра окончена...");
}

void Menu::setSkin(QPixmap skin) {
    ui->skinImg->setPixmap(skin);
}

QPixmap Menu::getSkin() {
    return ui->skinImg->pixmap(Qt::ReturnByValueConstant());
}


void Menu::on_pushButton_6_clicked()
{
    if (m_skinsCode[0])
        ui->skinImg->setPixmap(m_skins[0]);
}


void Menu::on_pushButton_10_clicked()
{
    if (m_skinsCode[1])
        ui->skinImg->setPixmap(m_skins[1]);
    else if (*m_coins >= 2228) {
        setCoinsLabel(QString::number(*m_coins - 2228));
        ui->pushButton_10->setText("");
        m_skinsCode[1] = 1;
    }
}


void Menu::on_pushButton_12_clicked()
{
    if (m_skinsCode[2])
        ui->skinImg->setPixmap(m_skins[2]);
    else if (*m_coins >= 640) {
        setCoinsLabel(QString::number(*m_coins - 640));
        ui->pushButton_12->setText("");
        m_skinsCode[2] = 1;
    }
}


void Menu::on_pushButton_5_clicked()
{
    if (m_skinsCode[3])
        ui->skinImg->setPixmap(m_skins[3]);
    else if (*m_coins >= 1485) {
        setCoinsLabel(QString::number(*m_coins - 1485));
        ui->pushButton_5->setText("");
        m_skinsCode[3] = 1;
    }
}


void Menu::on_pushButton_13_clicked()
{
    if (m_skinsCode[4])
        ui->skinImg->setPixmap(m_skins[4]);
    else if (*m_coins >= 1575) {
        setCoinsLabel(QString::number(*m_coins - 1575));
        ui->pushButton_13->setText("");
        m_skinsCode[4] = 1;
    }
}


void Menu::on_pushButton_14_clicked()
{
    if (m_skinsCode[5])
        ui->skinImg->setPixmap(m_skins[5]);
    else if (*m_coins >= 3260) {
        setCoinsLabel(QString::number(*m_coins - 3260));
        ui->pushButton_14->setText("");
        m_skinsCode[5] = 1;
    }
}


void Menu::on_pushButton_16_clicked()
{
    if (m_skinsCode[6])
        ui->skinImg->setPixmap(m_skins[6]);
    else if (*m_coins >= 950) {
        setCoinsLabel(QString::number(*m_coins - 950));
        ui->pushButton_16->setText("");
        m_skinsCode[6] = 1;
    }
}


void Menu::on_pushButton_15_clicked()
{
    if (m_skinsCode[7])
        ui->skinImg->setPixmap(m_skins[7]);
    else if (*m_coins >= 1350) {
        setCoinsLabel(QString::number(*m_coins - 1350));
        ui->pushButton_15->setText("");
        m_skinsCode[7] = 1;
    }
}


void Menu::on_skin1Btn_clicked()
{
    if (m_skinsCode[8])
        ui->skinImg->setPixmap(m_skins[8]);
    else if (*m_coins >= 5555) {
        setCoinsLabel(QString::number(*m_coins - 5555));
        ui->skin1Btn->setText("");
        m_skinsCode[8] = 1;
    }
}


void Menu::on_skin2Btn_clicked()
{
    if (m_skinsCode[9])
        ui->skinImg->setPixmap(m_skins[9]);
    else if (*m_coins >= 5555) {
        setCoinsLabel(QString::number(*m_coins - 5555));
        ui->skin2Btn->setText("");
        m_skinsCode[9] = 1;
    }
}


void Menu::on_skin3Btn_clicked()
{
    if (m_skinsCode[10])
        ui->skinImg->setPixmap(m_skins[10]);
    else if (*m_coins >= 5555) {
        setCoinsLabel(QString::number(*m_coins - 5555));
        ui->skin3Btn->setText("");
        m_skinsCode[10] = 1;
    }
}


void Menu::on_skin4Btn_clicked()
{
    if (m_skinsCode[11])
        ui->skinImg->setPixmap(m_skins[11]);
    else if (*m_coins >= 5555) {
        setCoinsLabel(QString::number(*m_coins - 5555));
        ui->skin4Btn->setText("");
        m_skinsCode[11] = 1;
    }
}

void Menu::on_pushButton_clicked() {
    delete this;
}

