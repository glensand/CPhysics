#include "ViveExploreFilter.h"

#include "CvPlot/CvPlot.h"
#include "Interface/Figure.h"

void ViveExploreFilter::ClearPlot()
{
    m_filteredFigureX = GeneratePlotParameters({ 0, 0, 255 });
    m_filteredFigureY = GeneratePlotParameters({ 0, 0, 255 });
    m_filteredFigureZ = GeneratePlotParameters({ 0, 0, 255 });

    m_figureX = GeneratePlotParameters();
    m_figureY = GeneratePlotParameters();
    m_figureZ = GeneratePlotParameters();
}

ViveExploreFilter::ViveExploreFilter()
    : ViveExploreBase(PlotStyle::AdaptiveRange)
    , m_x(0.0000001, 0.001)
    , m_y(0.000001, 0.0001)
    , m_z(0.00001, 0.001)
{
    ViveExploreFilter::Clear();
}

void ViveExploreFilter::ProcessNewPointImpl(std::size_t curIndex)
{
    if(m_figureX.DequeX.empty())
    {
        m_x.SetState(m_lastPoint.x, 0.1);
        m_y.SetState(m_lastPoint.y, 0.1);
        m_z.SetState(m_lastPoint.z, 0.1);
    }

    m_x.Correct(m_lastPoint.x);
    m_y.Correct(m_lastPoint.y);
    m_z.Correct(m_lastPoint.z);

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

    UpdateAdaptiveRangeFigure(
        m_filteredFigureX.DequeX, m_filteredFigureX.DequeY,
        m_curMedian.x, m_x.GetState()
    );

    UpdateAdaptiveRangeFigure(
        m_filteredFigureY.DequeX, m_filteredFigureY.DequeY,
        m_curMedian.y, m_y.GetState()
    );

    UpdateAdaptiveRangeFigure(
        m_filteredFigureZ.DequeX, m_filteredFigureZ.DequeY,
        m_curMedian.z, m_z.GetState()
    );
}

void ViveExploreFilter::InitializeFigures(Plotter::Plot& plot)
{
    auto&& figures = plot.CreateFigure(1, 3);
    auto* figure1 = figures[0];
    auto* figure2 = figures[1];
    auto* figure3 = figures[2];
   
    figure1->AddGraph(&m_figureX);
    figure1->AddGraph(&m_filteredFigureX);

    figure2->AddGraph(&m_figureY);
    figure2->AddGraph(&m_filteredFigureY);

    figure3->AddGraph(&m_figureZ);
    figure3->AddGraph(&m_filteredFigureZ);

    Plotter::GridProperties grid;
    grid.DrawAxis = false;
    grid.PrintRange = true;

    grid.FunctionName = "X pos";
    figure1->SetGridProperties(grid);

    grid.FunctionName = "Y pos";
    figure2->SetGridProperties(grid);

    grid.FunctionName = "Z pos";
    figure3->SetGridProperties(grid);
}

void ViveExploreFilter::ProcessKeyImpl(int keyCode)
{

}
