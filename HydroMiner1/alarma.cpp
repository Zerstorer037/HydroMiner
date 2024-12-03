#include "alarma.h"
#include "ui_alarma.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

alarma::alarma(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::alarma)
{
    ui->setupUi(this);
    ui->date_alarma->setDisplayFormat("yyyy-MM-dd");
    setupConnections();
}

alarma::~alarma()
{
    delete ui;
}

void alarma::setupConnections()
{
    connect(ui->Bactual, &QPushButton::clicked, this, [this]() { emit goToActual(); });
    connect(ui->Bhistorico, &QPushButton::clicked, this, [this]() { emit goToHistorico(); });
    connect(ui->Bmenu, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->Bvolver, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->Button_alarma, &QPushButton::clicked, this, &alarma::fetchDataFromFirebase); // Usamos fetchDataFromFirebase aquí
}

void alarma::fetchDataFromFirebase()
{
    QUrl url("https://aguagod-beaac-default-rtdb.firebaseio.com/.json");
    QNetworkRequest request(url);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();
            qDebug() << "Respuesta de Firebase:" << response;

            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject rootObj = jsonDoc.object();

                QVector<double> pH;
                QVector<double> TDS;
                QVector<double> temperatura;
                QVector<QString> fechas; // Para almacenar las fechas

                // Obtenemos la fecha seleccionada
                QDate fechaSeleccionada = ui->date_alarma->date();

                // Verificamos que la fecha esté correctamente establecida
                if (!fechaSeleccionada.isValid()) {
                    qDebug() << "Por favor, ingresa una fecha válida.";
                    return;
                }

                // Convertir la fecha seleccionada a un string en formato "yyyy-MM-dd"
                QString fechaSeleccionadaStr = fechaSeleccionada.toString("yyyy-MM-dd");

                // Recorrer todos los datos de Firebase y filtrar por fecha
                for (const QString &key : rootObj.keys()) {
                    QJsonObject registro = rootObj[key].toObject();
                    if (registro.contains("pH") && registro["pH"].isDouble() &&
                        registro.contains("TDS") && registro["TDS"].isDouble() &&
                        registro.contains("Temperatura") && registro["Temperatura"].isDouble() &&
                        registro.contains("date") && registro["date"].isString()) {

                        QString fechaFirebase = registro["date"].toString();

                        // Filtramos los datos según la fecha
                        if (fechaSeleccionadaStr == fechaFirebase) {
                            pH.append(registro["pH"].toDouble());
                            TDS.append(registro["TDS"].toDouble());
                            temperatura.append(registro["Temperatura"].toDouble());
                        }
                    }
                }

                // Ahora filtramos los datos y solo mostramos los correspondientes a la fecha seleccionada
                if (!pH.isEmpty()) {
                    // Llamar a la actualización de la alarma con los datos filtrados
                    actualizarAlarma(pH, TDS, temperatura);
                } else {
                    qDebug() << "No hay datos disponibles para esta fecha.";
                }
            }
        }
        reply->deleteLater();
    });
}

void alarma::actualizarAlarma(const QVector<double>& pH, const QVector<double>& TDS, const QVector<double>& temperatura) {
    QDate fechaSeleccionada = ui->date_alarma->date();  // Obtener solo la fecha sin hora

    // Verificar si la fecha está establecida
    if (!fechaSeleccionada.isValid()) {
        qDebug() << "Por favor, ingresa una fecha válida.";
        return;  // Salir si la fecha no es válida
    }

    qDebug() << "Fecha seleccionada: " << fechaSeleccionada.toString("yyyy-MM-dd"); // Verificar la fecha seleccionada

    // Procesamiento de datos, calculando desviaciones estándar y promedios
    double desviacionPH = calcularDesviacionEstandar(pH);
    double desviacionTDS = calcularDesviacionEstandar(TDS);
    double desviacionTemp = calcularDesviacionEstandar(temperatura);

    double promedioPH = calcularPromedio(pH);
    double promedioTDS = calcularPromedio(TDS);
    double promedioTemp = calcularPromedio(temperatura);

    // Ahora procesamos los datos de Firebase para filtrar por fecha
    QVector<double> pHFiltrado;
    QVector<double> TDSFiltrado;
    QVector<double> temperaturaFiltrada;

    for (int i = 0; i < pH.size(); ++i) {
        // Suponiendo que "fechas" de Firebase están en formato "yyyy-MM-dd"
        QString fechaFirebase = "2024-11-30";  // Aquí deberías obtener la fecha de Firebase para este índice
        QDate fechaFirebaseConvertida = QDate::fromString(fechaFirebase, "yyyy-MM-dd");

        if (fechaSeleccionada == fechaFirebaseConvertida) {
            pHFiltrado.append(pH[i]);
            TDSFiltrado.append(TDS[i]);
            temperaturaFiltrada.append(temperatura[i]);
        }
    }

    // Ahora que tenemos los datos filtrados, se clasifica cada parámetro
    QString estadoPH = clasificarParametro(promedioPH, 6.0, 8.5); // Rango ejemplo para pH
    QString estadoTDS = clasificarParametro(promedioTDS, 0, 500); // Rango ejemplo para TDS
    QString estadoTemp = clasificarParametro(promedioTemp, 0, 40); // Rango ejemplo para Temperatura

    // Actualización de los datos en los labels con los colores apropiados
    actualizarLabel(ui->label_PH, estadoPH, desviacionPH, promedioPH, "pH");
    actualizarLabel(ui->label_TDS, estadoTDS, desviacionTDS, promedioTDS, "TDS");
    actualizarLabel(ui->label_TEMP, estadoTemp, desviacionTemp, promedioTemp, "Temperatura");
}

void alarma::actualizarLabel(QLabel* label, const QString& estado, double desviacion, double promedio, const QString& tipo) {
    // Set the label text with the corresponding values
    label->setText(tipo + ": " + estado + " | Desviación: " + QString::number(desviacion) + " | Promedio: " + QString::number(promedio));

    // Update the color based on the status (Seguro, Mejorable, Peligroso)
    if (estado == "Seguro") {
        label->setStyleSheet("background-color: green; color: white;");
    } else if (estado == "Mejorable") {
        label->setStyleSheet("background-color: yellow; color: black;");
    } else if (estado == "Peligroso") {
        label->setStyleSheet("background-color: red; color: white;");
    }
}

double alarma::calcularDesviacionEstandar(const QVector<double>& datos)
{
    double suma = 0.0;
    double promedio = 0.0;
    for (double dato : datos) {
        suma += dato;
    }
    promedio = suma / datos.size();

    double sumaCuadrados = 0.0;
    for (double dato : datos) {
        sumaCuadrados += pow(dato - promedio, 2);
    }

    return sqrt(sumaCuadrados / datos.size());
}

double alarma::calcularPromedio(const QVector<double>& datos)
{
    double suma = 0.0;
    for (double dato : datos) {
        suma += dato;
    }
    return suma / datos.size();
}

QString alarma::clasificarParametro(double valor, double valorMinimo, double valorMaximo)
{
    if (valor < valorMinimo) {
        return "Peligroso"; // Color rojo
    } else if (valor > valorMaximo) {
        return "Peligroso"; // Color rojo
    } else if (valor < (valorMaximo - valorMinimo) / 2 + valorMinimo) {
        return "Mejorable"; // Color amarillo
    } else {
        return "Seguro"; // Color verde
    }
}
