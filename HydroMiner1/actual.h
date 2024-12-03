#ifndef ACTUAL_H
#define ACTUAL_H

#include <QMainWindow>
#include <QLabel>  // Incluye la clase para el widget de etiqueta

namespace Ui {
class actual;
}

class actual : public QMainWindow
{
    Q_OBJECT

public:
    explicit actual(QWidget *parent = nullptr);  // Constructor, toma un puntero al widget padre
    ~actual();  // Destructor

signals:
    // Señales que indican cuándo ir a otras vistas
    void goToAlarma();
    void goToHistorico();
    void goToMenu();

private:
    Ui::actual *ui;  // Puntero a la interfaz de usuario generada

    // Métodos privados
    void setupConnections();  // Establece las conexiones de las señales de los botones
    void fetchDataFromFirebase();  // Método para obtener datos de Firebase (modificado para datos simulados)
    void actualizarLabel(QLabel* label, const QString& clasificacion, const QString& tipo);  // Actualiza la etiqueta con clasificación

    // Funciones para clasificar los parámetros
    QString clasificarPh(double ph);  // Clasificación del valor de pH
    QString clasificarTds(double tds);  // Clasificación del valor de TDS
    QString clasificarTemperature(double temp);  // Clasificación de la temperatura
};

#endif // ACTUAL_H
