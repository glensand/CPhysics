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

class DoubleDoubleTestBase : public ITask
{
public:
	DoubleDoubleTestBase() = default;
	virtual ~DoubleDoubleTestBase() override = default;

	virtual void Clear() override{}

	virtual void Run(const Params* params = nullptr) override
	{
		Plotter::CvPlot plot;
		auto&& figures = plot.CreateFigure(2, 2);
		auto* figure1 = figures[0];
		auto* figure2 = figures[1];
		auto* figure3 = figures[2];
		auto* figure4 = figures[3];

		Plotter::GraphParameters graphParams1;
		Plotter::GraphParameters graphParams2;

		constexpr double left = -50;
		for(std::size_t i{ 0 }; i < 100; ++i)
		{
			const auto x = (double)i + left;
			graphParams1.X.push_back(x);
			graphParams1.Y.push_back(ComputeY(x));

			graphParams2.X.push_back(x);
			graphParams2.Y.push_back(-ComputeY(x));
		}

		figure1->AddGraph(&graphParams1);
		figure2->AddGraph(&graphParams2);

		figure3->AddGraph(&graphParams1);
		figure4->AddGraph(&graphParams2);

		plot.Show(true);
		plot.Close();
	}

	virtual double ComputeY(double x) const = 0;
};

class DoubleDoubleTest1 final : public DoubleDoubleTestBase
{
public:
	DoubleDoubleTest1() = default;
private:
	virtual double ComputeY(double x) const override { return x; }
};

class DoubleDoubleTest2 final : public DoubleDoubleTestBase
{
public:
	DoubleDoubleTest2() = default;
private:
	virtual double ComputeY(double x) const override { return -x; }
};

class DoubleDoubleTest3 final : public DoubleDoubleTestBase
{
public:
	DoubleDoubleTest3() = default;
private:
	virtual double ComputeY(double x) const override { return x * x; }
};


class DoubleDoubleTest4 final : public DoubleDoubleTestBase
{
public:
	DoubleDoubleTest4() = default;
private:
	virtual double ComputeY(double x) const override { return x * x * x; }
};