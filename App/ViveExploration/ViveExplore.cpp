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
    m_sliceMin = GenerateSliceParameters({ 0, 255, 0 });
    m_sliceMedian = GenerateSliceParameters({ 0, 0, 0 });
    m_sliceMax = GenerateSliceParameters({ 0, 0, 255 });
    m_figure = GeneratePlotParameters();
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
    auto front = m_figure.DequeY.front();

    m_figure.DequeX.pop_front();
    m_figure.DequeY.pop_front();
    m_curMedian += m_lastPoint.y;
    m_curMedian -= front / 1000;

    m_figure.DequeX.push_back((double)m_lastPoint.time);
    m_figure.DequeY.push_back(pYMm);

    if (curIndex > IndexBeginCompare)
    {
        if (pYMm < m_curMin)
            m_curMin = pYMm;

        if (m_curMax < pYMm)
            m_curMax = pYMm;
    }
    else
    {
        m_curMax = m_curMin = m_curMedian;
    }

    m_sliceMin.Y[0] = m_sliceMin.Y[1] = (double)m_curMin;
    m_sliceMax.Y[0] = m_sliceMax.Y[1] = (double)m_curMax;
    m_sliceMedian.Y[0] = m_sliceMedian.Y[1] = (double)m_curMedian;
    m_sliceMin.X[0] = m_sliceMax.X[0] = m_sliceMedian.X[0] = m_figure.DequeX.front();
    m_sliceMin.X[1] = m_sliceMax.X[1] = m_sliceMedian.X[1] = m_figure.DequeX.back();
}

void ViveExplore::UpdateAllTimeFixed()
{
    m_lastPoints.emplace_back(m_lastPoint);

    if(m_lastPoints.size() == PointToAverageCount)
    {
        double sumY = 0;
        double sumT = 0;
        for(auto&& point : m_lastPoints)
        {
            sumT += point.time;
            sumY += point.y;
        }

        auto&& averageT = sumT / PointToAverageCount;
        auto&& [min, max] = std::minmax_element(std::begin(m_lastPoints), std::end(m_lastPoints),
            [](const Point& p1, const Point& p2) { return p1.y < p2.y; });
        m_sliceMax.X.push_back(averageT);
        
        m_sliceMax.Y.push_back(1000 * max->y);
        m_sliceMin.X.push_back(averageT);
        m_sliceMin.Y.push_back(1000 * min->y);
        m_figure.X.push_back(averageT);
        m_figure.Y.push_back(1000 * sumY / PointToAverageCount);

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

void ViveExplore::RunDrawing()
{
    Plotter::CvPlot plot;
    auto&& figures = plot.CreateFigure(1, 1);
    auto* figure1 = figures[0];
    Plotter::GridProperties gridProperties;
    gridProperties.HorizonLinesCount = 20;
    figure1->SetGridProperties(gridProperties);

    if(m_style == PlotStyle::MinMaxFixed || m_style == PlotStyle::AllTimeFixed)
    {
        figure1->AddGraph(&m_sliceMax);
        figure1->AddGraph(&m_sliceMin);
    }

    if(m_style != PlotStyle::AllTimeFixed)
    {
        figure1->AddGraph(&m_sliceMedian);
    }

    figure1->AddGraph(&m_figure);

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
