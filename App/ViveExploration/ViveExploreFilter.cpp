#include "ViveExploreFilter.h"

#include "CvPlot/CvPlot.h"
#include "Interface/Figure.h"

void ViveExploreFilter::ClearPlot()
{
    m_figureY = GeneratePlotParameters();
    m_figureYFiltered = GeneratePlotParameters();
}

ViveExploreFilter::ViveExploreFilter(PlotStyle style)
    : ViveExploreBase(style)
{
    ViveExploreFilter::Clear();
}

void ViveExploreFilter::ProcessNewPointImpl(std::size_t curIndex)
{
    // TODO:: implementation
}

void ViveExploreFilter::InitializeFigures(Plotter::Plot& plot)
{
    auto&& figures = plot.CreateFigure(1, 3);
    auto* figure1 = figures[0];
    auto* figure2 = figures[1];
   
    Plotter::GridProperties grid;
    grid.DrawAxis = false;
    grid.PrintRange = true;

    grid.FunctionName = "Y axis";
    figure1->SetGridProperties(grid);

    grid.FunctionName = "Y axis filtered";
    figure2->SetGridProperties(grid);

    figure1->AddGraph(&m_figureY);
    figure2->AddGraph(&m_figureYFiltered);
}

void ViveExploreFilter::ProcessKeyImpl(int keyCode)
{

}
