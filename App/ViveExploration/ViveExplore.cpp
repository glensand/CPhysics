#include "ViveExplore.h"

#include <iomanip>
#include <iostream>
#include <numeric>

#include "CvPlot/CvPlot.h"
#include "Interface/Figure.h"
#include "Stream/TcpStream.h"

namespace
{

constexpr std::size_t PointsCount{ 1000 };
constexpr std::size_t PointToAverageCount{ 100 };

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

    m_figureX = GeneratePlotParameters();
    m_figureY = GeneratePlotParameters();
    m_figureZ = GeneratePlotParameters();

    m_curMedian = Point{ 0, 0,0 };

    m_lastPoints.reserve(PointToAverageCount);
}

void ViveExplore::Clear()
{
    ClearPlot();
    m_transformer.Deinitialize();
    m_pipeActive = false;
}

ViveExplore::ViveExplore(PlotStyle style)
    : m_style(style)
{
    ViveExplore::Clear();
}

void ViveExplore::ProcessNewPoint(std::size_t curIndex)
{
    bool newAdded;
    {
        std::lock_guard lock(m_mutex);
        newAdded = m_added;
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
            UpdateAdaptiveRange();
    }
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

void ViveExplore::UpdateAdaptiveRangeFigure(std::deque<double>& x, std::deque<double>& y, 
    float& median, float curValue)
{
    auto pYMm = curValue * 1000;

    if(x.size() < PointsCount)
    {
        median = median / (x.size() + 1) * x.size();
        median += pYMm / (x.size() > 0 ? x.size() : 1);
    }
    else
    {
        auto frontY = y.front();

        x.pop_front();
        y.pop_front();

        median += curValue;
        median -= frontY / 1000;
    }

    x.push_back((double)m_lastPoint.time);
    y.push_back(pYMm);
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

Plotter::GraphParameters ViveExplore::GeneratePlotParameters() const
{
    Plotter::GraphParameters graphParams;
    graphParams.PointRadius = 1;
    graphParams.Style = m_style != PlotStyle::AllTimeFixed ? Plotter::PlotStyle::POINT_LINE : Plotter::PlotStyle::LINE;
    graphParams.Color = Plotter::Color{ 255, 0, 0 };
    graphParams.UseDeque = m_style != PlotStyle::AllTimeFixed;

    //if(m_style != PlotStyle::AllTimeFixed)
    //{
    //    graphParams.DequeX.resize(PointsCount, 0);
    //    graphParams.DequeY.resize(PointsCount, 0);
    //}

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
    auto* figure2 = figures[1];
    auto* figure3 = figures[2];

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

    Plotter::GridProperties grid;
    grid.DrawAxis = false;

    for (auto&& figure : figures)
        figure->SetGridProperties(grid);

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
    RunStream();
    RunDrawing();
    StopStream();
}

void ViveExplore::ProcessKey(int keyCode)
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
    else if(Reset == keyCode && m_style == PlotStyle::AdaptiveRange)
    {
        ClearPlot();
    }
}

void ViveExplore::RunStream()
{
    m_stream = new TcpStream("localhost", 11488);

    m_stream->Connect();

    m_pipeActive.store(true);
    m_pipeThread = std::thread([this]
    {
        while(m_pipeActive.load(std::memory_order_acquire))
        {
            m_point.Back->x = m_stream->Read<float>();
            m_point.Back->y = m_stream->Read<float>();
            m_point.Back->z = m_stream->Read<float>();
            m_point.Back->time = m_stream->Read<float>();
            std::lock_guard lock(m_mutex);
            m_point.Swap();
            m_added = true;
        }
    });
}

void ViveExplore::StopStream()
{
    m_pipeActive.store(false, std::memory_order_release);
    m_pipeThread.join();
    m_stream->Close(Stream::ClosingPolicy::ClearOperations);
    delete m_stream;
}
