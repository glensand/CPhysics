#include "CVPlot/CvPlot.h"
#include "CVPlot/CvFigure.h"

#include <opencv2/highgui.hpp>

namespace Plotter
{

void CvPlot::Present(bool waitKey)
{
    cv::namedWindow(m_plotName, cv::WINDOW_AUTOSIZE);
    cv::setMouseCallback(m_plotName, OnMouseHandle, this);
    cv::imshow(m_plotName, m_plot);
    static int rawDelay = 1;
    const auto delay = waitKey ? 0 : rawDelay;
	m_lastKey = cv::waitKey(delay);
}

const Plot::FigureList& CvPlot::CreateFigure(std::size_t cols, std::size_t rows)
{
	const auto figureHeight = std::size_t(double(m_plotSize.height - 2 * m_borderSize) / rows);
	const auto figureWidth = std::size_t(double(m_plotSize.width - 2 * m_borderSize) / cols);
	const cv::Size figureSize(figureWidth, figureHeight);

	for(auto col{ 0 }; col < cols; ++col)
	{
	    for(auto row{ 0 }; row < rows; ++row)
	    {
			const Point curCorner{ col * figureWidth , row * figureHeight };
			m_figures.push_back(new CvFigure(m_plot, figureSize, curCorner));
	    }
	}

	return m_figures;
}

void CvPlot::Show(bool waitKey)
{
	m_plot = cv::Mat(m_plotSize.height, m_plotSize.width, CV_8UC3, m_defaultBackgroundColor);

    for (auto* fig : m_figures)
		fig->Show();

	Present(waitKey);
}

void CvPlot::Close()
{
	cv::destroyWindow(m_plotName);
}

void CvPlot::Clear()
{
	for (auto* fig : m_figures)
		delete fig;

	m_figures.clear();
}

void CvPlot::OnMouseHandle(int event, int x, int y, int, void* instance)
{
	if (instance == nullptr) return;
	reinterpret_cast<CvPlot*>(instance)->OnMouseHandleInner(event, x, y);
}

void CvPlot::OnMouseHandleInner(int event, int x, int y)
{
	if (!m_debugPrint) 
		return;
}

}
