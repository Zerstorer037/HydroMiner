#include "actual.h"
#include "ui_actual.h"
#include <QNetworkAccessManager>  // Esta librería proporciona clases para gestionar las solicitudes de red (HTTP, etc.)
#include <QNetworkRequest>  // Define una clase que contiene los detalles de una solicitud HTTP, como la URL, el tipo de solicitud (GET, POST, etc.)
#include <QNetworkReply>  // Representa la respuesta de una solicitud de red. Se utiliza para leer los datos devueltos por la solicitud HTTP y gestionar el estado de la respuesta
#include <QJsonDocument>  // Esta clase permite trabajar con documentos JSON.
#include <QJsonObject>  // Representa un objeto JSON.
#include <QJsonArray>  // Representa una lista de objetos JSON.
#include <QDebug>  // Esta librería proporciona funciones para depuración. Se utiliza comúnmente para imprimir mensajes de depuración en la consola de Qt y seguir el flujo de ejecución o los valores de las variables.

actual::actual(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::actual)  // Inicialización de la interfaz gráfica
{
    ui->setupUi(this);  // Cargar la interfaz de usuario desde el archivo .ui
    ui->date_actual->setDisplayFormat("yyyy-MM-dd");  // Formato de fecha (día-mes-año)
    setupConnections();  // Configura las conexiones de señales y slots
}

actual::~actual()
{
    delete ui;  // Liberar la memoria ocupada por la interfaz de usuario
}

// Configuración de las conexiones entre señales y slots (eventos)
void actual::setupConnections()
{
    // Conectar los botones a sus respectivas funciones
    connect(ui->Balarma, &QPushButton::clicked, this, [this]() { emit goToAlarma(); });
    connect(ui->Bhistorico, &QPushButton::clicked, this, [this]() { emit goToHistorico(); });
    connect(ui->Bmenu, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->Bvolver, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->Button_generar, &QPushButton::clicked, this, &actual::fetchDataFromFirebase);  // Conectar al botón de generar
}

// Función que obtiene los datos desde Firebase
void actual::fetchDataFromFirebase()
{
    QUrl url("https://aguagod-beaac-default-rtdb.firebaseio.com/.json");  // URL de la base de datos Firebase
    QNetworkRequest request(url);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);  // Crear el gestor de red
    QNetworkReply *reply = manager->get(request);  // Realizar una solicitud GET a Firebase

    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();  // Obtener la respuesta de la base de datos
            qDebug() << "Respuesta de Firebase:" << response;

            // Procesar los datos JSON recibidos
            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject rootObj = jsonDoc.object();  // Extraer el objeto raíz del JSON

                // Definir vectores para almacenar los datos
                QVector<double> pH;
                QVector<double> TDS;
                QVector<double> temperatura;
                QVector<QString> pHClasificacion;
                QVector<QString> TDSClasificacion;
                QVector<QString> TempClasificacion;

                QDate fechaSeleccionada = ui->date_actual->date();  // Obtener la fecha seleccionada desde la interfaz
                if (!fechaSeleccionada.isValid()) {
                    qDebug() << "Por favor, ingresa una fecha válida.";
                    return;  // Salir si la fecha no es válida
                }

                qDebug() << "Fecha seleccionada: " << fechaSeleccionada.toString("yyyy-MM-dd");  // Imprimir la fecha seleccionada

                // Recorrer los registros de Firebase
                for (const QString &key : rootObj.keys()) {
                    QJsonObject registro = rootObj[key].toObject();
                    if (registro.contains("pH") && registro["pH"].isDouble() &&
                        registro.contains("TDS") && registro["TDS"].isDouble() &&
                        registro.contains("Temperatura") && registro["Temperatura"].isDouble() &&
                        registro.contains("date") && registro["date"].isString()) {

                        // Filtrar los datos por fecha
                        QString fechaFirebase = registro["date"].toString();
                        QDate fechaFirebaseConvertida = QDate::fromString(fechaFirebase, "yyyy-MM-dd");

                        if (fechaSeleccionada == fechaFirebaseConvertida) {
                            // Extraer y clasificar los datos
                            double ph = registro["pH"].toDouble();
                            double tds = registro["TDS"].toDouble();
                            double temp = registro["Temperatura"].toDouble();

                            pH.append(ph);  // Agregar valor de pH
                            TDS.append(tds);  // Agregar valor de TDS
                            temperatura.append(temp);  // Agregar valor de temperatura

                            // Clasificar los valores obtenidos
                            pHClasificacion.append(clasificarPh(ph));
                            TDSClasificacion.append(clasificarTds(tds));
                            TempClasificacion.append(clasificarTemperature(temp));
                        }
                    }
                }

                // Mostrar los resultados en la interfaz si hay datos
                if (!pH.isEmpty()) {
                    actualizarLabel(ui->label_PH, pHClasificacion[0], "pH");
                    actualizarLabel(ui->label_TDS, TDSClasificacion[0], "TDS");
                    actualizarLabel(ui->label_TEMP, TempClasificacion[0], "Temperatura");
                }
            }
        }
        reply->deleteLater();  // Eliminar el objeto reply cuando haya terminado
    });
}

// Actualiza el texto y el color del label según la clasificación
void actual::actualizarLabel(QLabel* label, const QString& clasificacion, const QString& tipo)
{
    label->setText(tipo + ": " + clasificacion);  // Mostrar la clasificación

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

// Función para clasificar el pH
QString actual::clasificarPh(double ph)
{
    if (ph < 6.5) return "Ácido";
    if (ph >= 6.5 && ph <= 8.5) return "Neutro";
    return "Alcalino";
}

// Función para clasificar el TDS (Total Dissolved Solids)
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

// Función para clasificar la temperatura
QString actual::clasificarTemperature(double temp)
{
    if (temp < 0) return "Congelante";
    if (temp < 10) return "Frío";
    if (temp < 25) return "Moderado";
    if (temp < 35) return "Cálido";
    return "Caliente";
}
