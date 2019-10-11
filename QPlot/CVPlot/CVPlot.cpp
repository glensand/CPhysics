#include "CVPlot.h"

#include <opencv2/imgproc/imgproc_c.h>

namespace Plotter
{

//------------------------------------------------------------------------------
void CVPlot::AddGraphs(const GraphParams* params)
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
	m_plot = cv::Mat::ones(m_plotSize.height, m_plotSize.width, CV_8UC3);
	// find maximum/minimum of axes
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

	if (m_maxX - m_minX > 1.f)
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
		{ m_plotSize.width - m_borderSize, xAxisPos }, m_axisColor);

	// TODO:move y axis to (0; 0)
	// y axis
	cv::line(m_plot, { m_borderSize, m_plotSize.height - m_borderSize },
		{  m_borderSize, m_borderSize }, m_axisColor);

	// Write the scale of the y axis
	const int chw = 6, chh = 10;
	if ((m_maxY - yRef) > 0.05 * (m_maxY - m_minY))
		cv::putText(m_plot, std::to_string(m_maxY), cvPoint(m_borderSize / 5, m_borderSize - chh / 2),
			cv::FONT_HERSHEY_PLAIN, 0.55, m_axisColor);

	if ((yRef - m_minY) > 0.05 * (m_maxX - m_minY))
		cv::putText(m_plot, std::to_string(m_minY), cvPoint(m_borderSize / 5, m_plotSize.height - m_borderSize + chh),
			cv::FONT_HERSHEY_PLAIN, 0.55, m_axisColor);

	// x axis
	cv::putText(m_plot, std::to_string(yRef), cvPoint(m_borderSize / 5, xAxisPos + chh / 2),
		cv::FONT_HERSHEY_PLAIN, 0.55, m_axisColor);

	// Write the scale of the x axis
	const auto maxX = std::to_string(m_maxX);
	cv::putText(m_plot, maxX, cvPoint(m_plotSize.width - maxX.size() * chw, xAxisPos + chh),
		cv::FONT_HERSHEY_PLAIN, 0.55, m_axisColor);

	// x min
	cv::putText(m_plot, std::to_string(m_minX), cvPoint(m_borderSize, xAxisPos + chh),
		cv::FONT_HERSHEY_PLAIN, 0.55, m_axisColor);
}
//------------------------------------------------------------------------------
void CVPlot::DrawPlots()
{
	for(const auto &graph : m_graphs)
	{
		cv::Point prevPoint;
		for(size_t i = 0; i < graph.m_x.size(); ++i)
		{
			const int y = cvRound((graph.m_y[i] - m_minY) * m_scaleY);
			const int x = cvRound((graph.m_x[i] - m_minX) * m_scaleX);

			const CvPoint nextPoint = cvPoint(m_borderSize + x, 
				m_plotSize.height - (m_borderSize + y));

			cv::circle(m_plot, nextPoint, 1, m_axisColor, 1);

			// draw a line between two points
			if (i >= 1)
				cv::line(m_plot, prevPoint,
					nextPoint, m_axisColor, 1, CV_AA);
			prevPoint = nextPoint;
		}
	}
}
//------------------------------------------------------------------------------
void CVPlot::DrawLabels()
{
	// TODO::rework that shit

	//CvFont font;
	//cvInitFont(&font, CV_FONT_HERSHEY_PLAIN, 0.55, 1.0, 0, 1, CV_AA);

	//// character size
	//int chw = 6, chh = 8;

	// plots == m_graphs
	//for (std::vector<Series>::iterator iter = plots.begin();
	//	iter != plots.end();
	//	iter++)
	//{
	//	std::string lbl = iter->label;
	//	// draw label if one is available
	//	if (lbl.length() > 0)
	//	{
	//		cvLine(output, cvPoint(posx, posy - chh / 2), cvPoint(posx + 15, posy - chh / 2),
	//			iter->color, 2, CV_AA);

	//		cvPutText(output, lbl.c_str(), cvPoint(posx + 20, posy),
	//			&font, iter->color);

	//		posy += int(chh * 1.5);
	//	}
	//}
}
//------------------------------------------------------------------------------
}
