/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */


#pragma once

#include "../ITask.h"
#include "CVPlot/CvPlot.h"
#include "Interface/FigureProperties.h"
#include "Interface/Figure.h"

class SinglePlotTestBase : public ITask
{
public:
	SinglePlotTestBase() = default;
	virtual ~SinglePlotTestBase() override = default;

	virtual void Clear() override{}

	virtual void Run(const Params* params = nullptr) override
	{
		Plotter::CvPlot plot;
		auto&& figures = plot.CreateFigure(1, 1);
		auto* figure = figures[0];

		Plotter::GraphParameters graphParams;
		graphParams.PointRadius = 2;
		graphParams.Style = Plotter::PlotStyle::POINT_LINE;
		graphParams.Color = Plotter::Color{0, 0, 255};

		constexpr double left = -50;
		for(std::size_t i{ 0 }; i < 100; ++i)
		{
			const auto x = (double)i + left;
			graphParams.X.push_back(x);
			graphParams.Y.push_back(ComputeY(x));
		}

		figure->AddGraph(&graphParams);

		plot.Show(true);
		plot.Close();
	}

	virtual double ComputeY(double x) const = 0;
};

class SinglePlotTest1 final : public SinglePlotTestBase
{
public:
	SinglePlotTest1() = default;
private:
	virtual double ComputeY(double x) const override { return x; }
};

class SinglePlotTest2 final : public SinglePlotTestBase
{
public:
	SinglePlotTest2() = default;
private:
	virtual double ComputeY(double x) const override { return -x; }
};

class SinglePlotTest3 final : public SinglePlotTestBase
{
public:
	SinglePlotTest3() = default;
private:
	virtual double ComputeY(double x) const override { return x * x; }
};


class SinglePlotTest4 final : public SinglePlotTestBase
{
public:
	SinglePlotTest4() = default;
private:
	virtual double ComputeY(double x) const override { return x * x * x; }
};