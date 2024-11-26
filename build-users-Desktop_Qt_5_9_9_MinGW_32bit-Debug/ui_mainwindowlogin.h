/********************************************************************************
** Form generated from reading UI file 'mainwindowlogin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOWLOGIN_H
#define UI_MAINWINDOWLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowLogin
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QLabel *label;
    QLineEdit *username;
    QLabel *label_4;
    QPushButton *login;
    QLineEdit *password;
    QLabel *label_5;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_6;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindowLogin)
    {
        if (MainWindowLogin->objectName().isEmpty())
            MainWindowLogin->setObjectName(QStringLiteral("MainWindowLogin"));
        MainWindowLogin->resize(1733, 1159);
        MainWindowLogin->setStyleSheet(QStringLiteral("background-color:#F1F6FE;"));
        centralwidget = new QWidget(MainWindowLogin);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(340, 240, 1051, 591));
        groupBox->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(520, 90, 471, 391));
        label->setPixmap(QPixmap(QString::fromUtf8(":/img/img/waveitt.png")));
        label->setScaledContents(true);
        username = new QLineEdit(groupBox);
        username->setObjectName(QStringLiteral("username"));
        username->setGeometry(QRect(80, 210, 381, 51));
        username->setStyleSheet(QStringLiteral(""));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(80, 50, 429, 71));
        QPalette palette;
        QBrush brush(QColor(67, 127, 247, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(67, 127, 247, 128));
        brush2.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        QBrush brush3(QColor(67, 127, 247, 128));
        brush3.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush3);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush4(QColor(67, 127, 247, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
#endif
        label_4->setPalette(palette);
        QFont font;
        font.setFamily(QStringLiteral("Poppins"));
        font.setPointSize(28);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        label_4->setFont(font);
        label_4->setStyleSheet(QLatin1String("color: #437FF7;\n"
""));
        login = new QPushButton(groupBox);
        login->setObjectName(QStringLiteral("login"));
        login->setGeometry(QRect(80, 450, 171, 51));
        QFont font1;
        font1.setFamily(QStringLiteral("Poppins"));
        login->setFont(font1);
        login->setStyleSheet(QLatin1String("background-color:#437FF7;border-radius :10px; \n"
"color : #fff;\n"
""));
        password = new QLineEdit(groupBox);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(80, 330, 381, 51));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(80, 520, 171, 21));
        QFont font2;
        font2.setFamily(QStringLiteral("Poppins"));
        font2.setPointSize(9);
        font2.setUnderline(true);
        label_5->setFont(font2);
        label_5->setStyleSheet(QStringLiteral("color: #747474;"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 170, 181, 21));
        label_2->setStyleSheet(QStringLiteral("font : 10pt;"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(90, 290, 181, 21));
        label_3->setStyleSheet(QStringLiteral("font : 10pt;"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(-370, -30, 1991, 1311));
        label_6->setPixmap(QPixmap(QString::fromUtf8(":/img/bg.png")));
        MainWindowLogin->setCentralWidget(centralwidget);
        label_6->raise();
        groupBox->raise();
        menubar = new QMenuBar(MainWindowLogin);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1733, 26));
        MainWindowLogin->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowLogin);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindowLogin->setStatusBar(statusbar);

        retranslateUi(MainWindowLogin);

        QMetaObject::connectSlotsByName(MainWindowLogin);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowLogin)
    {
        MainWindowLogin->setWindowTitle(QApplication::translate("MainWindowLogin", "MainWindow", Q_NULLPTR));
        groupBox->setTitle(QString());
        label->setText(QString());
        label_4->setText(QApplication::translate("MainWindowLogin", "Login :", Q_NULLPTR));
        login->setText(QApplication::translate("MainWindowLogin", "LOGIN", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindowLogin", "forgot password?", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindowLogin", "Username :", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindowLogin", "Password :", Q_NULLPTR));
        label_6->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindowLogin: public Ui_MainWindowLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOWLOGIN_H
