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

	std::string	m_arg{"x"};	// Name of the arguments axis
	std::string	m_val{"y"};	// Name of the values axis
};
//==============================================================================
struct Color final
{
	Color() = default;
	~Color() = default;

	ChanelColor		m_b{ };	
	ChanelColor		m_g{ };	
	ChanelColor		m_r{ };

	bool operator==(const Color &rhs) const { return m_b == rhs.m_b && m_r == rhs.m_r && m_g == rhs.m_g; }
	bool operator!=(const Color& rhs) const { return !(*this != rhs); }
	bool operator<(const Color& rhs) const
	{
		if (m_b != rhs.m_b) return m_b < rhs.m_b;
		if (m_g != rhs.m_g) return m_g < rhs.m_g;

		return m_r < rhs.m_r;
	}
};
//==============================================================================
struct GraphParams final
{
	GraphParams() = default;
	~GraphParams() = default;

	std::vector<double>	m_x;		// Vector of x's axis point
	std::vector<double>	m_y;		// Vector of y's axis point

	PlotStyle			m_style{ PlotStyle::LINE };						// graph style
	Color				m_color{ -1, -1, -1};					// Color to be used for graph plotting
	std::string			m_label{ "function" };
	size_t				m_pointRadius{ 2 };
	bool				m_randomColor{ true };
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

