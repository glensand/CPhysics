#pragma once
#include "qplotwidget.h"

#include <QThread>
#include <QObject>

struct QPlotParams
{
	QPlotParams() = default;
	virtual ~QPlotParams() = default;

	size_t	m_test{};
};

class QPlotInternal final : public QObject
{

	Q_OBJECT

public:
	~QPlotInternal() = default;
	QPlotInternal() = default;

			// Sets params to be used for graphic plotting
	void	SetParams(const QPlotParams &params);
	
public slots:
			// Plot the graphic using passed params
	void	Plot();

private:
	QPlotParams	m_qPlotParams;	// Used to specify plotting graphic
};

class QPlot final : public QObject
{

	Q_OBJECT

public:

	QPlot() = default;
	~QPlot() = default;

	void	Plot(const QPlotParams &params);

private:

	QThread*		m_thread;			//	Used to run qApp instace

	QPlotInternal*	m_qPlotInternal;	//	Instance of internal plotting class
};

