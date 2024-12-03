#include "actual.h"
#include "ui_actual.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

actual::actual(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::actual)
{
    ui->setupUi(this);
    ui->date_actual->setDisplayFormat("yyyy-MM-dd");  // Formato de fecha
    setupConnections();
}

actual::~actual()
{
    delete ui;
}

void actual::setupConnections()
{
    connect(ui->Balarma, &QPushButton::clicked, this, [this]() { emit goToAlarma(); });
    connect(ui->Bhistorico, &QPushButton::clicked, this, [this]() { emit goToHistorico(); });
    connect(ui->Bmenu, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->Bvolver, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->Button_generar, &QPushButton::clicked, this, &actual::fetchDataFromFirebase);  // Conectar al botón de generar
}

void actual::fetchDataFromFirebase()
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
                QVector<QString> pHClasificacion;
                QVector<QString> TDSClasificacion;
                QVector<QString> TempClasificacion;

                QDate fechaSeleccionada = ui->date_actual->date();  // Obtener la fecha del QDateEdit
                if (!fechaSeleccionada.isValid()) {
                    qDebug() << "Por favor, ingresa una fecha válida.";
                    return;  // Salir si la fecha no es válida
                }

                qDebug() << "Fecha seleccionada: " << fechaSeleccionada.toString("yyyy-MM-dd"); // Verificar la fecha seleccionada

                for (const QString &key : rootObj.keys()) {
                    QJsonObject registro = rootObj[key].toObject();
                    if (registro.contains("pH") && registro["pH"].isDouble() &&
                        registro.contains("TDS") && registro["TDS"].isDouble() &&
                        registro.contains("Temperatura") && registro["Temperatura"].isDouble() &&
                        registro.contains("date") && registro["date"].isString()) {

                        // Filtrar por fecha
                        QString fechaFirebase = registro["date"].toString();
                        QDate fechaFirebaseConvertida = QDate::fromString(fechaFirebase, "yyyy-MM-dd");

                        if (fechaSeleccionada == fechaFirebaseConvertida) {
                            double ph = registro["pH"].toDouble();
                            double tds = registro["TDS"].toDouble();
                            double temp = registro["Temperatura"].toDouble();

                            // Clasificar y agregar los valores
                            pH.append(ph);
                            TDS.append(tds);
                            temperatura.append(temp);

                            // Clasificación de los valores
                            pHClasificacion.append(clasificarPh(ph));
                            TDSClasificacion.append(clasificarTds(tds));
                            TempClasificacion.append(clasificarTemperature(temp));
                        }
                    }
                }

                // Mostrar los resultados
                if (!pH.isEmpty()) {
                    actualizarLabel(ui->label_PH, pHClasificacion[0], "pH");
                    actualizarLabel(ui->label_TDS, TDSClasificacion[0], "TDS");
                    actualizarLabel(ui->label_TEMP, TempClasificacion[0], "Temperatura");
                }
            }
        }
        reply->deleteLater();
    });
}

void actual::actualizarLabel(QLabel* label, const QString& clasificacion, const QString& tipo)
{
    label->setText(tipo + ": " + clasificacion);

    // Asignar colores según la clasificación
    if (clasificacion == "Óptimo") {
        label->setStyleSheet("background-color: green; color: white;");
    } else if (clasificacion == "Aceptable") {
        label->setStyleSheet("background-color: yellow; color: black;");
    } else if (clasificacion == "Bastante Aceptable") {
        label->setStyleSheet("background-color: lightgreen; color: black;");
    } else if (clasificacion == "Moderado") {
        label->setStyleSheet("background-color: orange; color: black;");
    } else if (clasificacion == "Peligroso") {
        label->setStyleSheet("background-color: red; color: white;");
    } else if (clasificacion == "Neutro") {
        label->setStyleSheet("background-color: lightblue; color: black;");
    }
}

QString actual::clasificarPh(double ph)
{
    if (ph < 6.5) return "Ácido";
    if (ph >= 6.5 && ph <= 8.5) return "Neutro";
    return "Alcalino";
}

QString actual::clasificarTds(double tds)
{
    if (tds < 50) return "Inaceptable";
    if (tds < 200) return "Bueno";
    if (tds < 400) return "Aceptable";
    if (tds < 600) return "Bastante Aceptable";
    if (tds < 900) return "Menos Aceptable";
    if (tds < 1200) return "Poco Aceptable";
    return "Inaceptable";
}

QString actual::clasificarTemperature(double temp)
{
    if (temp < 0) return "Congelante";
    if (temp < 10) return "Frío";
    if (temp < 25) return "Moderado";
    if (temp < 35) return "Cálido";
    return "Caliente";
}
