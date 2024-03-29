#include "ViveExplore.h"

#include <numeric>
#include <iostream>

#include "CvPlot/CvPlot.h"
#include "Interface/Figure.h"

namespace
{

constexpr unsigned PointToAverageCount{ 100 };
constexpr unsigned PointToTrendLine{ 100 };

}

ViveExplore::ViveExplore(PlotStyle style)
    : ViveExploreBase(style)
{
    ViveExplore::Clear();
}

void ViveExplore::ClearPlot()
{
    m_sliceMinX = GenerateSliceParameters({ 0, 255, 0 });
    m_sliceMedianX = GenerateSliceParameters({ 0, 0, 0 });
    m_sliceMaxX = GenerateSliceParameters({ 0, 0, 255 });

    m_sliceMinY = GenerateSliceParameters({ 0, 255, 0 });
    m_sliceMedianY = GenerateSliceParameters({ 0, 0, 0 });
    m_sliceMaxY = GenerateSliceParameters({ 0, 0, 255 });

    m_sliceMinZ = GenerateSliceParameters({ 0, 255, 0 });
    m_sliceMedianZ = GenerateSliceParameters({ 0, 0, 0 });
    m_sliceMaxZ = GenerateSliceParameters({ 0, 0, 255 });

    m_trendX = GenerateSliceParameters({ 0, 0, 255 });
    m_trendY = GenerateSliceParameters({ 0, 0, 255 });
    m_trendZ = GenerateSliceParameters({ 0, 0, 255 });

    m_figureX = GeneratePlotParameters();
    m_figureY = GeneratePlotParameters();
    m_figureZ = GeneratePlotParameters();

    m_curMedian = Point{ 0, 0,0 };

    m_lastPoints.clear();
    m_lastPoints.reserve(PointToAverageCount);
}

void ViveExplore::ProcessNewPointImpl(std::size_t curIndex)
{
    if(m_transformer.IsInitialized())
    {
        auto&& transformed = m_transformer.Transform(
            Vector3(m_lastPoint.x, m_lastPoint.y, m_lastPoint.z)
        );
        m_lastPoint.x = transformed[0];
        m_lastPoint.y = transformed[1];
        m_lastPoint.z = transformed[2];
    }

    if (m_style == PlotStyle::AllTimeFixed)
        UpdateAllTimeFixed();
    else if (m_style == PlotStyle::AdaptiveRange)
        UpdateAdaptiveRange();
    else
        UpdateMinMaxFixed();
    
}

void ViveExplore::UpdateAdaptiveRange()
{
    UpdateAdaptiveRangeFigure(
        m_figureX.DequeX, m_figureX.DequeY,
        m_curMedian.x, m_lastPoint.x
    );

    UpdateAdaptiveRangeFigure(
        m_figureY.DequeX, m_figureY.DequeY,
        m_curMedian.y, m_lastPoint.y
    );

    UpdateAdaptiveRangeFigure(
        m_figureZ.DequeX, m_figureZ.DequeY,
        m_curMedian.z, m_lastPoint.z
    );

    m_sliceMedianX.X[0] = m_sliceMedianY.X[0] = m_sliceMedianZ.X[0] = m_figureX.DequeX.front();
    m_sliceMedianX.X[1] = m_sliceMedianY.X[1] = m_sliceMedianZ.X[1] = m_figureX.DequeX.back();

    m_sliceMedianX.Y[0] = m_sliceMedianX.Y[1] = m_curMedian.x;
    m_sliceMedianY.Y[0] = m_sliceMedianY.Y[1] = m_curMedian.y;
    m_sliceMedianZ.Y[0] = m_sliceMedianZ.Y[1] = m_curMedian.z;
}

void ViveExplore::AddSliceGraphPoint(Graph3Set&& graph, double averageT, const Point& point)
{
    graph.X.X.push_back(averageT);
    graph.X.Y.push_back(1000 * point.x);
    graph.Y.X.push_back(averageT);
    graph.Y.Y.push_back(1000 * point.y);
    graph.Z.X.push_back(averageT);
    graph.Z.Y.push_back(1000 * point.z);
}

void ViveExplore::UpdateAllTimeFixed()
{
    m_lastPoints.emplace_back(m_lastPoint);

    if(m_lastPoints.size() == PointToAverageCount)
    {
        double sumX = 0;
        double sumY = 0;
        double sumZ = 0;
        double sumT = 0;

        for(auto&& point : m_lastPoints)
        {
            sumT += point.time;
            sumX += point.x;
            sumY += point.y;
            sumZ += point.z;
        }

        auto&& averageT = sumT / PointToAverageCount;

        auto&& [minX, maxX] = std::minmax_element(std::begin(m_lastPoints), std::end(m_lastPoints),
            [](const Point& p1, const Point& p2) { return p1.x < p2.x; });

        auto&& [minY, maxY] = std::minmax_element(std::begin(m_lastPoints), std::end(m_lastPoints),
            [](const Point& p1, const Point& p2) { return p1.y < p2.y; });

        auto&& [minZ, maxZ] = std::minmax_element(std::begin(m_lastPoints), std::end(m_lastPoints),
            [](const Point& p1, const Point& p2) { return p1.z < p2.z; });

        auto&& maxPoint = Point{ maxX->x, maxY->y, maxZ->z };
        AddSliceGraphPoint({ m_sliceMaxX, m_sliceMaxY, m_sliceMaxZ }, averageT, maxPoint);

        auto&& minPoint = Point{ minX->x, minY->y, minZ->z };
        AddSliceGraphPoint({ m_sliceMinX, m_sliceMinY, m_sliceMinZ }, averageT, minPoint);

        auto&& figurePoint = Point{ (float)sumX / PointToAverageCount , (float)sumY / PointToAverageCount, (float)sumZ / PointToAverageCount };
        AddSliceGraphPoint({ m_figureX, m_figureY, m_figureZ}, averageT, figurePoint);
       
        m_lastPoints.clear();
    }
}

void ViveExplore::UpdateMinMaxFixed()
{
    m_figureX.DequeX.emplace_back(m_lastPoint.time);
    m_figureY.DequeX.emplace_back(m_lastPoint.time);
    m_figureZ.DequeX.emplace_back(m_lastPoint.time);

    m_figureX.DequeY.emplace_back(m_lastPoint.x * 1000);
    m_figureY.DequeY.emplace_back(m_lastPoint.y * 1000);
    m_figureZ.DequeY.emplace_back(m_lastPoint.z * 1000);

    if(m_style == PlotStyle::SlippingAverage)
    {
        UpdateTrend(m_figureX, m_trendX);
        UpdateTrend(m_figureY, m_trendY);
        UpdateTrend(m_figureZ, m_trendZ);
    }
}

void ViveExplore::UpdateTrend(const Plotter::GraphParameters& graph, Plotter::GraphParameters& trend)
{
    if (m_figureZ.DequeX.size() > PointToTrendLine)
    {
        auto PointsToPoint{ unsigned((double)m_figureZ.DequeX.size() / 4) };

        double sum = 0;
        for (unsigned i = 0; i < PointsToPoint; ++i)
            sum += graph.DequeY[i];
        trend.Y[0] = sum / PointsToPoint;

        double sum2 = 0;
        for (unsigned i = graph.DequeY.size() - PointsToPoint; i < graph.DequeY.size(); ++i)
            sum2 += graph.DequeY[i];
        trend.Y[1] = sum2 / PointsToPoint;
    }
    else
    {
        trend.Y[0] = graph.DequeY.front();
        trend.Y[1] = graph.DequeY.back();
    }

    trend.X[0] = graph.DequeX.front();
    trend.X[1] = graph.DequeX.back();
}

void ViveExplore::InitializeFigures(Plotter::Plot& plot)
{
    auto&& figures = plot.CreateFigure(1, 3);
    auto* figure1 = figures[0];
    auto* figure2 = figures[1];
    auto* figure3 = figures[2];

    if(m_style == PlotStyle::AllTimeFixed)
    {
        figure1->AddGraph(&m_sliceMaxX);
        figure1->AddGraph(&m_sliceMinX);

        figure2->AddGraph(&m_sliceMaxY);
        figure2->AddGraph(&m_sliceMinY);

        figure3->AddGraph(&m_sliceMaxZ);
        figure3->AddGraph(&m_sliceMinZ);
    }

    if(m_style == PlotStyle::AdaptiveRange)
    {
        figure1->AddGraph(&m_sliceMedianX);
        figure2->AddGraph(&m_sliceMedianY);
        figure3->AddGraph(&m_sliceMedianZ);
    }

    if(m_style == PlotStyle::SlippingAverage)
    {
        figure1->AddGraph(&m_trendX);
        figure2->AddGraph(&m_trendY);
        figure3->AddGraph(&m_trendZ);
    }

    Plotter::GridProperties grid;
    grid.DrawAxis = false;
    grid.PrintRange = true;

    grid.FunctionName = "X axis";
    figure1->SetGridProperties(grid);

    grid.FunctionName = "Y axis";
    figure2->SetGridProperties(grid);

    grid.FunctionName = "Z axis";
    figure3->SetGridProperties(grid);

    figure1->AddGraph(&m_figureX);
    figure2->AddGraph(&m_figureY);
    figure3->AddGraph(&m_figureZ);
}

void ViveExplore::ProcessKeyImpl(int keyCode)
{
    if(Calibrate == keyCode)
    {
        m_planeList.emplace_back(m_lastPoint.x, m_lastPoint.y, m_lastPoint.z);

        std::cout << "New point handled" << std::endl;

        if(m_planeList.size() == 3)
        {
            m_transformer.Initialize(m_planeList);
            m_planeList.clear();

            std::cout << "Calibrated" << std::endl; 
        }
    }
    else if(Undo == keyCode)
    {
        m_transformer.Deinitialize();
    }
}
