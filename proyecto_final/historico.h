#ifndef HISTORICO_H
#define HISTORICO_H

#include <QtCharts>
#include <QNetworkAccessManager>
#include <QJsonObject>
#include <QDateTime>

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

public slots:
    void updateData(const QVector<QJsonObject> &datos);
    void fetchDataFromFirebase();
    void generarGrafico();
    void configurarGraficos();
    void setupConnections();
    void ajustarEjes(QLineSeries *serie, QChart *grafico);
    void ajustarEjesConDias(QLineSeries *serie, QChart *grafico, int dias);

    QVector<QJsonObject> obtenerDatosDePrueba();

private:
    Ui::historico *ui;

    // Gráficos y series
    QChart *graficoPH;
    QChartView *graficoViewPH;
    QChart *graficoTEMP;
    QChartView *graficoViewTEMP;
    QChart *graficoTDS;
    QChartView *graficoViewTDS;
    QLineSeries *seriePH;
    QLineSeries *serieTEMP;
    QLineSeries *serieTDS;

    // Fecha
    QDateTime obtenerFechaDesde();
    QDateTime obtenerFechaHasta();

    // Red
    QNetworkAccessManager *manager;
};

#endif // HISTORICO_H
