//------------------------------------------------------------------------------
// CVPlot.h
// 
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 9.10.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "../IPlot.h"

#include <string>
#include <set>

namespace Plotter
{
//==============================================================================
struct FontProperties final
{
	double		Scale{ .4 };
	int			Type{ cv::HersheyFonts::FONT_HERSHEY_SIMPLEX };
	cv::Scalar	Color{ 0, 0, 0 };
};
//==============================================================================
struct AxisProperties final
{
	cv::Scalar	Color {0, 0, 0};
	int			Thickness{ 2 };
};
//==============================================================================
class CVPlot final : public IPlot
{
public:

				CVPlot() = default;
	virtual		~CVPlot() = default;

	void		AddGraph(const GraphParams* params) override;

	void		Release() override;

	void		Show() override;

	void		Close() override;

	// own methods
	void		EnableDebugPrint(bool enable) { m_debugPrint = enable; };
private:

	void				Initialize();

	void				DrawAxis();

	void				DrawPlots();

	void				DrawLabels();

	void				Print(const std::string &text, int x, int y);
	
	Color				GenerateColorRand();
	
	cv::Scalar			DeduceColor(const Color &color);

	static void			OnMouseHandle(int event, int x, int y, int, void* instance);
	void				OnMouseHandleInner(int event, int x, int y);

	std::string		m_plotName { "Plot" };
	cv::Mat			m_plot;
	cv::Size		m_plotSize{ 1300, 700 };
	cv::Scalar		m_defaultBackgroundColor{ 255, 255, 255 };

	const int		m_borderSize{ 30 };

	float			m_minX{ 0 };
	float			m_maxX{ 0 };
	float			m_minY{ FLT_MAX };
	float			m_maxY{ FLT_MIN };

	float			m_scaleY{ 1.f };
	float			m_scaleX{ 1.f };

	bool			m_debugPrint{ false };
	
	std::vector<GraphParams>		m_graphs;
	AxisLabels						m_labels;

	std::set<Color>					m_usedColors;
};
//==============================================================================
}

