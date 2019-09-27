#pragma once
#include "IPlot.h"

#include "ui_QPlot.h"

class QPlotWidget final : public QMainWindow
{
	Q_OBJECT

public:
	QPlotWidget(const Plotter::PlotParams &plotParams, QWidget *parent = Q_NULLPTR);
	
private:

	static void			ComputeArgInterval(const std::vector<double>& x, double &x0, double &x1);
		
	Ui::QPlotClass	m_ui;
};
