#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "alarma.h"  // Incluir la clase alarma, que se utiliza en el menú
#include "historico.h"  // Incluir la clase historico, que también se utiliza en el menú
#include "actual.h"  // Incluir la clase actual, que se utiliza en el menú

namespace Ui {
class Menu;
}


class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private:
    Ui::Menu *ui;

    // Punteros a las clases de las diferentes vistas (alarma, historico, actual)
    actual *actualw;
    historico *historicow;
    alarma *alarmaw;

    // Método privado para establecer las conexiones de señales y slots
    void setupConnections();

public slots:
    // Slots públicos que permiten la navegación entre las diferentes vistas
    void goToActual();  // Navegar a la vista 'Actual'
    void goToAlarma();  // Navegar a la vista 'Alarma'
    void goToHistorico();  // Navegar a la vista 'Historico'
    void goToMenu();  // Navegar a la vista principal 'Menu'
};

#endif // MENU_H
