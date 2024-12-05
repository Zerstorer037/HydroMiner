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
    connect(ui->Button_alarma, &QPushButton::clicked, this, &alarma::fetchDataFromFirebase);
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

                QVector<double> pH, TDS, temperatura;
                QVector<QString> fechas;

                QDate fechaSeleccionada = ui->date_alarma->date();
                if (!fechaSeleccionada.isValid()) {
                    qDebug() << "Por favor, ingresa una fecha válida.";
                    return;
                }

                QString fechaSeleccionadaStr = fechaSeleccionada.toString("yyyy-MM-dd");

                for (const QString &key : rootObj.keys()) {
                    QJsonObject registro = rootObj[key].toObject();
                    if (registro.contains("pH") && registro["pH"].isDouble() &&
                        registro.contains("TDS") && registro["TDS"].isDouble() &&
                        registro.contains("Temperatura") && registro["Temperatura"].isDouble() &&
                        registro.contains("date") && registro["date"].isString()) {

                        QString fechaFirebase = registro["date"].toString();

                        if (fechaSeleccionadaStr == fechaFirebase) {
                            pH.append(registro["pH"].toDouble());
                            TDS.append(registro["TDS"].toDouble());
                            temperatura.append(registro["Temperatura"].toDouble());
                        }
                    }
                }

                if (!pH.isEmpty()) {
                    actualizarAlarma(pH, TDS, temperatura);
                } else {
                    qDebug() << "No hay datos disponibles para esta fecha.";
                }
            }
        }
        reply->deleteLater();
    });
}

void alarma::actualizarAlarma(const QVector<double>& pH, const QVector<double>& TDS, const QVector<double>& temperatura)
{
    QDate fechaSeleccionada = ui->date_alarma->date();
    if (!fechaSeleccionada.isValid()) {
        qDebug() << "Por favor, ingresa una fecha válida.";
        return;
    }

    qDebug() << "Fecha seleccionada: " << fechaSeleccionada.toString("yyyy-MM-dd");

    double desviacionPH = calcularDesviacionEstandar(pH);
    double desviacionTDS = calcularDesviacionEstandar(TDS);
    double desviacionTemp = calcularDesviacionEstandar(temperatura);

    double promedioPH = calcularPromedio(pH);
    double promedioTDS = calcularPromedio(TDS);
    double promedioTemp = calcularPromedio(temperatura);

    double derivadaPH = calcularPrimeraDerivada(pH);
    double derivadaTDS = calcularPrimeraDerivada(TDS);
    double derivadaTemp = calcularPrimeraDerivada(temperatura);

    QString estadoPH = clasificarParametro(promedioPH, 6.0, 8.5);
    QString estadoTDS = clasificarParametro(promedioTDS, 0, 500);
    QString estadoTemp = clasificarParametro(promedioTemp, 0, 40);

    actualizarLabel(ui->label_PH, estadoPH, desviacionPH, promedioPH, "pH", derivadaPH);
    actualizarLabel(ui->label_TDS, estadoTDS, desviacionTDS, promedioTDS, "TDS", derivadaTDS);
    actualizarLabel(ui->label_TEMP, estadoTemp, desviacionTemp, promedioTemp, "Temperatura", derivadaTemp);
}

void alarma::actualizarLabel(QLabel* label, const QString& estado, double desviacion, double promedio, const QString& tipo, double derivada)
{
    label->setText(tipo + ": " + estado + " | Desviación: " + QString::number(desviacion) + " | Promedio: " + QString::number(promedio) + " | Derivada: " + QString::number(derivada));

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

double alarma::calcularPrimeraDerivada(const QVector<double>& datos)
{
    QVector<double> derivada;
    for (int i = 1; i < datos.size(); ++i) {
        double cambio = datos[i] - datos[i - 1];
        derivada.append(cambio);
    }

    // Promediar las derivadas para obtener la tasa de cambio promedio
    double sumaDerivada = 0.0;
    for (double d : derivada) {
        sumaDerivada += d;
    }
    return sumaDerivada / derivada.size();
}

QString alarma::clasificarParametro(double valor, double valorMinimo, double valorMaximo)
{
    if (valor < valorMinimo) {
        return "Peligroso";
    } else if (valor > valorMaximo) {
        return "Peligroso";
    } else if (valor < (valorMaximo - valorMinimo) / 2 + valorMinimo) {
        return "Mejorable";
    } else {
        return "Seguro";
    }
}
