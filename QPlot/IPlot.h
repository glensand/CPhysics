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

struct GraphInformation final
{
	GraphInformation() = default;
	~GraphInformation() = default;

	std::vector<double>	m_x;		// Vector of x's axis point
	std::vector<double>	m_y;		// Vector of y's axis point

	PlotStyle			m_style{ PlotStyle::LINE };					// Plot's graph style
	Color				m_color{ 0, 0, 0, 255};		// Color to be used for graph plotting
	AxisLabels			m_labels{ "x", "y" };			// Axis names
};

struct PlotParams
{
	PlotParams() = default;
	virtual ~PlotParams() = default;

	std::vector<GraphInformation>	m_functions;	// All the functions to be plotted
};

class IPlot
{
public:

	IPlot() = default;
	virtual  ~IPlot() = default;

					// Plot the graph using passed params
	virtual void	Plot(const PlotParams* params) = 0;
};
}

