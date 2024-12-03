#include "historico.h"
#include "ui_historico.h"
#include <QtCharts>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

// Constructor y Destructor
historico::historico(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::historico)
    , graficoPH(new QChart())
    , graficoViewPH(new QChartView(graficoPH))
    , graficoTEMP(new QChart())
    , graficoViewTEMP(new QChartView(graficoTEMP))
    , graficoTDS(new QChart())
    , graficoViewTDS(new QChartView(graficoTDS))
    , seriePH(new QLineSeries())
    , serieTEMP(new QLineSeries())
    , serieTDS(new QLineSeries())
    , manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    // Configuración inicial de widgets
    ui->desde->setDisplayFormat("yyyy-MM-dd");
    ui->hasta->setDisplayFormat("yyyy-MM-dd");
    ui->desde->setDate(QDate::currentDate());
    ui->hasta->setDate(QDate::currentDate());

    // Configuración de gráficos
    configurarGraficos();

    // Configuración de conexiones
    setupConnections();
}

historico::~historico()
{
    delete ui;
}
// En historico.cpp

QDateTime historico::obtenerFechaDesde()
{
    return ui->desde->dateTime();  // Devuelve la fecha y hora del QDateEdit 'desde'
}

QDateTime historico::obtenerFechaHasta()
{
    return ui->hasta->dateTime();  // Devuelve la fecha y hora del QDateEdit 'hasta'
}
void historico::setupConnections() {
    connect(ui->Bactual, &QPushButton::clicked, this, [this]() { emit goToActual(); });
    connect(ui->Balarma, &QPushButton::clicked, this, [this]() { emit goToAlarma(); });
    connect(ui->Bmenu, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->Bvolver, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->GenerarButton, &QPushButton::clicked, this, &historico::generarGrafico);
}

void historico::configurarGraficos()
{
    graficoPH->addSeries(seriePH);
    graficoPH->setTitle("pH del agua");
    graficoPH->createDefaultAxes();
    graficoPH->axes(Qt::Horizontal).first()->setTitleText("Días");
    graficoPH->axes(Qt::Vertical).first()->setTitleText("pH");

    QVBoxLayout *layoutPH = new QVBoxLayout(ui->graficoPH);
    layoutPH->addWidget(graficoViewPH);
    ui->graficoPH->setLayout(layoutPH);

    graficoTEMP->addSeries(serieTEMP);
    graficoTEMP->setTitle("Temperatura");
    graficoTEMP->createDefaultAxes();
    graficoTEMP->axes(Qt::Horizontal).first()->setTitleText("Días");
    graficoTEMP->axes(Qt::Vertical).first()->setTitleText("Temperatura (°C)");

    QVBoxLayout *layoutTEMP = new QVBoxLayout(ui->graficoTEMP);
    layoutTEMP->addWidget(graficoViewTEMP);
    ui->graficoTEMP->setLayout(layoutTEMP);

    graficoTDS->addSeries(serieTDS);
    graficoTDS->setTitle("TDS");
    graficoTDS->createDefaultAxes();
    graficoTDS->axes(Qt::Horizontal).first()->setTitleText("Días");
    graficoTDS->axes(Qt::Vertical).first()->setTitleText("TDS (ppm)");

    QVBoxLayout *layoutTDS = new QVBoxLayout(ui->graficoTDS);
    layoutTDS->addWidget(graficoViewTDS);
    ui->graficoTDS->setLayout(layoutTDS);
}

void historico::ajustarEjes(QLineSeries *serie, QChart *grafico)
{
    if (serie->count() == 0) {
        qDebug() << "No hay datos en la serie para ajustar ejes.";
        return;
    }

    double minY = serie->at(0).y(), maxY = serie->at(0).y();
    for (int i = 1; i < serie->count(); ++i) {
        minY = std::min(minY, serie->at(i).y());
        maxY = std::max(maxY, serie->at(i).y());
    }

    grafico->axes(Qt::Vertical).first()->setRange(minY, maxY);

    // Ajustar el eje X si es necesario
    if (auto *axisX = dynamic_cast<QDateTimeAxis *>(grafico->axes(Qt::Horizontal).first())) {
        axisX->setFormat("yyyy-MM-dd");
        axisX->setTitleText("Fecha y Hora");
        if (serie->count() > 0) {
            qint64 minX = serie->at(0).x();
            qint64 maxX = serie->at(serie->count() - 1).x();
            axisX->setRange(QDateTime::fromMSecsSinceEpoch(minX), QDateTime::fromMSecsSinceEpoch(maxX));
        }
    }

    qDebug() << "Ejes ajustados: Y (" << minY << ", " << maxY << ")";
}
void historico::updateData(const QVector<QJsonObject> &datos)
{
    // Calcula la diferencia de días
    QDateTime fechaInicio = obtenerFechaDesde();
    QDateTime fechaFin = obtenerFechaHasta();

    int diasDeDiferencia = fechaInicio.daysTo(fechaFin);
    qDebug() << "Días de diferencia entre las fechas: " << diasDeDiferencia;

    // Ahora, vamos a iterar sobre los datos y calcular la diferencia de días
    int diaContador = 0;  // Este contador representará los días desde la fecha de inicio

    for (const QJsonObject &registro : datos) {
        if (registro.contains("pH") && registro["pH"].isDouble() &&
            registro.contains("date") && registro["date"].isString()) {
            QDateTime fecha = QDateTime::fromString(registro["date"].toString(), "yyyy-MM-dd");
            double phValue = registro["pH"].toDouble();
            // Usamos la diferencia de días
            int diaDiferencia = fechaInicio.daysTo(fecha);
            seriePH->append(diaDiferencia, phValue);
        }

        if (registro.contains("Temperatura") && registro["Temperatura"].isDouble() &&
            registro.contains("date") && registro["date"].isString()) {
            QDateTime fecha = QDateTime::fromString(registro["date"].toString(), "yyyy-MM-dd");
            double tempValue = registro["Temperatura"].toDouble();
            // Usamos la diferencia de días
            int diaDiferencia = fechaInicio.daysTo(fecha);
            serieTEMP->append(diaDiferencia, tempValue);
        }

        if (registro.contains("TDS") && registro["TDS"].isDouble() &&
            registro.contains("date") && registro["date"].isString()) {
            QDateTime fecha = QDateTime::fromString(registro["date"].toString(), "yyyy-MM-dd");
            double tdsValue = registro["TDS"].toDouble();
            // Usamos la diferencia de días
            int diaDiferencia = fechaInicio.daysTo(fecha);
            serieTDS->append(diaDiferencia, tdsValue);
        }
    }

    // Ahora ajustamos los ejes
    ajustarEjesConDias(seriePH, graficoPH, diasDeDiferencia);
    ajustarEjesConDias(serieTEMP, graficoTEMP, diasDeDiferencia);
    ajustarEjesConDias(serieTDS, graficoTDS, diasDeDiferencia);
}

// Cambia la implementación de la función para usar el valor de días (int)
void historico::ajustarEjesConDias(QLineSeries *serie, QChart *grafico, int dias)
{
    if (serie->count() == 0) {
        qDebug() << "No hay datos en la serie para ajustar ejes.";
        return;
    }

    double minY = serie->at(0).y(), maxY = serie->at(0).y();
    for (int i = 1; i < serie->count(); ++i) {
        minY = std::min(minY, serie->at(i).y());
        maxY = std::max(maxY, serie->at(i).y());
    }

    grafico->axes(Qt::Vertical).first()->setRange(minY, maxY);

    // Ajustamos el eje X a la cantidad de días
    if (auto *axisX = dynamic_cast<QValueAxis *>(grafico->axes(Qt::Horizontal).first())) {
        axisX->setRange(0, dias);  // Usamos el valor de días directamente
        axisX->setTitleText("Días");
    }

    qDebug() << "Ejes ajustados: X (0, " << dias << ") y Y (" << minY << ", " << maxY << ")";
}

// Función de obtención de datos de prueba
QVector<QJsonObject> historico::obtenerDatosDePrueba()
{
    QVector<QJsonObject> datos;

    // Día 2024-11-20
    QJsonObject registro1;
    registro1["pH"] = 7.35;
    registro1["Temperatura"] = 21.8;
    registro1["TDS"] = 345;
    registro1["date"] = "2024-11-20";
    datos.append(registro1);

    // Día 2024-11-21
    QJsonObject registro2;
    registro2["pH"] = 7.45;
    registro2["Temperatura"] = 22.1;
    registro2["TDS"] = 350;
    registro2["date"] = "2024-11-21";
    datos.append(registro2);

    // Día 2024-11-22
    QJsonObject registro3;
    registro3["pH"] = 7.5;
    registro3["Temperatura"] = 22.3;
    registro3["TDS"] = 355;
    registro3["date"] = "2024-11-22";
    datos.append(registro3);

    // Día 2024-11-23
    QJsonObject registro4;
    registro4["pH"] = 7.0;
    registro4["Temperatura"] = 21.9;
    registro4["TDS"] = 340;
    registro4["date"] = "2024-11-23";
    datos.append(registro4);

    // Día 2024-11-24
    QJsonObject registro5;
    registro5["pH"] = 6.85;
    registro5["Temperatura"] = 21.6;
    registro5["TDS"] = 330;
    registro5["date"] = "2024-11-24";
    datos.append(registro5);

    // Día 2024-11-25
    QJsonObject registro6;
    registro6["pH"] = 6.95;
    registro6["Temperatura"] = 21.7;
    registro6["TDS"] = 325;
    registro6["date"] = "2024-11-25";
    datos.append(registro6);

    // Día 2024-11-26
    QJsonObject registro7;
    registro7["pH"] = 7.1;
    registro7["Temperatura"] = 22.0;
    registro7["TDS"] = 340;
    registro7["date"] = "2024-11-26";
    datos.append(registro7);

    // Día 2024-11-27
    QJsonObject registro8;
    registro8["pH"] = 7.2;
    registro8["Temperatura"] = 22.2;
    registro8["TDS"] = 345;
    registro8["date"] = "2024-11-27";
    datos.append(registro8);

    // Día 2024-11-28
    QJsonObject registro9;
    registro9["pH"] = 7.15;
    registro9["Temperatura"] = 22.3;
    registro9["TDS"] = 330;
    registro9["date"] = "2024-11-28";
    datos.append(registro9);

    // Día 2024-11-29
    QJsonObject registro10;
    registro10["pH"] = 7.3;
    registro10["Temperatura"] = 22.4;
    registro10["TDS"] = 335;
    registro10["date"] = "2024-11-29";
    datos.append(registro10);

    // Día 2024-11-30
    QJsonObject registro11;
    registro11["pH"] = 7.35;
    registro11["Temperatura"] = 22.5;
    registro11["TDS"] = 340;
    registro11["date"] = "2024-11-30";
    datos.append(registro11);

    // Día 2024-12-01
    QJsonObject registro12;
    registro12["pH"] = 7.4;
    registro12["Temperatura"] = 22.6;
    registro12["TDS"] = 350;
    registro12["date"] = "2024-12-01";
    datos.append(registro12);

    // Día 2024-12-02
    QJsonObject registro13;
    registro13["pH"] = 7.45;
    registro13["Temperatura"] = 22.7;
    registro13["TDS"] = 355;
    registro13["date"] = "2024-12-02";
    datos.append(registro13);


    return datos;
}

// Implementa la función fetchDataFromFirebase aquí si la necesitas
void historico::fetchDataFromFirebase()
{
    // Lógica de fetch de datos de Firebase aquí
}

void historico::generarGrafico()
{
    qDebug() << "Generación de gráficos...";

    // Crear un conjunto de datos de prueba
    QVector<QJsonObject> datos = obtenerDatosDePrueba();
    updateData(datos);
}
