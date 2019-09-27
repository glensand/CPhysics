#pragma once
//------------------------------------------------------------------------------
// QPlot.h
// QPlot classes
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 27.09.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#include "qplotwidget.h"

#include <QThread>
#include <QObject>

#include "IPlot.h"

namespace Plotter
{

class QPlotInternal final : public QObject
{

	Q_OBJECT

public:
	~QPlotInternal() = default;
	QPlotInternal() = default;

			// Sets params to be used for graphic plotting
	void	SetParams(const PlotParams* params);

public slots:
			// Plot the graphic using passed params
	void	Plot();

private:
	PlotParams	m_qPlotParams;	// Used to specify plotting graphic
};

class QPlot final : public QObject, IPlot
{

	Q_OBJECT

public:

	QPlot() = default;
	virtual ~QPlot();

	void	Plot(const PlotParams* params) override;

private:

	QThread*		m_thread;			//	Used to run qApp instace

	QPlotInternal*	m_qPlotInternal;	//	Instance of internal plotting class
};
}
