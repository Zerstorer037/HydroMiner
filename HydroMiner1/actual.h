#ifndef ACTUAL_H
#define ACTUAL_H

#include <QMainWindow>
#include <QLabel>

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
    void fetchDataFromFirebase(); // Método modificado para usar datos simulados
    void actualizarLabel(QLabel* label, const QString& clasificacion, const QString& tipo);

    // Funciones para clasificar los parámetros
    QString clasificarPh(double ph);
    QString clasificarTds(double tds);
    QString clasificarTemperature(double temp);
};

#endif // ACTUAL_H
