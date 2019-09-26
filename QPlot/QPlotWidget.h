#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QPlot.h"

class QPlotWidget : public QMainWindow
{
	Q_OBJECT

public:
	QPlotWidget(QWidget *parent = Q_NULLPTR);

private:

	Ui::QPlotClass	m_ui;
};
