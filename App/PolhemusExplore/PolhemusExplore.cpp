#include "PolhemusExplore.h"

#include <iostream>

#include "CVPlot/CVPlot.h"
#include "Interface/Figure.h"

namespace PolhemusInput
{
#include "PolhemusInput/PolhemusInput.h"
}

namespace
{
constexpr std::size_t PointsCount = 1000;
}

PolhemusExplore::PolhemusExplore()
{
    ClearPlot();
    m_startTime = std::chrono::system_clock::now();
}

void PolhemusExplore::Clear()
{
    ClearPlot();
}

void PolhemusExplore::ClearPlot()
{
    m_figureX = GeneratePlotParameters();
    m_figureY = GeneratePlotParameters();
    m_figureZ = GeneratePlotParameters();
}

void PolhemusExplore::ProcessNewPoint(std::size_t curIndex)
{
    float dataArray[7];
    auto&& now = std::chrono::system_clock::now();
    PolhemusInput::GetPnO(0, dataArray, dataArray + 1, dataArray + 2, dataArray + 3, dataArray + 4, dataArray + 5, dataArray + 6);

    m_lastPoint.x = dataArray[0];
    m_lastPoint.y = dataArray[1];
    m_lastPoint.z = dataArray[2];
    const std::chrono::duration<double> delta = now - m_startTime;
    m_lastPoint.time = (float)delta.count();

    ProcessNewPointImpl(curIndex);
}

Plotter::GraphParameters PolhemusExplore::GeneratePlotParameters() const
{
    Plotter::GraphParameters graphParams;
    graphParams.PointRadius = 1;
    graphParams.Style = Plotter::PlotStyle::POINT_LINE;
    graphParams.Color = Plotter::Color{ 255, 0, 0 };
    graphParams.UseDeque = true;

    return graphParams;
}

void PolhemusExplore::RunDrawing()
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

void PolhemusExplore::ProcessNewPointImpl(std::size_t index)
{
    UpdateAdaptiveRangeFigure(m_figureX.DequeX, m_figureX.DequeY, m_lastPoint.x);
    UpdateAdaptiveRangeFigure(m_figureY.DequeX, m_figureY.DequeY, m_lastPoint.y);
    UpdateAdaptiveRangeFigure(m_figureZ.DequeX, m_figureZ.DequeY, m_lastPoint.z);
}

void PolhemusExplore::UpdateAdaptiveRangeFigure(std::deque<double>& x, std::deque<double>& y, float curValue)
{
    if (x.size() > PointsCount)
    {
        x.pop_front();
        y.pop_front();
    }

    x.push_back((double)m_lastPoint.time);
    y.push_back(curValue * 10); // cm -> mm
}

void PolhemusExplore::InitializeFigures(Plotter::Plot& plot)
{
    auto&& figures = plot.CreateFigure(1, 3);
    auto* figure1 = figures[0];
    auto* figure2 = figures[1];
    auto* figure3 = figures[2];

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

void PolhemusExplore::Run(const Params* params)
{
    auto err = PolhemusInput::Init();
    if(err != 0)
    {
        std::cout << "Error: " << err;
        return;
    }

    PolhemusInput::SetPosFilter();

    RunDrawing();

    PolhemusInput::Release();
}

void PolhemusExplore::ProcessKey(int keyCode)
{
    if(Reset == keyCode)
    {
        ClearPlot();
    }
    else
    {
        ProcessKeyImpl(keyCode);
    }
}
