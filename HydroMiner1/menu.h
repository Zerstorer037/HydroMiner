#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "alarma.h"
#include "historico.h"
#include "actual.h"

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
    actual *actualw;
    historico *historicow;
    alarma *alarmaw;

    void setupConnections();

public slots:
    void goToActual();
    void goToAlarma();
    void goToHistorico();
    void goToMenu();
};

#endif // MENU_H
