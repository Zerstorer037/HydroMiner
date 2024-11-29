#ifndef HISTORICO_H
#define HISTORICO_H

#include <QMainWindow>

namespace Ui {
class historico;
}

class historico : public QMainWindow
{
    Q_OBJECT

public:
    explicit historico(QWidget *parent = nullptr);
    ~historico();

signals:
    void goToAlarma();
    void goToActual();
    void goToMenu();

private:
    Ui::historico *ui;

    void setupConnections();
};

#endif // HISTORICO_H
