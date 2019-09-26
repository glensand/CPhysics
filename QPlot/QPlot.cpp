#include "QPlot.h"
#include <iostream>

void QPlotInternal::SetParams(const QPlotParams& params)
{
	m_qPlotParams = params;
}

void QPlotInternal::Plot()
{
	std::cout << m_qPlotParams.m_test;
	int argc = 1;
	QApplication a(argc, nullptr);
	QPlotWidget w;

	// use params
	w.show();
	a.exec();
}

void QPlot::Plot(const QPlotParams &params)
{
	m_thread = new QThread;
	m_qPlotInternal = new QPlotInternal;
	m_qPlotInternal->SetParams(params);
	
	m_qPlotInternal->moveToThread(m_thread);

	connect(m_thread, SIGNAL(started()), m_qPlotInternal, SLOT(Plot()));
	
	m_thread->start();
}
