/********************************************************************************
** Form generated from reading UI file 'QPlot.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QPLOT_H
#define UI_QPLOT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_QPlotClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QCustomPlot *widget;
    QMenuBar *menuBar;
    QMenu *menuQPlot;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QPlotClass)
    {
        if (QPlotClass->objectName().isEmpty())
            QPlotClass->setObjectName(QString::fromUtf8("QPlotClass"));
        QPlotClass->resize(1069, 783);
        QPlotClass->setMaximumSize(QSize(1069, 783));
        centralWidget = new QWidget(QPlotClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setMaximumSize(QSize(1069, 718));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QCustomPlot(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setEnabled(true);
        widget->setMaximumSize(QSize(1047, 696));

        gridLayout->addWidget(widget, 0, 0, 1, 1);

        QPlotClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QPlotClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1069, 26));
        menuQPlot = new QMenu(menuBar);
        menuQPlot->setObjectName(QString::fromUtf8("menuQPlot"));
        QPlotClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QPlotClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QPlotClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QPlotClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        QPlotClass->setStatusBar(statusBar);

        menuBar->addAction(menuQPlot->menuAction());

        retranslateUi(QPlotClass);

        QMetaObject::connectSlotsByName(QPlotClass);
    } // setupUi

    void retranslateUi(QMainWindow *QPlotClass)
    {
        QPlotClass->setWindowTitle(QApplication::translate("QPlotClass", "QPlot", nullptr));
        menuQPlot->setTitle(QApplication::translate("QPlotClass", "QPlot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QPlotClass: public Ui_QPlotClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QPLOT_H
