#include "QPlotWidget.h"

QPlotWidget::QPlotWidget(const Plotter::PlotParams &plotParams, QWidget *parent)
	: QMainWindow(parent)
{
	m_ui.setupUi(this);

	m_ui.widget->clearGraphs();
	double y0 = 0, y1 = 0;
	double x0 = 0, x1 = 0;
	
	for (const auto& function : plotParams.m_functions)
	{
		static size_t i{ 0 };
		m_ui.widget->addGraph();

		m_ui.widget->graph(i)->setData(QVector<double>::fromStdVector(function.m_x), QVector<double>::fromStdVector(function.m_y));

		const QColor color = { function.m_color.m_r, function.m_color.m_g, function.m_color.m_b, function.m_color.m_a };
		m_ui.widget->graph(i)->setPen(color);

		// sets default graph style
		// TODO: add styles convertation
		m_ui.widget->graph(i)->setLineStyle(QCPGraph::lsLine);
		//m_ui.widget->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 4));

		ComputeArgInterval(function.m_x, x0, x1);
		ComputeArgInterval(function.m_y, y0, y1);
		
		++i;
	}

	m_ui.widget->xAxis->setLabel(plotParams.m_labels.m_arg.c_str());
	m_ui.widget->yAxis->setLabel(plotParams.m_labels.m_val.c_str());

	m_ui.widget->xAxis->setRange(x0, x1);
	m_ui.widget->yAxis->setRange(y0, y1);
	
	m_ui.widget->replot();
}

void QPlotWidget::ComputeArgInterval(const std::vector<double>& x, double& x0, double& x1)
{
	for(size_t i = 1; i < x.size(); ++i)
	{
		if (x[i] > x1)
			x1 = x[i];

		if (x[i] < x0)
			x0 = x[i];
	}
}

