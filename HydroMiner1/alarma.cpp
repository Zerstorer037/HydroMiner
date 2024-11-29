#include "alarma.h"
#include "ui_alarma.h"

alarma::alarma(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::alarma)
{
    ui->setupUi(this);
    setupConnections();

}
void alarma::setupConnections()
{
    connect(ui->Bactual, &QPushButton::clicked, this, [this]() { emit goToActual(); });
    connect(ui->Bhistorico, &QPushButton::clicked, this, [this]() { emit goToHistorico(); });
    connect(ui->Bmenu, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->Bvolver, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
}
alarma::~alarma()
{
    delete ui;
}
