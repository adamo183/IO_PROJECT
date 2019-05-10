/********************************************************************************
** Form generated from reading UI file 'main_win.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WIN_H
#define UI_MAIN_WIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main_winClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QScrollArea *main_scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *main_winClass)
    {
        if (main_winClass->objectName().isEmpty())
            main_winClass->setObjectName(QString::fromUtf8("main_winClass"));
        main_winClass->resize(600, 400);
        centralWidget = new QWidget(main_winClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        main_scrollArea = new QScrollArea(centralWidget);
        main_scrollArea->setObjectName(QString::fromUtf8("main_scrollArea"));
        main_scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 580, 327));
        main_scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(main_scrollArea, 0, 0, 1, 1);

        main_winClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(main_winClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        main_winClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(main_winClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        main_winClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(main_winClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        main_winClass->setStatusBar(statusBar);

        retranslateUi(main_winClass);

        QMetaObject::connectSlotsByName(main_winClass);
    } // setupUi

    void retranslateUi(QMainWindow *main_winClass)
    {
        main_winClass->setWindowTitle(QApplication::translate("main_winClass", "main_win", nullptr));
    } // retranslateUi

};

namespace Ui {
    class main_winClass: public Ui_main_winClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WIN_H
