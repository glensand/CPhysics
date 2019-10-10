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

using ChanelColor = uint8_t;
	
enum class PlotStyle
{
	POINT = 0,		// Point styled graph
	LINE,			// Line styled graph

	NONE			// Means count of styles
};

struct AxisLabels final
{
	AxisLabels() = default;
	~AxisLabels() = default;

	std::string	m_arg{"x"};	// Name of the arguments axis
	std::string	m_val{"y"};	// Name of the values axis
};
	
struct Color final
{
	Color() = default;
	~Color() = default;

	ChanelColor		m_r{ };	// Red
	ChanelColor		m_g{ };	// Green
	ChanelColor		m_b{ };	// Blue
	ChanelColor		m_a{ };	// Alpha
};

struct GraphParams final
{
	GraphParams() = default;
	~GraphParams() = default;

	std::vector<double>	m_x;		// Vector of x's axis point
	std::vector<double>	m_y;		// Vector of y's axis point

	PlotStyle			m_style{ PlotStyle::LINE };						// AddGraphs's graph style
	Color				m_color{ 0, 0, 0, 255};		// Color to be used for graph plotting
};

class IPlot
{
public:

	IPlot() = default;
	virtual  ~IPlot() = default;

					// Add  the graph using passed params
	virtual void	AddGraphs(const GraphParams* params) = 0;

	virtual void	Release() = 0;

	virtual void	Show() = 0;
};
}

