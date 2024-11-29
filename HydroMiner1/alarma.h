#ifndef ALARMA_H
#define ALARMA_H

#include <QMainWindow>


namespace Ui {
class alarma;
}

class alarma : public QMainWindow
{
    Q_OBJECT

public:
    explicit alarma(QWidget *parent = nullptr);
    ~alarma();
signals:
    void goToActual();
    void goToHistorico();
    void goToMenu();

private:
    Ui::alarma *ui;
    void setupConnections();
};

#endif // ALARMA_H
