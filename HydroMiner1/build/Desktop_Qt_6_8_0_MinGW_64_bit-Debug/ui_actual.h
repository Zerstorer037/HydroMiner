/********************************************************************************
** Form generated from reading UI file 'actual.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACTUAL_H
#define UI_ACTUAL_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_actual
{
public:
    QWidget *centralwidget;
    QPushButton *Balarma;
    QPushButton *Bhistorico;
    QPushButton *Bvolver;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *Bmenu;
    QLabel *label;
    QLabel *label_3;
    QPushButton *Bactual;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *actual)
    {
        if (actual->objectName().isEmpty())
            actual->setObjectName("actual");
        actual->resize(1200, 731);
        centralwidget = new QWidget(actual);
        centralwidget->setObjectName("centralwidget");
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
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/recursos/alertaI.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Balarma->setIcon(icon);
        Balarma->setIconSize(QSize(32, 32));
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
"    background-color: rgb(252, 209, 128); /* Color al pasar el mouse */\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/recursos/grficoI.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Bhistorico->setIcon(icon1);
        Bhistorico->setIconSize(QSize(32, 32));
        Bvolver = new QPushButton(centralwidget);
        Bvolver->setObjectName("Bvolver");
        Bvolver->setGeometry(QRect(30, 627, 61, 61));
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
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 101, 711));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 110, 158);"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(90, 0, 1111, 51));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 110, 158);"));
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
"/* Color al pasar el mouse */\n"
"	background-color: rgb(252, 209, 128);\n"
"\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/recursos/menuI.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Bmenu->setIcon(icon3);
        Bmenu->setIconSize(QSize(32, 32));
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
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 0, 1191, 741));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(249, 248, 245);"));
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
"    border: 4px solid #fcd180; /* Borde color #fcd180 al pasar el mouse */\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/recursos/rapido-en-el-tiempo (2).png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Bactual->setIcon(icon4);
        Bactual->setIconSize(QSize(32, 32));
        actual->setCentralWidget(centralwidget);
        label_3->raise();
        label_4->raise();
        label_5->raise();
        Bmenu->raise();
        label->raise();
        Bactual->raise();
        Balarma->raise();
        Bhistorico->raise();
        Bvolver->raise();
        menubar = new QMenuBar(actual);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 22));
        actual->setMenuBar(menubar);
        statusbar = new QStatusBar(actual);
        statusbar->setObjectName("statusbar");
        actual->setStatusBar(statusbar);

        retranslateUi(actual);

        QMetaObject::connectSlotsByName(actual);
    } // setupUi

    void retranslateUi(QMainWindow *actual)
    {
        actual->setWindowTitle(QCoreApplication::translate("actual", "MainWindow", nullptr));
        Balarma->setText(QString());
        Bhistorico->setText(QString());
        Bvolver->setText(QString());
        label_4->setText(QString());
        label_5->setText(QString());
        Bmenu->setText(QString());
        label->setText(QCoreApplication::translate("actual", "Fuente 1", nullptr));
        label_3->setText(QString());
        Bactual->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class actual: public Ui_actual {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACTUAL_H