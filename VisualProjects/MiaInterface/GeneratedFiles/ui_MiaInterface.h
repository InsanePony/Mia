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
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MiaInterfaceClass
{
public:
    QAction *actionNewNetwork;
    QAction *actionLoadNetwork;
    QAction *actionNewEntry;
    QWidget *centralWidget;
    QGraphicsView *digit;
    QSpinBox *digitSpinBox;
    QGraphicsView *miaResponse;
    QPushButton *askMiaButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MiaInterfaceClass)
    {
        if (MiaInterfaceClass->objectName().isEmpty())
            MiaInterfaceClass->setObjectName(QStringLiteral("MiaInterfaceClass"));
        MiaInterfaceClass->resize(1280, 720);
        actionNewNetwork = new QAction(MiaInterfaceClass);
        actionNewNetwork->setObjectName(QStringLiteral("actionNewNetwork"));
        actionLoadNetwork = new QAction(MiaInterfaceClass);
        actionLoadNetwork->setObjectName(QStringLiteral("actionLoadNetwork"));
        actionNewEntry = new QAction(MiaInterfaceClass);
        actionNewEntry->setObjectName(QStringLiteral("actionNewEntry"));
        centralWidget = new QWidget(MiaInterfaceClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        digit = new QGraphicsView(centralWidget);
        digit->setObjectName(QStringLiteral("digit"));
        digit->setGeometry(QRect(120, 80, 360, 360));
        digitSpinBox = new QSpinBox(centralWidget);
        digitSpinBox->setObjectName(QStringLiteral("digitSpinBox"));
        digitSpinBox->setGeometry(QRect(210, 460, 190, 40));
        digitSpinBox->setMaximum(70000);
        miaResponse = new QGraphicsView(centralWidget);
        miaResponse->setObjectName(QStringLiteral("miaResponse"));
        miaResponse->setGeometry(QRect(730, 80, 360, 360));
        askMiaButton = new QPushButton(centralWidget);
        askMiaButton->setObjectName(QStringLiteral("askMiaButton"));
        askMiaButton->setEnabled(false);
        askMiaButton->setGeometry(QRect(530, 460, 160, 50));
        MiaInterfaceClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MiaInterfaceClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1280, 26));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MiaInterfaceClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MiaInterfaceClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MiaInterfaceClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNewNetwork);
        menuFile->addAction(actionLoadNetwork);
        menuFile->addAction(actionNewEntry);

        retranslateUi(MiaInterfaceClass);

        QMetaObject::connectSlotsByName(MiaInterfaceClass);
    } // setupUi

    void retranslateUi(QMainWindow *MiaInterfaceClass)
    {
        MiaInterfaceClass->setWindowTitle(QApplication::translate("MiaInterfaceClass", "MiaInterface", Q_NULLPTR));
        actionNewNetwork->setText(QApplication::translate("MiaInterfaceClass", "New Network", Q_NULLPTR));
        actionLoadNetwork->setText(QApplication::translate("MiaInterfaceClass", "Load Network", Q_NULLPTR));
        actionNewEntry->setText(QApplication::translate("MiaInterfaceClass", "New Entry", Q_NULLPTR));
        askMiaButton->setText(QApplication::translate("MiaInterfaceClass", "What's this ?", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MiaInterfaceClass", "File", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MiaInterfaceClass: public Ui_MiaInterfaceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MIAINTERFACE_H
