//------------------------------------------------------------------------------
// IPlot.h
// General interface and params for all related plotting classes
//
// Copyright (c) 2019 GlenSand
// All rights reserved.
//
// Date: 9.10.2019
// Author: Bezborodov Gleb
//------------------------------------------------------------------------------
#pragma once
#include <vector>
#include <string>

namespace Plotter
{

using ChanelColor = int;
//==============================================================================	
enum class PlotStyle
{
	POINT = 0,		// Point styled graph
	LINE,			// Line styled graph
	POINT_LINE,		// Plots graph, with both of those elements

	NONE			// Means count of styles
};
//==============================================================================
struct AxisLabels final
{
	AxisLabels() = default;
	~AxisLabels() = default;

	std::string	Arg{"x"};	// Name of the arguments axis
	std::string	Val{"y"};	// Name of the values axis
};
//==============================================================================
struct Color final
{
	Color() = default;
	~Color() = default;

	ChanelColor		B{ };	
	ChanelColor		G{ };	
	ChanelColor		R{ };

	bool operator==(const Color &rhs) const { return B == rhs.B && R == rhs.R && G == rhs.G; }
	bool operator!=(const Color& rhs) const { return !(*this != rhs); }
	bool operator<(const Color& rhs) const
	{
		if (B != rhs.B) return B < rhs.B;
		if (G != rhs.G) return G < rhs.G;

		return R < rhs.R;
	}
};
//==============================================================================
struct GraphParams final
{
	GraphParams() = default;
	~GraphParams() = default;

	std::vector<double>	X;		// Vector of x's axis point
	std::vector<double>	Y;		// Vector of y's axis point

	PlotStyle			Style{ PlotStyle::LINE };						// graph style
	Color				Color{ -1, -1, -1};					// Color to be used for graph plotting
	std::string			Label{ "function" };
	size_t				PointRadius{ 2 };
	bool				RandomColor{ true };
};
//==============================================================================
class IPlot
{
public:

	IPlot() = default;
	virtual  ~IPlot() = default;

					// Add the graph using passed params
	virtual void	AddGraph(const GraphParams* params) = 0;

	virtual void	Release() = 0;

	virtual void	Show() = 0;

	virtual void	Close() = 0;
};
//==============================================================================
}

