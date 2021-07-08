/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include "ViveExploration/ViveExploreBase.h"
#include "PointTransformer.h"

class ViveExplore final : public ViveExploreBase
{
    struct Graph3Set final
    {
        Plotter::GraphParameters& X;
        Plotter::GraphParameters& Y;
        Plotter::GraphParameters& Z;
    };

public:
    ViveExplore(PlotStyle style = PlotStyle::AdaptiveRange);
    virtual ~ViveExplore() override = default;
    
private:
	virtual void ClearPlot() override;
    virtual void ProcessKeyImpl(int keyCode) override;
    virtual void ProcessNewPointImpl(std::size_t curIndex) override;
    virtual void InitializeFigures(Plotter::Plot& plot) override;

    void UpdateAdaptiveRange();
    void UpdateAdaptiveRangeFigure(std::deque<double>& x, std::deque<double>& y, float& median, float curValue);
    void AddSliceGraphPoint(Graph3Set&& graph, double averageT, const Point& point);
    void UpdateAllTimeFixed();
    void UpdateMinMaxFixed();
    void UpdateTrend(const Plotter::GraphParameters& graph, Plotter::GraphParameters& trend);

    Point m_curMedian{ 0, 0, 0 };

    std::vector<Point> m_lastPoints;
    PointTransformer m_transformer;
    std::vector<Vector3> m_planeList;

    Plotter::GraphParameters m_trendY;
    Plotter::GraphParameters m_trendX;
    Plotter::GraphParameters m_trendZ;

    Plotter::GraphParameters m_sliceMinY;
    Plotter::GraphParameters m_sliceMinX;
    Plotter::GraphParameters m_sliceMinZ;

    Plotter::GraphParameters m_sliceMaxY;
    Plotter::GraphParameters m_sliceMaxX;
    Plotter::GraphParameters m_sliceMaxZ;

    Plotter::GraphParameters m_sliceMedianY;
    Plotter::GraphParameters m_sliceMedianZ;
    Plotter::GraphParameters m_sliceMedianX;

    Plotter::GraphParameters m_figureY;
    Plotter::GraphParameters m_figureX;
    Plotter::GraphParameters m_figureZ;

    constexpr static Key Calibrate{ 99, 67 };
    constexpr static Key Undo{ 85, 117 };
};
