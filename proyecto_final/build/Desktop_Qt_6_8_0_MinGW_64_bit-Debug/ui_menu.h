/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

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

class Ui_Menu
{
public:
    QWidget *centralwidget;
    QPushButton *Balarma;
    QPushButton *Bmenu;
    QPushButton *registro;
    QPushButton *alarma;
    QLabel *label;
    QPushButton *Bhistorico;
    QLabel *label_3;
    QLabel *label_5;
    QPushButton *estado;
    QLabel *label_4;
    QPushButton *Bactual;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName("Menu");
        Menu->resize(1200, 731);
        centralwidget = new QWidget(Menu);
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
"    border: 4px solid #fcd180; /* Borde color #fcd180 al pasar el mouse */\n"
"}"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/recursos/hogar (3).png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Bmenu->setIcon(icon1);
        Bmenu->setIconSize(QSize(32, 32));
        registro = new QPushButton(centralwidget);
        registro->setObjectName("registro");
        registro->setGeometry(QRect(180, 240, 281, 111));
        QFont font;
        font.setFamilies({QString::fromUtf8("Segoe UI Black")});
        font.setPointSize(18);
        font.setBold(true);
        registro->setFont(font);
        registro->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	color: rgb(255, 255, 255);\n"
"	background-image: url(:/recursos/48854.jpg);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat;\n"
"    background-size: cover;\n"
"    border-radius: 10px; /* Bordes redondeados */\n"
"}\n"
"QPushButton:hover {\n"
"    border: 10px solid #fcd180; /* Borde color #fcd180 al pasar el mouse */\n"
"}"));
        alarma = new QPushButton(centralwidget);
        alarma->setObjectName("alarma");
        alarma->setGeometry(QRect(490, 240, 171, 111));
        alarma->setFont(font);
        alarma->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	color: rgb(255, 255, 255);\n"
"	background-image: url(:/recursos/48854.jpg);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat;\n"
"    background-size: cover;\n"
"    border-radius: 10px; /* Bordes redondeados */\n"
"}\n"
"QPushButton:hover {\n"
"    border: 10px solid #fcd180; /* Borde color #fcd180 al pasar el mouse */\n"
"}\n"
"\n"
""));
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
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Arial Black")});
        font1.setPointSize(18);
        font1.setBold(true);
        label->setFont(font1);
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"background-color: rgba(193, 232, 255, 0);"));
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
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/recursos/grficoI.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Bhistorico->setIcon(icon2);
        Bhistorico->setIconSize(QSize(32, 32));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 0, 1201, 731));
        label_3->setStyleSheet(QString::fromUtf8("background-color: rgb(249, 248, 245);"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(90, 0, 1121, 51));
        label_5->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 110, 158);"));
        estado = new QPushButton(centralwidget);
        estado->setObjectName("estado");
        estado->setGeometry(QRect(180, 90, 481, 111));
        QFont font2;
        font2.setPointSize(36);
        font2.setBold(true);
        estado->setFont(font2);
        estado->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	color: rgb(255, 255, 255);\n"
"	background-image: url(:/recursos/48854.jpg);\n"
"    background-position: center;\n"
"    background-repeat: no-repeat;\n"
"    background-size: cover;\n"
"    border-radius: 10px; /* Bordes redondeados */\n"
"}\n"
"QPushButton:hover {\n"
"    border: 10px solid #fcd180; /* Borde color #fcd180 al pasar el mouse */\n"
"}"));
        estado->setCheckable(true);
        estado->setAutoRepeat(false);
        estado->setAutoExclusive(true);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 0, 101, 731));
        label_4->setStyleSheet(QString::fromUtf8("background-color: rgb(59, 110, 158);"));
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
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/recursos/ActualI.png"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        Bactual->setIcon(icon3);
        Bactual->setIconSize(QSize(32, 32));
        Menu->setCentralWidget(centralwidget);
        label_3->raise();
        label_5->raise();
        estado->raise();
        label_4->raise();
        registro->raise();
        alarma->raise();
        Bmenu->raise();
        Bhistorico->raise();
        Balarma->raise();
        Bactual->raise();
        label->raise();
        menubar = new QMenuBar(Menu);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 22));
        Menu->setMenuBar(menubar);
        statusbar = new QStatusBar(Menu);
        statusbar->setObjectName("statusbar");
        Menu->setStatusBar(statusbar);

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QMainWindow *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "Menu", nullptr));
        Balarma->setText(QString());
        Bmenu->setText(QString());
        registro->setText(QCoreApplication::translate("Menu", "Registro Historico", nullptr));
        alarma->setText(QCoreApplication::translate("Menu", "Alertas", nullptr));
        label->setText(QCoreApplication::translate("Menu", "Fuente 1", nullptr));
        Bhistorico->setText(QString());
        label_3->setText(QString());
        label_5->setText(QString());
        estado->setText(QCoreApplication::translate("Menu", "Estado Actual", nullptr));
        label_4->setText(QString());
        Bactual->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
