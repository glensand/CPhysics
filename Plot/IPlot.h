/* Copyright (C) 2019 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once
#include <deque>
#include <vector>
#include <string>

namespace Plotter
{

using ChanelColor = int;
	
enum class PlotStyle
{
	POINT = 0,		// Point styled graph
	LINE,			// Line styled graph
	POINT_LINE,		// Plots graph, with both of those elements

	NONE			// Means count of styles
};

struct AxisLabels final
{
	AxisLabels() = default;
	~AxisLabels() = default;

	std::string	Arg{"x"};	// Name of the arguments axis
	std::string	Val{"y"};	// Name of the values axis
};

struct Color final
{
	Color() = default;
	~Color() = default;

	ChanelColor B{ };	
	ChanelColor G{ };	
	ChanelColor R{ };

	bool operator==(const Color &rhs) const { return B == rhs.B && R == rhs.R && G == rhs.G; }
	bool operator!=(const Color& rhs) const { return !(*this != rhs); }
	bool operator<(const Color& rhs) const
	{
		if (B != rhs.B) return B < rhs.B;
		if (G != rhs.G) return G < rhs.G;

		return R < rhs.R;
	}
};

struct GridProperties final
{
	int HorizonThickness{ 1 };
	int VerticalThickness{ 1 };
	int HorizonLinesCount{ 10 };
	int VerticalLinesCount{ 10 };
    Color GridColor{ 200,203,200 };
};

struct GraphParameters final
{
	GraphParameters() = default;
	~GraphParameters() = default;

	std::vector<double>	X;		// Vector of x's axis point
	std::vector<double>	Y;		// Vector of y's axis point

	PlotStyle			Style{ PlotStyle::LINE };						// graph style
	Color				Color{ -1, -1, -1};					// Color to be used for graph plotting
	std::string			Label{ "function" };
	size_t				PointRadius{ 2 };
	bool				RandomColor{ true };

	std::deque<double>	DequeX;	// Deque of x's axis point
	std::deque<double>	DequeY;	// Deque of y's axis point
	bool UseDeque{ false };
};

class IPlot
{
public:

	IPlot() = default;
	virtual  ~IPlot() = default;

					// Add the graph using passed params
	virtual void	AddGraph(const GraphParameters* params) = 0;
	virtual void	Release() = 0;
	virtual void	Show(bool waitKey = true) = 0;
	virtual void	Clear() = 0;
	virtual void	Close() = 0;
	virtual void	SetGridProperties(const GridProperties& gridProperties) = 0;
};

}

