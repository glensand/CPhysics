#include "QPlot.h"
#include <iostream>

int main()
{
	Plotter::PlotParams params;

	const double a = -1; 
	const double b = 1; 
	const double h = 0.1; 

	const int N = (b - a) / h + 2;
	Plotter::GraphInformation info;

	info.m_x.reserve(N);
	info.m_y.reserve(N);
	
	for (double X = a; X <= b; X += h)
	{
		info.m_x.emplace_back(X);
		info.m_y.emplace_back(X * X);
	}

	params.m_functions.emplace_back(info);
	Plotter::QPlot plot;
	
	plot.Plot(&params);

	char c;
	std::cin >> c;
}
