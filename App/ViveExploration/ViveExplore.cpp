#include "ViveExplore.h"

#include <iomanip>
#include <numeric>

#include "Pipe.h"
#include "CVPlot/CvPlot.h"
#include "Interface/Figure.h"

namespace
{

constexpr std::size_t PointsCount{ 1000 };
constexpr std::size_t IndexBeginCompare{ 3000 };
constexpr std::size_t PointToAverageCount{ 100 };

}

ViveExplore::ViveExplore(PlotStyle style)
    : m_style(style)
{
    m_sliceMinY = GenerateSliceParameters({ 0, 255, 0 });
    m_sliceMedianY = GenerateSliceParameters({ 0, 0, 0 });
    m_sliceMaxY = GenerateSliceParameters({ 0, 0, 255 });
    m_figureY = GeneratePlotParameters();
    m_pipeActive = false;
    m_lastPoints.reserve(PointToAverageCount);
}

void ViveExplore::ProcessNewPoint(std::size_t curIndex)
{
    bool newAdded;
    {
        std::lock_guard lock(mu);
        newAdded = added;
        m_lastPoint = *m_point.Front;
    }

    if(newAdded)
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
        else
            UpdateAdaptiveRange(curIndex);
    }
}

void ViveExplore::UpdateAdaptiveRange(std::size_t curIndex)
{
    auto pYMm = m_lastPoint.y * 1000;
    auto frontX = m_figureX.DequeY.front();
    auto frontY = m_figureY.DequeY.front();
    auto frontZ = m_figureZ.DequeY.front();

    m_figureY.DequeX.pop_front();
    m_figureY.DequeY.pop_front();
    m_curMedianY += m_lastPoint.y;
    m_curMedianY -= frontY / 1000;

    m_figureY.DequeX.push_back((double)m_lastPoint.time);
    m_figureY.DequeY.push_back(pYMm);

    if (curIndex > IndexBeginCompare)
    {
        if (pYMm < m_curMin)
            m_curMin = pYMm;

        if (m_curMax < pYMm)
            m_curMax = pYMm;
    }
    else
    {
        m_curMax = m_curMin = m_curMedianY;
    }

    m_sliceMinY.Y[0] = m_sliceMinY.Y[1] = (double)m_curMin;
    m_sliceMaxY.Y[0] = m_sliceMaxY.Y[1] = (double)m_curMax;
    m_sliceMedianY.Y[0] = m_sliceMedianY.Y[1] = (double)m_curMedianY;
    m_sliceMinY.X[0] = m_sliceMaxY.X[0] = m_sliceMedianY.X[0] = m_figureY.DequeX.front();
    m_sliceMinY.X[1] = m_sliceMaxY.X[1] = m_sliceMedianY.X[1] = m_figureY.DequeX.back();
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

Plotter::GraphParameters ViveExplore::GeneratePlotParameters()
{
    Plotter::GraphParameters graphParams;
    graphParams.PointRadius = 1;
    graphParams.Style = m_style != PlotStyle::AllTimeFixed ? Plotter::PlotStyle::POINT_LINE : Plotter::PlotStyle::LINE;
    graphParams.Color = Plotter::Color{ 255, 0, 0 };
    graphParams.UseDeque = m_style != PlotStyle::AllTimeFixed;

    if(m_style != PlotStyle::AllTimeFixed)
    {
        graphParams.DequeX.resize(PointsCount, 0);
        graphParams.DequeY.resize(PointsCount, 0);
    }

    return graphParams;
}

Plotter::GraphParameters ViveExplore::GenerateSliceParameters(const Plotter::Color& color)
{
    Plotter::GraphParameters sliceParameters;
    sliceParameters.Style = Plotter::PlotStyle::LINE;
    sliceParameters.Color = color;

    if(m_style != PlotStyle::AllTimeFixed)
    {
        sliceParameters.LineThickness = 2;
        sliceParameters.X.resize(2, 0);
        sliceParameters.Y.resize(2, 0);
    }
    
    return sliceParameters;
}

void ViveExplore::InitializeFigures(Plotter::Plot& plot)
{
    auto&& figures = plot.CreateFigure(1, 3);
    auto* figure1 = figures[0];
    auto* figure2 = figures[0];
    auto* figure3 = figures[0];

    if(m_style == PlotStyle::MinMaxFixed || m_style == PlotStyle::AllTimeFixed)
    {
        figure1->AddGraph(&m_sliceMaxX);
        figure1->AddGraph(&m_sliceMinX);

        figure2->AddGraph(&m_sliceMaxY);
        figure2->AddGraph(&m_sliceMinY);

        figure3->AddGraph(&m_sliceMaxZ);
        figure3->AddGraph(&m_sliceMinZ);
    }

    if(m_style != PlotStyle::AllTimeFixed)
    {
        figure1->AddGraph(&m_sliceMedianX);
        figure2->AddGraph(&m_sliceMedianY);
        figure3->AddGraph(&m_sliceMedianZ);
    }

    figure1->AddGraph(&m_figureX);
    figure2->AddGraph(&m_figureY);
    figure3->AddGraph(&m_figureZ);
}

void ViveExplore::RunDrawing()
{
    Plotter::CvPlot plot;

    InitializeFigures(plot);

    std::size_t curIndex{ 0 };
    int lastKey = 0;
    while (lastKey != SpaceCode)
    {
        ProcessKey(lastKey);
        ProcessNewPoint(curIndex);
        curIndex++;
        plot.Show(false);
        lastKey = plot.GetLastKey();
    }

    plot.Close();
}

void ViveExplore::Run(const Params* params)
{
    RunPipeThread();
    RunDrawing();
    StopPipeThread();
}

void ViveExplore::ProcessKey(int keyCode)
{
    if(Calibrate == keyCode)
    {
        m_planeList.emplace_back(m_lastPoint.x, m_lastPoint.y, m_lastPoint.z);

        if(m_planeList.size() == 3)
        {
            m_transformer.Initialize(m_planeList);
            m_planeList.clear();
        }
    }
}

void ViveExplore::RunPipeThread()
{
    pipe = new Pipe();
    m_pipeActive.store(true);
    pipeThread = std::thread([this]
    {
        while(m_pipeActive.load(std::memory_order_acquire))
        {
            m_point.Back->x = pipe->Read<float>();
            m_point.Back->y = pipe->Read<float>();
            m_point.Back->z = pipe->Read<float>();
            m_point.Back->time = pipe->Read<float>();
            std::lock_guard lock(mu);
            m_point.Swap();
            added = true;
        }
    });
}

void ViveExplore::StopPipeThread()
{
    m_pipeActive.store(false, std::memory_order_release);
    pipeThread.join();
}
