#ifndef ACTUAL_H
#define ACTUAL_H

#include <QMainWindow>

namespace Ui {
class actual;
}

class actual : public QMainWindow
{
    Q_OBJECT

public:
    explicit actual(QWidget *parent = nullptr);
    ~actual();

signals:
    void goToAlarma();
    void goToHistorico();
    void goToMenu();

private:
    Ui::actual *ui;

    void setupConnections();
};

#endif // ACTUAL_H
