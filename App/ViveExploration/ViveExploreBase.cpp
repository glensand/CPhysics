#include "ViveExploreBase.h"

#include <iomanip>
#include "CVPlot/CVPlot.h"
#include "Stream/TcpStream.h"

ViveExploreBase::ViveExploreBase(PlotStyle style)
    : m_style(style)
{

}

void ViveExploreBase::Clear()
{
    ClearPlot();
    m_pipeActive = false;
}

void ViveExploreBase::ProcessNewPoint(std::size_t curIndex)
{
    bool newAdded;
    {
        std::lock_guard lock(m_spin_lock);
        newAdded = m_added;
        m_lastPoint = *m_point.Front;
    }

    if(newAdded)
    {
        ProcessNewPointImpl(curIndex);
    }
}

Plotter::GraphParameters ViveExploreBase::GeneratePlotParameters() const
{
    Plotter::GraphParameters graphParams;
    graphParams.PointRadius = 1;
    graphParams.Style = m_style != PlotStyle::AllTimeFixed ? Plotter::PlotStyle::POINT_LINE : Plotter::PlotStyle::LINE;
    graphParams.Color = Plotter::Color{ 255, 0, 0 };
    graphParams.UseDeque = m_style != PlotStyle::AllTimeFixed;

    return graphParams;
}

Plotter::GraphParameters ViveExploreBase::GenerateSliceParameters(const Plotter::Color& color)
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

void ViveExploreBase::RunDrawing()
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

void ViveExploreBase::Run(const Params* params)
{
    RunStream();
    RunDrawing();
    StopStream();
}

void ViveExploreBase::ProcessKey(int keyCode)
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

void ViveExploreBase::RunStream()
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
            
            std::lock_guard lock(m_spin_lock);
            m_point.Swap();
            m_added = true;
        }
    });
}

void ViveExploreBase::StopStream()
{
    m_pipeActive.store(false, std::memory_order_release);
    m_pipeThread.join();
    m_stream->Close(Stream::ClosingPolicy::ClearOperations);
    delete m_stream;
}
