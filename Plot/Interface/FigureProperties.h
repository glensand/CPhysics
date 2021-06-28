/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
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
	std::string FunctionName;

	int HorizonThickness{ 1 };
	int VerticalThickness{ 1 };
	int HorizonLinesCount{ 10 };
	int VerticalLinesCount{ 10 };
    Color GridColor{ 200,203,200 };
	bool PrintRange{ false };
	bool DrawAxis{ true };
};

struct GraphParameters final
{
	GraphParameters() = default;
	~GraphParameters() = default;

	std::vector<double>	X;		// Vector of x's axis point
	std::vector<double>	Y;		// Vector of y's axis point

	std::deque<double>	DequeX;	// Deque of x's axis point
	std::deque<double>	DequeY;	// Deque of y's axis point

	std::string Label{ "function" };

	PlotStyle Style{ PlotStyle::LINE };						// graph style
	Color Color{ -1, -1, -1 };					// Color to be used for graph plotting
	size_t PointRadius{ 2 };
    unsigned LineThickness{ 1 };
    bool RandomColor{ true };
	bool UseDeque{ false };
};

}

