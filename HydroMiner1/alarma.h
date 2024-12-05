#ifndef ALARMA_H
#define ALARMA_H

#include <QMainWindow>
#include <QLabel>  // Incluye la clase para el widget de etiqueta
#include <QDateTimeEdit>  // Incluye la clase para edición de fechas y horas
#include <QPushButton>  // Incluye la clase para botones

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
    // Señales que indican cuándo ir a otras vistas
    void goToActual();
    void goToHistorico();
    void goToMenu();

private:
    Ui::alarma *ui;

    // Métodos privados
    void setupConnections();  // Establece las conexiones de las señales de los botones
    void actualizarLabel(QLabel* label, const QString& estado, double desviacion, double promedio, const QString& tipo, double derivada);  // Actualiza la etiqueta con la clasificación, desviación estándar, promedio y derivada

    // Funciones para calcular desviación estándar, promedio y primera derivada
    double calcularDesviacionEstandar(const QVector<double>& datos);  // Calcula la desviación estándar de un conjunto de datos
    double calcularPromedio(const QVector<double>& datos);  // Calcula el promedio de un conjunto de datos
    double calcularPrimeraDerivada(const QVector<double>& datos);  // Calcula la primera derivada (tasa de cambio)

    // Función para clasificar los parámetros
    QString clasificarParametro(double valor, double valorMinimo, double valorMaximo);  // Clasifica el parámetro (pH, TDS, temperatura) en categorías como "Peligroso", "Mejorable" o "Seguro"

    void fetchDataFromFirebase();  // Función para obtener los datos desde Firebase

    QVector<QJsonObject> datosDeFirebase;  // Almacena los datos obtenidos de Firebase

    // Declaración de los labels para mostrar los resultados en la interfaz
    QLabel *label_PH;  // Etiqueta para mostrar el valor del pH
    QLabel *label_TDS;  // Etiqueta para mostrar el valor del TDS
    QLabel *label_TEMP;  // Etiqueta para mostrar el valor de la temperatura

public slots:
    // Slot para actualizar los datos de la alarma, que recibe los datos de pH, TDS y temperatura
    void actualizarAlarma(const QVector<double>& pH, const QVector<double>& TDS, const QVector<double>& temperatura);
};

#endif // ALARMA_H
