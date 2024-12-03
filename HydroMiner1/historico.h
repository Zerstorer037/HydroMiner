#ifndef HISTORICO_H
#define HISTORICO_H

#include <QtCharts>  // Incluye las bibliotecas necesarias para trabajar con gráficos en Qt
#include <QNetworkAccessManager>  // Para realizar solicitudes HTTP (obtener datos)
#include <QJsonObject>  // Para manejar objetos JSON
#include <QDateTime>  // Para manejar fechas y horas

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
    // Señales que indican cuándo ir a otras vistas
    void goToAlarma();
    void goToActual();
    void goToMenu();

public slots:
    // Slots que permiten la actualización de los datos, la generación de gráficos y la configuración de gráficos
    void updateData(const QVector<QJsonObject> &datos);  // Actualiza los datos del gráfico con los nuevos datos obtenidos
    void generarGrafico();  // Método para generar el gráfico
    void configurarGraficos();  // Configura los gráficos
    void setupConnections();  // Establece las conexiones de las señales
    void ajustarEjes(QLineSeries *serie, QChart *grafico);  // Ajusta los ejes de los gráficos
    void ajustarEjesConDias(QLineSeries *serie, QChart *grafico, int dias);  // Ajusta los ejes con los días transcurridos

    // Función de prueba para obtener los datos
    QVector<QJsonObject> obtenerDatosDePrueba();

private:
    Ui::historico *ui;  // Puntero a la interfaz de usuario generada

    // Declaración de gráficos y series
    QChart *graficoPH;  // Gráfico para el pH
    QChartView *graficoViewPH;  // Vista del gráfico para el pH
    QChart *graficoTEMP;  // Gráfico para la temperatura
    QChartView *graficoViewTEMP;  // Vista del gráfico para la temperatura
    QChart *graficoTDS;  // Gráfico para el TDS
    QChartView *graficoViewTDS;  // Vista del gráfico para el TDS
    QLineSeries *seriePH;  // Serie de datos para el pH
    QLineSeries *serieTEMP;  // Serie de datos para la temperatura
    QLineSeries *serieTDS;  // Serie de datos para el TDS

    // Métodos para obtener fechas
    QDateTime obtenerFechaDesde();  // Devuelve la fecha seleccionada de inicio
    QDateTime obtenerFechaHasta();  // Devuelve la fecha seleccionada de fin

    // Declaración de objeto para gestionar la red y realizar solicitudes
    QNetworkAccessManager *manager;
};

#endif // HISTORICO_H
