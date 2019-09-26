#include "QPlot.h"
#include <iostream>

int main(int argc, char *argv[])
{
	QPlotParams params;
	params.m_test = 1;

	QPlot plot;

	plot.Plot(params);

	char c;
	std::cin >> c;
}
