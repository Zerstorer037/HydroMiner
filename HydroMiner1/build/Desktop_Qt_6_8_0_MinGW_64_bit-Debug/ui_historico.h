/********************************************************************************
** Form generated from reading UI file 'historico.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTORICO_H
#define UI_HISTORICO_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_historico
{
public:
    QWidget *centralwidget;
    QPushButton *Bactual;
    QLabel *l;
    QPushButton *Bmenu;
    QLabel *label_4;
    QPushButton *Bvolver;
    QPushButton *Bhistorico;
    QPushButton *Balarma;
    QLabel *label;
    QLabel *label_5;
    QLabel *label_2;
    QDateEdit *dateEdit;
    QDateEdit *hasta;
    QLabel *label_3;
    QLabel *label_6;
    QLabel *label_7;
    QWidget *graficoPH;
    QWidget *graficoTEMP;
    QWidget *graficoTDS;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *historico)
    {
        if (historico->objectName().isEmpty())
            historico->setObjectName("historico");
        historico->resize(1200, 731);
        centralwidget = new QWidget(historico);
        centralwidget->setObjectName("centralwidget");
        Bactual = new QPushButton(centralwidget);
        Bactual->setObjectName("Bactual");
        Bactual->setGeometry(QRect(30, 160, 61, 61));
        Bactual->setMouseTracking(true);
        Bactual->setTabletTracking(true);
        Bactual->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(255, 255, 255, 0);\n"
"    border: 2px rgba(255, 255, 255, 0) ;\n"
"    font-size: 16px;\n"
"    border-radius: 10px;\n"
"}\n"
"QPushButton:hover {\n"
"/* Color al pasar el mouse */\n"
"	background-color: rgb(252, 209, 128);\n"
"\n"
"}"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/recursos/ActualI.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Bactual->setIcon(icon);
        Bactual->setIconSize(QSize(32, 32));
        l = new QLabel(centralwidget);
        l->setObjectName("l");
        l->setGeometry(QRect(0, 10, 1191, 731));
        l->setStyleSheet(QString::fromUtf8("background-color: rgb(249, 248, 245);"));
        Bmenu = new QPushButton(centralwidget);
        Bmenu->setObjectName("Bmenu");
        Bmenu->setGeometry(QRect(30, 70, 61, 61));
        Bmenu->setMouseTracking(true);
        Bmenu->setTabletTracking(false);
        Bmenu->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(255, 255, 255, 0);\n"
"    border: 2px rgba(255, 255, 255, 0) ;\n"
"    font-size: 16px;\n"
"    border-radius: 10px;\n"
"}\n"
"QPushButton:hover {\n"
"    background-color: rgb(252, 209, 128); /* Color al pasar el mouse */\n"
"}\n"
""));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/recursos/menuI.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Bmenu->setIcon(icon1);
        Bmenu->setIconSize(QSize(32, 32));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 101, 731));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 110, 158);"));
        Bvolver = new QPushButton(centralwidget);
        Bvolver->setObjectName("Bvolver");
        Bvolver->setGeometry(QRect(30, 645, 61, 61));
        Bvolver->setMouseTracking(true);
        Bvolver->setTabletTracking(true);
        Bvolver->setAutoFillBackground(false);
        Bvolver->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(255, 255, 255, 0);\n"
"    border: 2px rgba(255, 255, 255, 0) ;\n"
"    font-size: 16px;\n"
"    border-radius: 10px;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(252, 209, 128); /* Color al pasar el mouse */\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/recursos/flecha-pequena-izquierda (1).png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        icon2.addFile(QString::fromUtf8(":/recursos/flecha-pequena-izquierda (2).png"), QSize(), QIcon::Mode::Selected, QIcon::State::Off);
        Bvolver->setIcon(icon2);
        Bvolver->setIconSize(QSize(32, 32));
        Bhistorico = new QPushButton(centralwidget);
        Bhistorico->setObjectName("Bhistorico");
        Bhistorico->setGeometry(QRect(30, 250, 61, 61));
        Bhistorico->setMouseTracking(true);
        Bhistorico->setTabletTracking(true);
        Bhistorico->setAutoFillBackground(false);
        Bhistorico->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(255, 255, 255, 0);\n"
"    border: 2px rgba(255, 255, 255, 0) ;\n"
"    font-size: 16px;\n"
"    border-radius: 10px;\n"
"}\n"
"QPushButton:hover {\n"
"    border: 4px solid #fcd180; /* Borde color #fcd180 al pasar el mouse */\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/recursos/grafico-histograma (2).png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Bhistorico->setIcon(icon3);
        Bhistorico->setIconSize(QSize(32, 32));
        Balarma = new QPushButton(centralwidget);
        Balarma->setObjectName("Balarma");
        Balarma->setGeometry(QRect(30, 340, 61, 61));
        Balarma->setMouseTracking(true);
        Balarma->setTabletTracking(true);
        Balarma->setAutoFillBackground(false);
        Balarma->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-color: rgba(255, 255, 255, 0);\n"
"    border: 2px rgba(255, 255, 255, 0) ;\n"
"    font-size: 16px;\n"
"    border-radius: 10px;\n"
"}\n"
"QPushButton:hover {\n"
"	background-color: rgb(252, 209, 128); /* Color al pasar el mouse */\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/recursos/alertaI.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Balarma->setIcon(icon4);
        Balarma->setIconSize(QSize(32, 32));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(100, 10, 151, 41));
        QPalette palette;
        QBrush brush(QColor(193, 232, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(193, 232, 255, 0));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(193, 232, 255, 128));
        brush2.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        label->setPalette(palette);
        QFont font;
        font.setFamilies({QString::fromUtf8("Arial Black")});
        font.setPointSize(18);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgba(193, 232, 255, 0);"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(90, 0, 1111, 51));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 110, 158);"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(140, 90, 311, 161));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush3(QColor(252, 209, 128, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush3);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush3);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush3);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        label_2->setPalette(palette1);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(252, 209, 128);\n"
"border-radius: 10px"));
        dateEdit = new QDateEdit(centralwidget);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(210, 160, 110, 22));
        hasta = new QDateEdit(centralwidget);
        hasta->setObjectName("hasta");
        hasta->setGeometry(QRect(210, 210, 110, 22));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(150, 160, 51, 21));
        QFont font1;
        font1.setBold(true);
        label_3->setFont(font1);
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(150, 100, 241, 41));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush2);
#endif
        label_6->setPalette(palette2);
        label_6->setFont(font);
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgba(193, 232, 255, 0);"));
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(150, 210, 51, 21));
        label_7->setFont(font1);
        graficoPH = new QWidget(centralwidget);
        graficoPH->setObjectName("graficoPH");
        graficoPH->setGeometry(QRect(110, 310, 351, 261));
        graficoTEMP = new QWidget(centralwidget);
        graficoTEMP->setObjectName("graficoTEMP");
        graficoTEMP->setGeometry(QRect(480, 310, 341, 261));
        graficoTDS = new QWidget(centralwidget);
        graficoTDS->setObjectName("graficoTDS");
        graficoTDS->setGeometry(QRect(840, 310, 341, 261));
        historico->setCentralWidget(centralwidget);
        l->raise();
        label_4->raise();
        Balarma->raise();
        label_5->raise();
        label->raise();
        Bvolver->raise();
        Bmenu->raise();
        Bactual->raise();
        Bhistorico->raise();
        label_2->raise();
        dateEdit->raise();
        hasta->raise();
        label_3->raise();
        label_6->raise();
        label_7->raise();
        graficoPH->raise();
        graficoTEMP->raise();
        graficoTDS->raise();
        menubar = new QMenuBar(historico);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 21));
        historico->setMenuBar(menubar);
        statusbar = new QStatusBar(historico);
        statusbar->setObjectName("statusbar");
        historico->setStatusBar(statusbar);

        retranslateUi(historico);

        QMetaObject::connectSlotsByName(historico);
    } // setupUi

    void retranslateUi(QMainWindow *historico)
    {
        historico->setWindowTitle(QCoreApplication::translate("historico", "MainWindow", nullptr));
        Bactual->setText(QString());
        l->setText(QString());
        Bmenu->setText(QString());
        label_4->setText(QString());
        Bvolver->setText(QString());
        Bhistorico->setText(QString());
        Balarma->setText(QString());
        label->setText(QCoreApplication::translate("historico", "Fuente 1", nullptr));
        label_5->setText(QString());
        label_2->setText(QString());
#if QT_CONFIG(accessibility)
        dateEdit->setAccessibleName(QCoreApplication::translate("historico", "cdsm", nullptr));
#endif // QT_CONFIG(accessibility)
        label_3->setText(QCoreApplication::translate("historico", "Desde:", nullptr));
        label_6->setText(QCoreApplication::translate("historico", "Generar gr\303\241ficos", nullptr));
        label_7->setText(QCoreApplication::translate("historico", "Hasta:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class historico: public Ui_historico {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTORICO_H
