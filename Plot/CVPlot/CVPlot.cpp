#include "CVPlot.h"

#include <opencv2/imgproc/imgproc_c.h>

namespace
{
const Plotter::FontProperties	DEFAULT_FONT_PROPERTIES;
const Plotter::AxisProperties	DEFAULT_AXIS_PROPERTIES;
}

namespace Plotter
{

//------------------------------------------------------------------------------
void CVPlot::AddGraph(const GraphParams* params)
{
	m_graphs.emplace_back(*params);
}
//------------------------------------------------------------------------------
void CVPlot::Release()
{
}
//------------------------------------------------------------------------------
void CVPlot::Show()
{
	Initialize();

	DrawAxis();

	DrawPlots();

	DrawLabels();

	cv::namedWindow(m_plotName, cv::WINDOW_AUTOSIZE);
	cv::imshow(m_plotName, m_plot);
	cv::waitKey(0);
}
//------------------------------------------------------------------------------
void CVPlot::Initialize()
{
	m_plot = cv::Mat(m_plotSize.height, m_plotSize.width, CV_8UC3, m_defaultBackgroundColor);
	
	// find maximum/minimum of axis
	for(const auto &graph : m_graphs)
	{
		std::for_each(graph.m_x.begin(), graph.m_x.end(),
			[this](const double x)
			{
				if (x < m_minX) m_minX = static_cast<float>(x);
				if (x > m_maxX) m_maxX = static_cast<float>(x);
			}
		);
		
		std::for_each(graph.m_y.begin(), graph.m_y.end(),
			[this](const double y)
			{
				if (y < m_minY) m_minY = static_cast<float>(y);
				if (y > m_maxY) m_maxY = static_cast<float>(y);
			}
		);
	}

	float range = m_maxY - m_minY;
	const float eps = 1e-9f;
	if (range <= eps)
	{
		range = 1.f;
		m_minY = m_maxY / 2;
		m_maxY = m_maxY * 3 / 2;
	}

	m_scaleX = static_cast<float>(m_plotSize.width - m_borderSize * 2) / (m_maxX - m_minX);
	m_scaleY = static_cast<float>(m_plotSize.height - m_borderSize * 2) / range;	
}
//------------------------------------------------------------------------------
void CVPlot::DrawAxis()
{
	// draw the horizontal and vertical axis
	// let x, y axis cross at zero if possible.
	float yRef = m_minY;
	if (m_maxX > .0 && m_minY <= .0) 
		yRef = .0;

	const int xAxisPos = m_plotSize.height - m_borderSize
	- cvRound((yRef - m_minY) * m_scaleY);

	// x axis
	cv::line(m_plot, { m_borderSize, xAxisPos },
		{ m_plotSize.width - m_borderSize, xAxisPos }, 
		DEFAULT_AXIS_PROPERTIES.m_color, DEFAULT_AXIS_PROPERTIES.m_thickness);

	// TODO:move y axis to (0; 0)
	// y axis
	cv::line(m_plot, { m_borderSize, m_plotSize.height - m_borderSize },
		{  m_borderSize, m_borderSize }, 
		DEFAULT_AXIS_PROPERTIES.m_color, DEFAULT_AXIS_PROPERTIES.m_thickness);

	// Write the scale of the y axis
	const int chw = 12, chh = 20;
	if ((m_maxY - yRef) > 0.05 * (m_maxY - m_minY))
		cv::putText(m_plot, std::to_string(m_maxY), cvPoint(m_borderSize / 5, m_borderSize - chh / 2),
			DEFAULT_FONT_PROPERTIES.m_type, DEFAULT_FONT_PROPERTIES.m_scale, DEFAULT_FONT_PROPERTIES.m_color);

	if ((yRef - m_minY) > 0.05 * (m_maxX - m_minY))
		cv::putText(m_plot, std::to_string(m_minY), cvPoint(m_borderSize / 5, m_plotSize.height - m_borderSize + chh),
			DEFAULT_FONT_PROPERTIES.m_type, DEFAULT_FONT_PROPERTIES.m_scale, DEFAULT_FONT_PROPERTIES.m_color);

	// x axis
	cv::putText(m_plot, std::to_string(yRef), cvPoint(m_borderSize / 5, xAxisPos + chh / 2),
		DEFAULT_FONT_PROPERTIES.m_type, DEFAULT_FONT_PROPERTIES.m_scale, DEFAULT_FONT_PROPERTIES.m_color);

	// Write the scale of the x axis
	const auto maxX = std::to_string(m_maxX);
	cv::putText(m_plot, maxX, cvPoint(m_plotSize.width - maxX.size() * chw, xAxisPos + chh),
		DEFAULT_FONT_PROPERTIES.m_type, DEFAULT_FONT_PROPERTIES.m_scale, DEFAULT_FONT_PROPERTIES.m_color);

	// x min
	cv::putText(m_plot, std::to_string(m_minX), cvPoint(m_borderSize, xAxisPos + chh),
		DEFAULT_FONT_PROPERTIES.m_type, DEFAULT_FONT_PROPERTIES.m_scale, DEFAULT_FONT_PROPERTIES.m_color);
}
//------------------------------------------------------------------------------
void CVPlot::DrawPlots()
{
	for(const auto &graph : m_graphs)
	{
		cv::Point prevPoint;
		const auto color = DeduceColor(graph.m_color);
		for(size_t i = 0; i < graph.m_x.size(); ++i)
		{
			const int y = cvRound((graph.m_y[i] - m_minY) * m_scaleY);
			const int x = cvRound((graph.m_x[i] - m_minX) * m_scaleX);

			const CvPoint nextPoint = cvPoint(m_borderSize + x, 
				m_plotSize.height - (m_borderSize + y));

			if(graph.m_style == PlotStyle::POINT || graph.m_style == PlotStyle::POINT_LINE)
				cv::circle(m_plot, nextPoint, graph.m_pointRadius, color, graph.m_pointRadius);

			// draw a line between two points
			if ((graph.m_style == PlotStyle::LINE || graph.m_style == PlotStyle::POINT_LINE) && i >= 1)
				cv::line(m_plot, prevPoint,
					nextPoint, color, 1, CV_AA);
			prevPoint = nextPoint;
		}
	}
}
//------------------------------------------------------------------------------
void CVPlot::DrawLabels()
{
	//// TODO::rework this shit
	//const int chw = 12, chh = 20;

	//for(const auto& graph : m_graphs)
	//{
	//	const auto color = DeduceColor(graph.m_color);
	//	//cv::line(m_plot, prevPoint,	nextPoint, color, 1, CV_AA);

	//	cv::putText(m_plot, graph.m_label, cvPoint(m_borderSize / 5, m_plotSize.height - m_borderSize + chh),
	//		DEFAULT_FONT_PROPERTIES.m_type, DEFAULT_FONT_PROPERTIES.m_scale, color);
	//	
	//	//posy += int(chh * 1.5);
	//}
}
//------------------------------------------------------------------------------
cv::Scalar CVPlot::DeduceColor(const Color& color)
{
	return cv::Scalar(color.m_b, color.m_g, color.m_r);
}
//------------------------------------------------------------------------------
}
