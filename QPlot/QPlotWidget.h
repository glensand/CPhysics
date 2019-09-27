#pragma once
//------------------------------------------------------------------------------
// QPlotWidget.h
// Plotting widget via QT
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
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
