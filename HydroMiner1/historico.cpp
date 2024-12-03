#include "historico.h"
#include "ui_historico.h"
#include <QtCharts>  // Esta librería proporciona la funcionalidad necesaria para crear gráficos interactivos dentro de una aplicación Qt.
#include <QMessageBox>  // Esta clase se utiliza para crear y mostrar cuadros de mensaje en la interfaz gráfica.
#include <QNetworkAccessManager>  // Esta clase gestiona las solicitudes de red en una aplicación Qt.
#include <QNetworkRequest>  // Esta clase define una solicitud de red, especificando los detalles como la URL, los encabezados HTTP y los parámetros de la solicitud.
#include <QNetworkReply>  // Representa la respuesta a una solicitud de red.
#include <QJsonDocument>  // Esta clase maneja los documentos JSON en Qt.
#include <QJsonObject>  // Representa un objeto JSON en Qt, que se corresponde con un diccionario o mapa de clave-valor.
#include <QJsonArray>  // Representa un arreglo JSON en Qt, que se corresponde con un array de valores.

// Constructor y Destructor
historico::historico(QWidget *parent)
    : QMainWindow(parent)  // Constructor de la clase QMainWindow, que se llama al iniciar la ventana principal
    , ui(new Ui::historico)  // Inicialización de la interfaz de usuario
    , graficoPH(new QChart())  // Creación de un nuevo objeto para el gráfico de pH
    , graficoViewPH(new QChartView(graficoPH))  // Vista para el gráfico de pH
    , graficoTEMP(new QChart())  // Creación de un nuevo objeto para el gráfico de temperatura
    , graficoViewTEMP(new QChartView(graficoTEMP))  // Vista para el gráfico de temperatura
    , graficoTDS(new QChart())  // Creación de un nuevo objeto para el gráfico de TDS
    , graficoViewTDS(new QChartView(graficoTDS))  // Vista para el gráfico de TDS
    , seriePH(new QLineSeries())  // Serie de datos para pH
    , serieTEMP(new QLineSeries())  // Serie de datos para temperatura
    , serieTDS(new QLineSeries())  // Serie de datos para TDS
    , manager(new QNetworkAccessManager(this))  // Inicialización del manager de red para hacer solicitudes HTTP
{
    ui->setupUi(this);  // Configura la interfaz gráfica según el archivo .ui

    // Configuración inicial de widgets
    ui->desde->setDisplayFormat("yyyy-MM-dd");  // Configura el formato de la fecha para 'desde'
    ui->hasta->setDisplayFormat("yyyy-MM-dd");  // Configura el formato de la fecha para 'hasta'
    ui->desde->setDate(QDate::currentDate());  // Establece la fecha actual por defecto en 'desde'
    ui->hasta->setDate(QDate::currentDate());  // Establece la fecha actual por defecto en 'hasta'

    // Configuración de gráficos
    configurarGraficos();

    // Configuración de las conexiones entre los botones y las funciones correspondientes
    setupConnections();
}

// Destructor
historico::~historico()
{
    delete ui;  // Liberar memoria de la interfaz de usuario cuando el objeto sea destruido
}

// Función para obtener la fecha de inicio desde el QDateEdit 'desde' como QDateTime
QDateTime historico::obtenerFechaDesde()
{
    return ui->desde->dateTime();  // Devuelve la fecha y hora del QDateEdit 'desde'
}

// Función para obtener la fecha de fin desde el QDateEdit 'hasta' como QDateTime
QDateTime historico::obtenerFechaHasta()
{
    return ui->hasta->dateTime();  // Devuelve la fecha y hora del QDateEdit 'hasta'
}

// Función para configurar las conexiones de los botones de la interfaz de usuario
void historico::setupConnections() {
    connect(ui->Bactual, &QPushButton::clicked, this, [this]() { emit goToActual(); });  // Botón para ir a la vista actual
    connect(ui->Balarma, &QPushButton::clicked, this, [this]() { emit goToAlarma(); });  // Botón para ir a la vista de alarma
    connect(ui->Bmenu, &QPushButton::clicked, this, [this]() { emit goToMenu(); });  // Botón para ir al menú principal
    connect(ui->Bvolver, &QPushButton::clicked, this, [this]() { emit goToMenu(); });  // Botón para volver al menú
    connect(ui->GenerarButton, &QPushButton::clicked, this, &historico::generarGrafico);  // Botón para generar el gráfico
}

// Función para configurar los gráficos de pH, temperatura y TDS
void historico::configurarGraficos()
{
    // Configuración para el gráfico de pH
    graficoPH->addSeries(seriePH);  // Añadir la serie de pH al gráfico
    graficoPH->setTitle("pH del agua");  // Título del gráfico de pH
    graficoPH->createDefaultAxes();  // Crear ejes predeterminados para el gráfico
    graficoPH->axes(Qt::Horizontal).first()->setTitleText("Días");  // Título para el eje X (Días)
    graficoPH->axes(Qt::Vertical).first()->setTitleText("pH");  // Título para el eje Y (pH)

    QVBoxLayout *layoutPH = new QVBoxLayout(ui->graficoPH);  // Layout para el gráfico de pH
    layoutPH->addWidget(graficoViewPH);  // Añadir la vista del gráfico
    ui->graficoPH->setLayout(layoutPH);  // Configurar el layout del gráfico de pH

    // Configuración para el gráfico de temperatura
    graficoTEMP->addSeries(serieTEMP);  // Añadir la serie de temperatura al gráfico
    graficoTEMP->setTitle("Temperatura");  // Título del gráfico de temperatura
    graficoTEMP->createDefaultAxes();  // Crear ejes predeterminados para el gráfico
    graficoTEMP->axes(Qt::Horizontal).first()->setTitleText("Días");  // Título para el eje X (Días)
    graficoTEMP->axes(Qt::Vertical).first()->setTitleText("Temperatura (°C)");  // Título para el eje Y (Temperatura)

    QVBoxLayout *layoutTEMP = new QVBoxLayout(ui->graficoTEMP);  // Layout para el gráfico de temperatura
    layoutTEMP->addWidget(graficoViewTEMP);  // Añadir la vista del gráfico
    ui->graficoTEMP->setLayout(layoutTEMP);  // Configurar el layout del gráfico de temperatura

    // Configuración para el gráfico de TDS
    graficoTDS->addSeries(serieTDS);  // Añadir la serie de TDS al gráfico
    graficoTDS->setTitle("TDS");  // Título del gráfico de TDS
    graficoTDS->createDefaultAxes();  // Crear ejes predeterminados para el gráfico
    graficoTDS->axes(Qt::Horizontal).first()->setTitleText("Días");  // Título para el eje X (Días)
    graficoTDS->axes(Qt::Vertical).first()->setTitleText("TDS (ppm)");  // Título para el eje Y (TDS)

    QVBoxLayout *layoutTDS = new QVBoxLayout(ui->graficoTDS);  // Layout para el gráfico de TDS
    layoutTDS->addWidget(graficoViewTDS);  // Añadir la vista del gráfico
    ui->graficoTDS->setLayout(layoutTDS);  // Configurar el layout del gráfico de TDS
}

// Función para ajustar los ejes del gráfico según los valores de la serie
void historico::ajustarEjes(QLineSeries *serie, QChart *grafico)
{
    if (serie->count() == 0) {
        qDebug() << "No hay datos en la serie para ajustar ejes.";  // Si no hay datos, no hacer nada
        return;
    }

    // Encontrar el valor mínimo y máximo de los datos en la serie
    double minY = serie->at(0).y(), maxY = serie->at(0).y();
    for (int i = 1; i < serie->count(); ++i) {
        minY = std::min(minY, serie->at(i).y());  // Calcular el valor mínimo
        maxY = std::max(maxY, serie->at(i).y());  // Calcular el valor máximo
    }

    grafico->axes(Qt::Vertical).first()->setRange(minY, maxY);  // Ajustar el eje Y con los valores mínimo y máximo

    // Ajustar el eje X con la fecha y hora
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

// Función para actualizar los datos de las series y los gráficos
void historico::updateData(const QVector<QJsonObject> &datos)
{
    QDateTime fechaInicio = obtenerFechaDesde();
    QDateTime fechaFin = obtenerFechaHasta();

    // Calcula los días de diferencia entre las fechas de inicio y fin
    int diasDeDiferencia = fechaInicio.daysTo(fechaFin);
    qDebug() << "Días de diferencia entre las fechas: " << diasDeDiferencia;

    // Iterar sobre los datos recibidos
    for (const QJsonObject &registro : datos) {
        if (registro.contains("pH") && registro["pH"].isDouble() &&
            registro.contains("date") && registro["date"].isString()) {
            QDateTime fecha = QDateTime::fromString(registro["date"].toString(), "yyyy-MM-dd");
            double phValue = registro["pH"].toDouble();
            int diaDiferencia = fechaInicio.daysTo(fecha);  // Calcular la diferencia de días
            seriePH->append(diaDiferencia, phValue);  // Añadir los datos de pH
        }

        if (registro.contains("Temperatura") && registro["Temperatura"].isDouble() &&
            registro.contains("date") && registro["date"].isString()) {
            QDateTime fecha = QDateTime::fromString(registro["date"].toString(), "yyyy-MM-dd");
            double tempValue = registro["Temperatura"].toDouble();
            int diaDiferencia = fechaInicio.daysTo(fecha);  // Calcular la diferencia de días
            serieTEMP->append(diaDiferencia, tempValue);  // Añadir los datos de temperatura
        }

        if (registro.contains("TDS") && registro["TDS"].isDouble() &&
            registro.contains("date") && registro["date"].isString()) {
            QDateTime fecha = QDateTime::fromString(registro["date"].toString(), "yyyy-MM-dd");
            double tdsValue = registro["TDS"].toDouble();
            int diaDiferencia = fechaInicio.daysTo(fecha);  // Calcular la diferencia de días
            serieTDS->append(diaDiferencia, tdsValue);  // Añadir los datos de TDS
        }
    }

    // Ajustar los ejes de los gráficos después de agregar los datos
    ajustarEjesConDias(seriePH, graficoPH, diasDeDiferencia);
    ajustarEjesConDias(serieTEMP, graficoTEMP, diasDeDiferencia);
    ajustarEjesConDias(serieTDS, graficoTDS, diasDeDiferencia);
}

// Función para ajustar los ejes de los gráficos basados en la cantidad de días
void historico::ajustarEjesConDias(QLineSeries *serie, QChart *grafico, int dias)
{
    if (serie->count() == 0) {
        qDebug() << "No hay datos en la serie para ajustar ejes.";  // Si no hay datos, no hacer nada
        return;
    }

    double minY = serie->at(0).y(), maxY = serie->at(0).y();
    for (int i = 1; i < serie->count(); ++i) {
        minY = std::min(minY, serie->at(i).y());  // Calcular el valor mínimo
        maxY = std::max(maxY, serie->at(i).y());  // Calcular el valor máximo
    }

    grafico->axes(Qt::Vertical).first()->setRange(minY, maxY);  // Ajustar el eje Y con los valores mínimo y máximo

    if (auto *axisX = dynamic_cast<QValueAxis *>(grafico->axes(Qt::Horizontal).first())) {
        axisX->setRange(0, dias);  // Usar el valor de días para el eje X
        axisX->setTitleText("Días");  // Título del eje X
    }

    qDebug() << "Ejes ajustados: X (0, " << dias << ") y Y (" << minY << ", " << maxY << ")";
}

// Función que devuelve un conjunto de datos de prueba para ser graficados
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

// Función para generar gráficos con los datos obtenidos
void historico::generarGrafico()
{
    qDebug() << "Generación de gráficos...";

    // Crear un conjunto de datos de prueba y actualizar los gráficos
    QVector<QJsonObject> datos = obtenerDatosDePrueba();
    updateData(datos);
}
