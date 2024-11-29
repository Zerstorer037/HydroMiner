#include "historico.h"
#include "ui_historico.h"

historico::historico(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::historico)
{
    ui->setupUi(this);
    setupConnections();
}

historico::~historico()
{
    delete ui;
}

void historico::setupConnections()
{
    connect(ui->Bactual, &QPushButton::clicked, this, [this]() { emit goToActual(); });
    connect(ui->Balarma, &QPushButton::clicked, this, [this]() { emit goToAlarma(); });
    connect(ui->Bmenu, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->Bvolver, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
}
