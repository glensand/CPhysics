#pragma once

#include "ITask.h"

class RuntimePlotExample : public ITask
{
public:
	RuntimePlotExample() = default;
	virtual ~RuntimePlotExample() override = default;

	virtual void Run(const Params* params = nullptr) override
	{
		Plotter::CVPlot plot;
		Plotter::GraphParameters graphParams;
		graphParams.PointRadius = 2;
		graphParams.Style = Plotter::PlotStyle::POINT_LINE;
		graphParams.Color = Plotter::Color{0, 0, 255};
	
		graphParams.UseDeque = true;

		for(std::size_t i{ 0 }; i < 100; ++i)
		{
			graphParams.DequeX.push_back((double)i / 100);
			graphParams.DequeY.push_back(2 * ((double)rand() / RAND_MAX) - 1);
		}

		Plotter::GridProperties gridProperties;
		gridProperties.HorizonLinesCount = 10;
		plot.SetGridProperties(gridProperties);
		plot.AddGraph(&graphParams);

		std::size_t xCounter{ 100 };

		while(true)
		{
			plot.Show(false);
			graphParams.DequeX.pop_front();
			graphParams.DequeY.pop_front();
			graphParams.DequeX.push_back((double)xCounter / 100);
			graphParams.DequeY.push_back(2 * ((double)rand() / RAND_MAX) - 1);
			++xCounter;
		}
	}
};
