#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
    , actualw(new actual(this))
    , historicow(new historico(this))
    , alarmaw(new alarma(this))
{
    ui->setupUi(this);
    setupConnections();
}

Menu::~Menu()
{
    delete ui; // Widgets hijos son destruidos automáticamente.
}

void Menu::setupConnections()
{
    connect(ui->Bactual, &QPushButton::clicked, this, &Menu::goToActual);
    connect(ui->Bhistorico, &QPushButton::clicked, this, &Menu::goToHistorico);
    connect(ui->Balarma, &QPushButton::clicked, this, &Menu::goToAlarma);
    connect(ui->estado, &QPushButton::clicked, this, &Menu::goToActual);
    connect(ui->registro, &QPushButton::clicked, this, &Menu::goToHistorico);
    connect(ui->alarma, &QPushButton::clicked, this, &Menu::goToAlarma);

    connect(actualw, &actual::goToMenu, this, &Menu::goToMenu);
    connect(actualw, &actual::goToAlarma, this, &Menu::goToAlarma);
    connect(actualw, &actual::goToHistorico, this, &Menu::goToHistorico);

    connect(alarmaw, &alarma::goToMenu, this, &Menu::goToMenu);
    connect(alarmaw, &alarma::goToActual, this, &Menu::goToActual);
    connect(alarmaw, &alarma::goToHistorico, this, &Menu::goToHistorico);

    connect(historicow, &historico::goToMenu, this, &Menu::goToMenu);
    connect(historicow, &historico::goToAlarma, this, &Menu::goToAlarma);
    connect(historicow, &historico::goToActual, this, &Menu::goToActual);
}

void Menu::goToAlarma()
{
    alarmaw->hide();
    actualw->hide();
    historicow->hide();
    this->hide();
    alarmaw->show();
}

void Menu::goToActual()
{
    alarmaw->hide();
    historicow->hide();
    this->hide();
    actualw->show();
}

void Menu::goToHistorico()
{
    alarmaw->hide();
    actualw->hide();
    this->hide();
    historicow->show();
}

void Menu::goToMenu()
{
    alarmaw->hide();
    actualw->hide();
    historicow->hide();
    this->show();
}
