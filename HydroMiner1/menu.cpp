#include "menu.h"
#include "ui_menu.h"


Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
    , actualw(new actual(this))  // Crea una instancia de la ventana 'actual' como hijo de 'Menu'
    , historicow(new historico(this))  // Crea una instancia de la ventana 'historico' como hijo de 'Menu'
    , alarmaw(new alarma(this))  // Crea una instancia de la ventana 'alarma' como hijo de 'Menu'
{
    ui->setupUi(this);
    setupConnections();
}

Menu::~Menu()
{
    delete ui;
}

// Función para configurar las conexiones entre botones y funciones
void Menu::setupConnections()
{
    // Conexiones de botones de la interfaz con funciones para cambiar entre las vistas
    connect(ui->Bactual, &QPushButton::clicked, this, &Menu::goToActual);  // Botón para ir a la vista actual
    connect(ui->Bhistorico, &QPushButton::clicked, this, &Menu::goToHistorico);  // Botón para ir a la vista histórico
    connect(ui->Balarma, &QPushButton::clicked, this, &Menu::goToAlarma);  // Botón para ir a la vista alarma
    connect(ui->estado, &QPushButton::clicked, this, &Menu::goToActual);  // Botón para ir a la vista actual
    connect(ui->registro, &QPushButton::clicked, this, &Menu::goToHistorico);  // Botón para ir a la vista histórico
    connect(ui->alarma, &QPushButton::clicked, this, &Menu::goToAlarma);  // Botón para ir a la vista alarma

    // Conexiones de señales y slots entre las diferentes ventanas
    connect(actualw, &actual::goToMenu, this, &Menu::goToMenu);  // Desde la ventana 'actual', ir al menú
    connect(actualw, &actual::goToAlarma, this, &Menu::goToAlarma);  // Desde la ventana 'actual', ir a la ventana de alarma
    connect(actualw, &actual::goToHistorico, this, &Menu::goToHistorico);  // Desde la ventana 'actual', ir a la ventana histórica

    connect(alarmaw, &alarma::goToMenu, this, &Menu::goToMenu);  // Desde la ventana 'alarma', ir al menú
    connect(alarmaw, &alarma::goToActual, this, &Menu::goToActual);  // Desde la ventana 'alarma', ir a la ventana 'actual'
    connect(alarmaw, &alarma::goToHistorico, this, &Menu::goToHistorico);  // Desde la ventana 'alarma', ir a la ventana histórica

    connect(historicow, &historico::goToMenu, this, &Menu::goToMenu);  // Desde la ventana 'historico', ir al menú
    connect(historicow, &historico::goToAlarma, this, &Menu::goToAlarma);  // Desde la ventana 'historico', ir a la ventana de alarma
    connect(historicow, &historico::goToActual, this, &Menu::goToActual);  // Desde la ventana 'historico', ir a la ventana 'actual'
}

// Función para mostrar la ventana de alarma
void Menu::goToAlarma()
{
    alarmaw->hide();  // Ocultar la ventana de alarma
    actualw->hide();  // Ocultar la ventana 'actual'
    historicow->hide();  // Ocultar la ventana histórica
    this->hide();  // Ocultar el menú
    alarmaw->show();  // Mostrar la ventana de alarma
}

// Función para mostrar la ventana actual
void Menu::goToActual()
{
    alarmaw->hide();  // Ocultar la ventana de alarma
    historicow->hide();  // Ocultar la ventana histórica
    this->hide();  // Ocultar el menú
    actualw->show();  // Mostrar la ventana actual
}

// Función para mostrar la ventana histórica
void Menu::goToHistorico()
{
    alarmaw->hide();  // Ocultar la ventana de alarma
    actualw->hide();  // Ocultar la ventana 'actual'
    this->hide();  // Ocultar el menú
    historicow->show();  // Mostrar la ventana histórica
}

// Función para regresar al menú desde cualquier vista
void Menu::goToMenu()
{
    alarmaw->hide();  // Ocultar la ventana de alarma
    actualw->hide();  // Ocultar la ventana 'actual'
    historicow->hide();  // Ocultar la ventana histórica
    this->show();  // Mostrar el menú
}
