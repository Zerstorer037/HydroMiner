#include "actual.h"
#include "ui_actual.h"

actual::actual(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::actual)
{
    ui->setupUi(this);
    setupConnections();
}

actual::~actual()
{
    delete ui; // No es estrictamente necesario, pero es buena práctica en el destructor.
}

void actual::setupConnections()
{
    connect(ui->Balarma, &QPushButton::clicked, this, [this]() { emit goToAlarma(); });
    connect(ui->Bhistorico, &QPushButton::clicked, this, [this]() { emit goToHistorico(); });
    connect(ui->Bmenu, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->Bvolver, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
}
