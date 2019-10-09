#include "QPlot.h"
#include <iostream>

namespace Plotter
{

void QPlotInternal::SetParams(const PlotParams* params)
{
	m_qPlotParams = *params;
}

void QPlotInternal::Plot()
{
	int argc = 1;
	QApplication a(argc, nullptr);
	QPlotWidget w(m_qPlotParams);
	// use params
	w.show();
	a.exec();
}

QPlot::~QPlot()
{
	m_thread->quit();
	while (m_thread->isRunning()) /*wait*/;
	delete m_thread;
	delete m_qPlotInternal;
}

void QPlot::Plot(const Plotter::PlotParams* params)
{
	m_thread = new QThread;
	m_qPlotInternal = new QPlotInternal;
	m_qPlotInternal->SetParams(params);

	m_qPlotInternal->moveToThread(m_thread);

	connect(m_thread, SIGNAL(started()), m_qPlotInternal, SLOT(Plot()));

	m_thread->start();
}

}
