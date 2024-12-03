#include "alarma.h"
#include "ui_alarma.h"
#include <QNetworkAccessManager>  // Esta librería proporciona clases para gestionar las solicitudes de red (HTTP, etc.)
#include <QNetworkRequest>  // Define una clase que contiene los detalles de una solicitud HTTP, como la URL, el tipo de solicitud (GET, POST, etc.)
#include <QNetworkReply>  // Representa la respuesta de una solicitud de red. Se utiliza para leer los datos devueltos por la solicitud HTTP y gestionar el estado de la respuesta
#include <QJsonDocument>  // Esta clase permite trabajar con documentos JSON.
#include <QJsonObject>  // Representa un objeto JSON.
#include <QJsonArray>  // Representa una lista de objetos JSON.
#include <QDebug>  // Esta librería proporciona funciones para depuración. Se utiliza comúnmente para imprimir mensajes de depuración en la consola de Qt y seguir el flujo de ejecución o los valores de las variables.


alarma::alarma(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::alarma)
{
    ui->setupUi(this);  // Inicializa la interfaz de usuario desde el archivo .ui
    ui->date_alarma->setDisplayFormat("yyyy-MM-dd");  // Configura el formato de la fecha
    setupConnections();  // Configura las conexiones entre señales y slots
}

alarma::~alarma()
{
    delete ui;  // Libera la memoria ocupada por la interfaz de usuario
}

// Configuración de las conexiones de los botones
void alarma::setupConnections()
{
    // Conectar botones a las acciones correspondientes
    connect(ui->Bactual, &QPushButton::clicked, this, [this]() { emit goToActual(); });
    connect(ui->Bhistorico, &QPushButton::clicked, this, [this]() { emit goToHistorico(); });
    connect(ui->Bmenu, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->Bvolver, &QPushButton::clicked, this, [this]() { emit goToMenu(); });
    connect(ui->Button_alarma, &QPushButton::clicked, this, &alarma::fetchDataFromFirebase); // Conectar al botón para obtener datos
}

// Función para obtener datos desde Firebase
void alarma::fetchDataFromFirebase()
{
    QUrl url("https://aguagod-beaac-default-rtdb.firebaseio.com/.json");  // URL de Firebase
    QNetworkRequest request(url);
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);  // Crear un administrador de red
    QNetworkReply *reply = manager->get(request);  // Realizar solicitud GET para obtener los datos

    // Conectar la señal de finalización de la solicitud
    connect(reply, &QNetworkReply::finished, [this, reply]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response = reply->readAll();  // Leer la respuesta de Firebase
            qDebug() << "Respuesta de Firebase:" << response;

            QJsonDocument jsonDoc = QJsonDocument::fromJson(response);  // Convertir la respuesta a JSON
            if (!jsonDoc.isNull() && jsonDoc.isObject()) {
                QJsonObject rootObj = jsonDoc.object();  // Obtenemos el objeto raíz del JSON

                QVector<double> pH;
                QVector<double> TDS;
                QVector<double> temperatura;
                QVector<QString> fechas;  // Almacenaremos las fechas para filtrarlas

                QDate fechaSeleccionada = ui->date_alarma->date();  // Obtener la fecha seleccionada en el QDateEdit
                if (!fechaSeleccionada.isValid()) {
                    qDebug() << "Por favor, ingresa una fecha válida.";
                    return;  // Salir si la fecha no es válida
                }

                // Convertir la fecha seleccionada a un string en formato "yyyy-MM-dd"
                QString fechaSeleccionadaStr = fechaSeleccionada.toString("yyyy-MM-dd");

                // Recorrer los registros de Firebase
                for (const QString &key : rootObj.keys()) {
                    QJsonObject registro = rootObj[key].toObject();  // Acceder al objeto del registro
                    if (registro.contains("pH") && registro["pH"].isDouble() &&
                        registro.contains("TDS") && registro["TDS"].isDouble() &&
                        registro.contains("Temperatura") && registro["Temperatura"].isDouble() &&
                        registro.contains("date") && registro["date"].isString()) {

                        QString fechaFirebase = registro["date"].toString();

                        // Filtramos los datos según la fecha
                        if (fechaSeleccionadaStr == fechaFirebase) {
                            pH.append(registro["pH"].toDouble());  // Agregar valor de pH
                            TDS.append(registro["TDS"].toDouble());  // Agregar valor de TDS
                            temperatura.append(registro["Temperatura"].toDouble());  // Agregar valor de temperatura
                        }
                    }
                }

                // Verificar si hay datos disponibles para la fecha seleccionada
                if (!pH.isEmpty()) {
                    // Llamar a la función que actualizará los datos de la alarma
                    actualizarAlarma(pH, TDS, temperatura);
                } else {
                    qDebug() << "No hay datos disponibles para esta fecha.";
                }
            }
        }
        reply->deleteLater();  // Eliminar el objeto reply una vez que se haya completado
    });
}

// Función para actualizar la alarma con los datos filtrados
void alarma::actualizarAlarma(const QVector<double>& pH, const QVector<double>& TDS, const QVector<double>& temperatura) {
    QDate fechaSeleccionada = ui->date_alarma->date();  // Obtener la fecha seleccionada

    // Verificar que la fecha esté establecida
    if (!fechaSeleccionada.isValid()) {
        qDebug() << "Por favor, ingresa una fecha válida.";
        return;  // Salir si la fecha no es válida
    }

    qDebug() << "Fecha seleccionada: " << fechaSeleccionada.toString("yyyy-MM-dd");

    // Calcular desviación estándar y promedios de los datos
    double desviacionPH = calcularDesviacionEstandar(pH);
    double desviacionTDS = calcularDesviacionEstandar(TDS);
    double desviacionTemp = calcularDesviacionEstandar(temperatura);

    double promedioPH = calcularPromedio(pH);
    double promedioTDS = calcularPromedio(TDS);
    double promedioTemp = calcularPromedio(temperatura);

    // Filtrar los datos por fecha (en el código de ejemplo, no se hace, pero es algo que puedes implementar)
    QVector<double> pHFiltrado;
    QVector<double> TDSFiltrado;
    QVector<double> temperaturaFiltrada;

    // Clasificar los parámetros
    QString estadoPH = clasificarParametro(promedioPH, 6.0, 8.5);  // Clasificar el pH
    QString estadoTDS = clasificarParametro(promedioTDS, 0, 500);  // Clasificar el TDS
    QString estadoTemp = clasificarParametro(promedioTemp, 0, 40);  // Clasificar la temperatura

    // Actualizar los labels con los resultados
    actualizarLabel(ui->label_PH, estadoPH, desviacionPH, promedioPH, "pH");
    actualizarLabel(ui->label_TDS, estadoTDS, desviacionTDS, promedioTDS, "TDS");
    actualizarLabel(ui->label_TEMP, estadoTemp, desviacionTemp, promedioTemp, "Temperatura");
}

// Función para actualizar los labels con los resultados
void alarma::actualizarLabel(QLabel* label, const QString& estado, double desviacion, double promedio, const QString& tipo) {
    // Mostrar el estado, la desviación estándar y el promedio
    label->setText(tipo + ": " + estado + " | Desviación: " + QString::number(desviacion) + " | Promedio: " + QString::number(promedio));

    // Actualizar el color del label según el estado
    if (estado == "Seguro") {
        label->setStyleSheet("background-color: green; color: white;");
    } else if (estado == "Mejorable") {
        label->setStyleSheet("background-color: yellow; color: black;");
    } else if (estado == "Peligroso") {
        label->setStyleSheet("background-color: red; color: white;");
    }
}

// Función para calcular la desviación estándar de un conjunto de datos
double alarma::calcularDesviacionEstandar(const QVector<double>& datos)
{
    double suma = 0.0;
    double promedio = 0.0;
    for (double dato : datos) {
        suma += dato;
    }
    promedio = suma / datos.size();  // Calcular el promedio

    // Calcular la suma de los cuadrados de las diferencias
    double sumaCuadrados = 0.0;
    for (double dato : datos) {
        sumaCuadrados += pow(dato - promedio, 2);  // Sumar el cuadrado de la diferencia entre cada valor y el promedio
    }

    // Devolver la raíz cuadrada de la varianza (desviación estándar)
    return sqrt(sumaCuadrados / datos.size());
}

// Función para calcular el promedio de los datos
double alarma::calcularPromedio(const QVector<double>& datos)
{
    double suma = 0.0;
    for (double dato : datos) {
        suma += dato;
    }
    return suma / datos.size();  // Devolver el promedio
}

// Función para clasificar un parámetro según un rango dado
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
