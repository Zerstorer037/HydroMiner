#ifndef ALARMA_H
#define ALARMA_H

#include <QMainWindow>
#include <QLabel>
#include <QDateTimeEdit>
#include <QPushButton>

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
    void actualizarLabel(QLabel* label, const QString& estado, double desviacion, double promedio, const QString& tipo);
    double calcularDesviacionEstandar(const QVector<double>& datos);
    double calcularPromedio(const QVector<double>& datos);
    QString clasificarParametro(double valor, double valorMinimo, double valorMaximo);
    void fetchDataFromFirebase(); // Declarar la función que obtiene los datos de Firebase
    QVector<QJsonObject> datosDeFirebase;  // Aquí se guardan los datos de Firebase
    // Declaración de los labels
    QLabel *label_PH;
    QLabel *label_TDS;
    QLabel *label_TEMP;

public slots:
    void actualizarAlarma(const QVector<double>& pH, const QVector<double>& TDS, const QVector<double>& temperatura);
};

#endif // ALARMA_H
