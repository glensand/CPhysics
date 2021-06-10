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

#include "ITask.h"
#include "CVPlot/CVPlot.h"

class CVPlotExamples : public ITask
{
public:

	virtual ~CVPlotExamples() = default;

	virtual void Clear() override {}
	void Run(const Params* params = nullptr) override;
};

inline void CVPlotExamples::Run(const Params*)
{	
	Plotter::CVPlot plotter;

	Plotter::GraphParameters params;

	const double a = -1; 
	const double b = 1; 
	const double h = 0.1; 

	const int N = (b - a) / h + 2;
	Plotter::GraphParameters info;
	Plotter::GraphParameters info2;

	info2.X.reserve(N);
	info2.Y.reserve(N);
	
	info.X.reserve(N);
	info.Y.reserve(N);
	
	for (double X = a; X <= b; X += h)
	{
		info.X.emplace_back(X);
		info.Y.emplace_back(X * X);

		info2.X.emplace_back(X);
		info2.Y.emplace_back(4 * X * X);
	}

	plotter.AddGraph(&info);
	plotter.AddGraph(&info2);

	plotter.Show();
}
