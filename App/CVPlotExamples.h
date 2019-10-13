//------------------------------------------------------------------------------
// CVPlotExamples.h
// 
// Some examples, which represent basic opportunities of CVPlot
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date:	11.10.2019
// Author:	Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once

#include "Task.h"
#include "CVPlot/CVPlot.h"

class CVPlotExamples : public Task
{
public:

	virtual ~CVPlotExamples() = default;

	void Run(const Params* params = nullptr) const override;
};

inline void CVPlotExamples::Run(const Params*) const
{	
	Plotter::CVPlot plotter;

	Plotter::GraphParams params;

	const double a = -1; 
	const double b = 1; 
	const double h = 0.1; 

	const int N = (b - a) / h + 2;
	Plotter::GraphParams info;
	Plotter::GraphParams info2;

	info2.m_x.reserve(N);
	info2.m_y.reserve(N);
	
	info.m_x.reserve(N);
	info.m_y.reserve(N);
	
	for (double X = a; X <= b; X += h)
	{
		info.m_x.emplace_back(X);
		info.m_y.emplace_back(X * X);

		info2.m_x.emplace_back(X);
		info2.m_y.emplace_back(4 * X * X);
	}

	plotter.AddGraph(&info);
	plotter.AddGraph(&info2);

	plotter.Show();
}
