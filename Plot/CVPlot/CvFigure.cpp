#include "CvFigure.h"

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/types_c.h>

#include <random>
#include <array>
#include <charconv>

namespace
{

struct FontProperties final
{
	double		Scale{ .4 };
	int			Type{ cv::HersheyFonts::FONT_HERSHEY_SIMPLEX };
	cv::Scalar	Color{ 0, 0, 0 };
};

struct AxisProperties final
{
	cv::Scalar	Color{ 0, 0, 0 };
	int			Thickness{ 2 };
};

const FontProperties		DEFAULT_FONT_PROPERTIES;
const AxisProperties		DEFAULT_AXIS_PROPERTIES;

const std::vector<Plotter::Color>	COLOR_RANGE{ {0, 0, 0}, {50, 50, 50} };
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

CvFigure::CvFigure(cv::Mat& mat, const cv::Size& figureSize, const Point& zero)
    : m_plot(mat)
	, m_figureSize(figureSize)
	, m_zero(zero)
{

}

void CvFigure::AddGraph(const GraphParameters* params)
{
	m_graphs.emplace_back(params);
}

void CvFigure::SetGridProperties(const GridProperties& gridProperties)
{
	m_gridProperties = gridProperties;

	if (m_gridProperties.PrintRange)
		m_rightGap = DefaultRightGap;
}

void CvFigure::Show()
{
	Initialize();
	DrawAxis();
	DrawGrid();
	DrawPlots();
	DrawLabels();
	DrawRange();
}

std::string CvFigure::Format(float value) const
{
	std::array<char, 10> buffer{};
	auto&& [ptr, ec] = std::to_chars(buffer.data(), buffer.data() + buffer.size(), value,
		std::chars_format::fixed, 3);
	return std::string(buffer.data(), ptr);
}

template<typename TContainer>
void CvFigure::InitializeMinMax(const TContainer& x, const TContainer& y)
{
	// find maximum/minimum of axis
	std::for_each(x.begin(), x.end(),
		[this](const double x)
		{
			if (x < m_minX) m_minX = x;
			if (x > m_maxX) m_maxX = x;
		}
	);

	std::for_each(y.begin(), y.end(),
		[this](const double y)
		{
			if (y < m_minY) 
				m_minY = y;
			if (y > m_maxY) 
				m_maxY = y;
		}
	);
}

void CvFigure::Initialize()
{
	m_minX = DBL_MAX;
	m_minY = DBL_MAX;

	m_maxX = -DBL_MAX;
	m_maxY = -DBL_MAX;

	for (const auto& graph : m_graphs)
	{
		if (graph->UseDeque)
		{
			InitializeMinMax(graph->DequeX, graph->DequeY);
		}
		else
		{
			InitializeMinMax(graph->X, graph->Y);
		}
	}

	auto range = m_maxY - m_minY;
	const double eps = 1e-9;
	if (range <= eps)
	{
		range = 1.;
		m_minY = m_maxY / 2;
		m_maxY = m_maxY * 3 / 2;
	}

	m_scaleX = double(m_figureSize.width - m_borderXSize * 2 - m_rightGap) / (m_maxX - m_minX);
	m_scaleY = double(m_figureSize.height - m_borderYSize * 2) / range;
}

void CvFigure::DrawAxis()
{
	if(!m_gridProperties.DrawAxis)
		return;

	float yRef = 0;

	const int xAxisPos = m_figureSize.height + m_zero.Y - m_borderYSize
		- cvRound((yRef - m_minY) * m_scaleY);

	// x axis
	cv::line(m_plot, { m_borderXSize + m_zero.X, xAxisPos },
		{ m_figureSize.width + m_zero.X - m_borderXSize - m_rightGap, xAxisPos },
		DEFAULT_AXIS_PROPERTIES.Color, DEFAULT_AXIS_PROPERTIES.Thickness);

	// TODO:move y axis to (0; 0)
	// y axis
	cv::line(m_plot, { m_borderXSize + m_zero.X, m_figureSize.height + m_zero.Y - m_borderYSize },
		{ m_borderXSize + m_zero.X, m_borderYSize + m_zero.Y },
		DEFAULT_AXIS_PROPERTIES.Color, DEFAULT_AXIS_PROPERTIES.Thickness);
}

void CvFigure::DrawGrid()
{
	auto&& gridColor = cv::Scalar(m_gridProperties.GridColor.B, m_gridProperties.GridColor.G, m_gridProperties.GridColor.R);

	const int yStep = (m_figureSize.height - 2 * m_borderYSize) / (m_gridProperties.HorizonLinesCount + 1);
	int curY = m_borderYSize + m_zero.Y;

	for (int i{ 0 }; i < m_gridProperties.HorizonLinesCount + 2; ++i)
	{
		cv::line(m_plot, { m_borderXSize + m_zero.X, curY },
			{ m_figureSize.width + m_zero.X - m_borderXSize - m_rightGap, curY },
			gridColor, m_gridProperties.HorizonThickness);

		DrawHorizonLineCoordinate(curY, i);

		curY += yStep;
	}

	const int xStep = (m_figureSize.width - 2 * m_borderXSize - m_rightGap) / (m_gridProperties.VerticalLinesCount + 1);
	int curX = m_borderXSize + m_zero.X;

	for (int i{ 0 }; i < m_gridProperties.VerticalLinesCount + 2; ++i)
	{
		cv::line(m_plot, { curX, m_zero.Y + m_borderYSize },
			{ curX, m_figureSize.height + m_zero.Y - m_borderYSize },
			gridColor, m_gridProperties.VerticalThickness);

		DrawVerticalLineCoordinate(curX, i);

		curX += xStep;
	}
}

void CvFigure::DrawHorizonLineCoordinate(int yPos, int lineIndex)
{
	const auto y = m_maxY - (float)lineIndex * (m_maxY - m_minY) / (float)(m_gridProperties.HorizonLinesCount + 1);
	PutText(Format(y), m_zero.X, yPos);
}

void CvFigure::DrawVerticalLineCoordinate(int xPos, int lineIndex)
{
	auto chh = 12;
	const auto x = m_minX + (float)lineIndex * (m_maxX - m_minX) / (float)(m_gridProperties.VerticalLinesCount + 1);
	PutText(Format(x), xPos + 1, m_figureSize.height + m_zero.Y - m_borderYSize + chh + 3);
}

void CvFigure::DrawPlots()
{
	for (const auto& graph : m_graphs)
	{
		cv::Point prevPoint;
		const auto color = DeduceColor(graph->Color);
		std::size_t size = graph->UseDeque ? graph->DequeX.size() : graph->X.size();

		for (size_t i = 0; i < size; ++i)
		{
			double rawX = graph->UseDeque ? graph->DequeX[i] : graph->X[i];
			double rawY = graph->UseDeque ? graph->DequeY[i] : graph->Y[i];

			int x = cvRound((rawX - m_minX) * m_scaleX);
			int y = cvRound((rawY - m_minY) * m_scaleY);

			const CvPoint nextPoint = cvPoint(m_borderXSize + m_zero.X + x,
				m_figureSize.height + m_zero.Y - (m_borderYSize + y));

			if (graph->Style == PlotStyle::POINT || graph->Style == PlotStyle::POINT_LINE)
				cv::circle(m_plot, nextPoint, graph->PointRadius, color, graph->PointRadius);

			// draw a line between two points
			if ((graph->Style == PlotStyle::LINE || graph->Style == PlotStyle::POINT_LINE) && i >= 1)
				cv::line(m_plot, prevPoint,
					nextPoint, color, graph->LineThickness, cv::LINE_AA);
			prevPoint = nextPoint;
		}
	}
}

void CvFigure::DrawLabels()
{

}

void CvFigure::DrawRange() const
{
	if (!m_gridProperties.PrintRange)
		return;


	int yGap = 30;
	if(!m_gridProperties.FunctionName.empty())
	{
		PutText(m_gridProperties.FunctionName, 10 + m_zero.X + m_figureSize.width - m_rightGap - m_borderXSize, m_zero.Y + yGap);
		yGap += 20;
	}

	PutText("Min f: ", 10 + m_zero.X + m_figureSize.width - m_rightGap - m_borderXSize, m_zero.Y + yGap);
	PutText(Format(m_minY), 55 + m_zero.X + m_figureSize.width - m_rightGap - m_borderXSize, m_zero.Y + yGap);
	yGap += 20;

	PutText("Max f: ", 10 + m_zero.X + m_figureSize.width - m_rightGap - m_borderXSize, m_zero.Y + yGap);
	PutText(Format(m_maxY), 55 + m_zero.X + m_figureSize.width - m_rightGap - m_borderXSize, m_zero.Y + yGap);
	yGap += 20;

	PutText("Range f: ", 10 + m_zero.X + m_figureSize.width - m_rightGap - m_borderXSize, m_zero.Y + yGap);
	PutText(Format(m_maxY - m_minY), 70 + m_zero.X + m_figureSize.width - m_rightGap - m_borderXSize, m_zero.Y + yGap);
}

void CvFigure::PutText(const std::string& text, int x, int y) const
{
	cv::putText(m_plot, text, cvPoint(x, y),
		DEFAULT_FONT_PROPERTIES.Type, DEFAULT_FONT_PROPERTIES.Scale, DEFAULT_FONT_PROPERTIES.Color);
}

Color CvFigure::GenerateColorRand()
{
	if (m_usedColors.size() < DEFAULT_COLORS.size())
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

cv::Scalar CvFigure::DeduceColor(const Color& color)
{
	if (color.B == -1)
		return DeduceColor(GenerateColorRand());
	return cv::Scalar(color.B, color.G, color.R);
}

}
