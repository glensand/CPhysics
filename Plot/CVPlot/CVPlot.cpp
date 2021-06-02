#include "CVPlot.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc_c.h>

#include <cctype>
#include <random>
#include <iostream>

namespace
{
const Plotter::FontProperties		DEFAULT_FONT_PROPERTIES;
const Plotter::AxisProperties		DEFAULT_AXIS_PROPERTIES;

const std::vector<Plotter::Color>	COLOR_RANGE{ {0, 0, 0}, {50, 50, 50}};
const std::vector<Plotter::Color>	DEFAULT_COLORS{
													{255, 0, 0},
													{0, 255, 0},
													{0, 0, 255},
													{255, 255, 0},
													{255, 0, 255},
													{0, 255, 255}
													};

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
	//cv::setOpenGlContext(m_plotName);
	cv::setMouseCallback(m_plotName, OnMouseHandle, this);
	cv::imshow(m_plotName, m_plot);
	cv::waitKey(0);
}
//------------------------------------------------------------------------------
void CVPlot::Close()
{
	cv::destroyWindow(m_plotName);
}
//------------------------------------------------------------------------------
void CVPlot::OnMouseHandle(int event, int x, int y, int, void* instance)
{
	if (instance == nullptr) return;
	reinterpret_cast<CVPlot*>(instance)->OnMouseHandleInner(event, x, y);
}
//------------------------------------------------------------------------------
void CVPlot::OnMouseHandleInner(int event, int x, int y)
{
	if (!m_debugPrint) return;
	const double relX = m_maxX - static_cast<double>(x) / static_cast<double>(m_plotSize.width) * (m_maxX - m_minX);
	const double relY = m_minY - static_cast<double>(y) / static_cast<double>(m_plotSize.width) * (m_maxY - m_minY);

	std::cout << -relX << " " << relY << std::endl;
	// TODO:: recompile opencv with opengl support
	/*
	cv::putText(m_plot, "x: " + std::to_string(relX), cvPoint(m_plotSize.width - 2 * m_borderSize, m_borderSize),
		DEFAULT_FONT_PROPERTIES.m_type, DEFAULT_FONT_PROPERTIES.m_scale, DEFAULT_FONT_PROPERTIES.m_color);

	cv::putText(m_plot, "y: " + std::to_string(relY), cvPoint(m_plotSize.width - 2 * m_borderSize, 2 * m_borderSize),
		DEFAULT_FONT_PROPERTIES.m_type, DEFAULT_FONT_PROPERTIES.m_scale, DEFAULT_FONT_PROPERTIES.m_color);

	cv::updateWindow(m_plotName);*/
}
//------------------------------------------------------------------------------
void CVPlot::Initialize()
{
	m_plot = cv::Mat(m_plotSize.height, m_plotSize.width, CV_8UC3, m_defaultBackgroundColor);
	
	// find maximum/minimum of axis
	for(const auto &graph : m_graphs)
	{
		std::for_each(graph.X.begin(), graph.X.end(),
			[this](const double x)
			{
				if (x < m_minX) m_minX = static_cast<float>(x);
				if (x > m_maxX) m_maxX = static_cast<float>(x);
			}
		);
		
		std::for_each(graph.Y.begin(), graph.Y.end(),
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
		DEFAULT_AXIS_PROPERTIES.Color, DEFAULT_AXIS_PROPERTIES.Thickness);

	// TODO:move y axis to (0; 0)
	// y axis
	cv::line(m_plot, { m_borderSize, m_plotSize.height - m_borderSize },
		{  m_borderSize, m_borderSize }, 
		DEFAULT_AXIS_PROPERTIES.Color, DEFAULT_AXIS_PROPERTIES.Thickness);

	// Write the scale of the y axis
	const int chw = 12, chh = 20;
	if ((m_maxY - yRef) > 0.05 * (m_maxY - m_minY))
		cv::putText(m_plot, std::to_string(m_maxY), cvPoint(m_borderSize / 5, m_borderSize - chh / 2),
			DEFAULT_FONT_PROPERTIES.Type, DEFAULT_FONT_PROPERTIES.Scale, DEFAULT_FONT_PROPERTIES.Color);

	if ((yRef - m_minY) > 0.05 * (m_maxX - m_minY))
		cv::putText(m_plot, std::to_string(m_minY), cvPoint(m_borderSize / 5, m_plotSize.height - m_borderSize + chh),
			DEFAULT_FONT_PROPERTIES.Type, DEFAULT_FONT_PROPERTIES.Scale, DEFAULT_FONT_PROPERTIES.Color);

	// x axis
	cv::putText(m_plot, std::to_string(yRef), cvPoint(m_borderSize / 5, xAxisPos + chh / 2),
		DEFAULT_FONT_PROPERTIES.Type, DEFAULT_FONT_PROPERTIES.Scale, DEFAULT_FONT_PROPERTIES.Color);

	// Write the scale of the x axis
	const auto maxX = std::to_string(m_maxX);
	cv::putText(m_plot, maxX, cvPoint(m_plotSize.width - maxX.size() * chw, xAxisPos + chh),
		DEFAULT_FONT_PROPERTIES.Type, DEFAULT_FONT_PROPERTIES.Scale, DEFAULT_FONT_PROPERTIES.Color);

	// x min
	cv::putText(m_plot, std::to_string(m_minX), cvPoint(m_borderSize, xAxisPos + chh),
		DEFAULT_FONT_PROPERTIES.Type, DEFAULT_FONT_PROPERTIES.Scale, DEFAULT_FONT_PROPERTIES.Color);
}
//------------------------------------------------------------------------------
void CVPlot::DrawPlots()
{
	for(const auto &graph : m_graphs)
	{
		cv::Point prevPoint;
		const auto color = DeduceColor(graph.Color);
		for(size_t i = 0; i < graph.X.size(); ++i)
		{
			const int y = cvRound((graph.Y[i] - m_minY) * m_scaleY);
			const int x = cvRound((graph.X[i] - m_minX) * m_scaleX);

			const CvPoint nextPoint = cvPoint(m_borderSize + x, 
				m_plotSize.height - (m_borderSize + y));

			if(graph.Style == PlotStyle::POINT || graph.Style == PlotStyle::POINT_LINE)
				cv::circle(m_plot, nextPoint, graph.PointRadius, color, graph.PointRadius);

			// draw a line between two points
			if ((graph.Style == PlotStyle::LINE || graph.Style == PlotStyle::POINT_LINE) && i >= 1)
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
void CVPlot::Print(const std::string& text, int x, int y)
{
}
//------------------------------------------------------------------------------
Color CVPlot::GenerateColorRand()
{
	if(m_usedColors.size() < DEFAULT_COLORS.size())
	{
		const auto color = DEFAULT_COLORS[m_usedColors.size()];
		m_usedColors.emplace(color);
		return color;
	}
	
	std::random_device rd;
	std::mt19937 mt(rd());
	const std::uniform_int_distribution<int> red(COLOR_RANGE[0].R, COLOR_RANGE[1].R);
	const std::uniform_int_distribution<int> green(COLOR_RANGE[0].G, COLOR_RANGE[1].G);
	const std::uniform_int_distribution<int> blue(COLOR_RANGE[0].B, COLOR_RANGE[1].B);

	const size_t iterations = 100;
	for (size_t i{ 0 }; i < iterations; ++i) {

		const auto color = Color{ blue(mt), green(mt), red(mt) };
		if (m_usedColors.count(color) == 0)
		{
			m_usedColors.emplace(color);
			return color;
		}
	}

	return Color{ 0, 0, 0 };
}
//------------------------------------------------------------------------------
cv::Scalar CVPlot::DeduceColor(const Color& color)
{
	if (color.B == -1) return DeduceColor(GenerateColorRand());
	return cv::Scalar( color.B, color.G, color.R );
}
//------------------------------------------------------------------------------
}
