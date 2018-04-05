/********************************************************************************
** Form generated from reading UI file 'MiaInterface.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MIAINTERFACE_H
#define UI_MIAINTERFACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiaInterfaceClass
{
public:
    QWidget *centralWidget;
    QGraphicsView *digit;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MiaInterfaceClass)
    {
        if (MiaInterfaceClass->objectName().isEmpty())
            MiaInterfaceClass->setObjectName(QStringLiteral("MiaInterfaceClass"));
        MiaInterfaceClass->resize(1280, 720);
        centralWidget = new QWidget(MiaInterfaceClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        digit = new QGraphicsView(centralWidget);
        digit->setObjectName(QStringLiteral("digit"));
        digit->setGeometry(QRect(120, 80, 360, 360));
        MiaInterfaceClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MiaInterfaceClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 26));
        MiaInterfaceClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MiaInterfaceClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MiaInterfaceClass->setStatusBar(statusBar);

        retranslateUi(MiaInterfaceClass);

        QMetaObject::connectSlotsByName(MiaInterfaceClass);
    } // setupUi

    void retranslateUi(QMainWindow *MiaInterfaceClass)
    {
        MiaInterfaceClass->setWindowTitle(QApplication::translate("MiaInterfaceClass", "MiaInterface", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MiaInterfaceClass: public Ui_MiaInterfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIAINTERFACE_H
