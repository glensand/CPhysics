//------------------------------------------------------------------------------
// CVPlot2.h
// cv::plot unified coverage
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 15.10.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once
#include "../IPlot.h"

#include <opencv2/opencv.hpp>
//#include <opencv2/plot.hpp>
#include <opencv2/core.hpp >

namespace Plotter
{
	
class CVPlot2 : public IPlot
{
public:
	
	CVPlot2() = default;
	virtual  ~CVPlot2() = default;

	void	AddGraph(const GraphParams* params) override;

	void	Show() override;

	void	Release() override;

	void	Close() override;

private:
	
	//cv::Ptr<cv::plot::Plot2d>
};

}

