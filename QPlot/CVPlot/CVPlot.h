//------------------------------------------------------------------------------
// CVPlot.h
// 
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

namespace Plotter
{

class CVPlot final : public IPlot
{
public:

				CVPlot() = default;
	virtual		~CVPlot() = default;

	void		AddGraphs(const GraphParams* params) override;

	void		Release() override;

	void		Show() override;
private:

	void		Initialize();

	void		DrawAxis();

	void		DrawPlots();

	void		DrawLabels();
	
	bool			m_initialized{ };
	std::string		m_plotName;
	cv::Mat			m_plot;
	cv::Size		m_plotSize{ };

	const size_t	m_borderSize{ 30 };

	std::vector<GraphParams>		m_graphs;
	AxisLabels						m_labels;
};

}

