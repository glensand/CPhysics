/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include "Interface/Figure.h"
#include "Interface/FigureProperties.h"
#include <set>
#include <opencv2/core.hpp>

namespace Plotter
{

struct Point final
{
	int X;
	int Y;
};

class CvFigure final : public Figure
{
	using GraphList = std::vector<const GraphParameters*>;
public:
	CvFigure(cv::Mat& mat, const cv::Size& figureSize, const Point& zero);
	virtual	~CvFigure() override = default;

	virtual void AddGraph(const GraphParameters* params) override;
	virtual void SetGridProperties(const GridProperties& gridProperties) override;
	virtual void Show() override;

private:
	void			Initialize();
	void			DrawAxis();
	void			DrawGrid();
	void			DrawHorizonLineCoordinate(int yPos, int lineIndex);
	void			DrawVerticalLineCoordinate(int xPos, int lineIndex);
	void			DrawPlots();
	void			DrawLabels();
	void			DrawRange() const;
	void			PutText(const std::string& text, int x, int y) const;
	Color			GenerateColorRand();
	cv::Scalar		DeduceColor(const Color &color);
	std::string		Format(float value) const;

	template<typename TContainer>
    void InitializeMinMax(const TContainer& x, const TContainer& y);

	cv::Mat& m_plot;
	const cv::Size m_figureSize;
	const Point m_zero;
	const int m_borderXSize{ 55 };
	const int m_borderYSize{ 10 };
	int m_rightGap{ 0 };

	double m_minX{ 0 };
	double m_maxX{ 0 };
	double m_minY{ FLT_MAX };
	double m_maxY{ FLT_MIN };

	double m_scaleY{ 1.f };
	double m_scaleX{ 1.f };

	GraphList m_graphs;
	GridProperties m_gridProperties;
	std::set<Color> m_usedColors;

	constexpr static int DefaultRightGap{ 65 };
};

}

