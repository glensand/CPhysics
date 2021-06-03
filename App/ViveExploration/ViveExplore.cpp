#include "ViveExplore.h"
#include "Pipe.h"
#include "CVPlot/CVPlot.h"

void ViveExplore::Run(const Params* params)
{
    RunPipeThread();

    Plotter::CVPlot plot;
    Plotter::GraphParams graphParams;
    graphParams.PointRadius = 2;
    graphParams.Style = Plotter::PlotStyle::POINT_LINE;
    graphParams.Color = Plotter::Color{0, 0, 255};

    graphParams.UseDeque = true;

    plot.AddGraph(&graphParams);

    auto start = std::chrono::high_resolution_clock::now();

    while (true)
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto&& deltaTime = (double)std::chrono::duration_cast<std::chrono::microseconds>(now - start).count() / 100000.0;
        Point point{};
        if(!hasNewPoint.test_and_set())
        {
            point = newPoint.load();
            if (graphParams.DequeX.size() > 40)
            {
                graphParams.DequeX.pop_front();
                graphParams.DequeY.pop_front();
            }
            
            graphParams.DequeX.push_back(deltaTime);
            graphParams.DequeY.push_back((double)point.x);
        }

        plot.Show(false);
    }
}

void ViveExplore::RunPipeThread()
{
    pipe = new Pipe();
    pipeThread = std::thread([this]
        {
            while(true)
            {
                auto&& point = pipe->Read<Point>();
                hasNewPoint.test_and_set();
                newPoint.store(point);
                hasNewPoint.clear();
            }
        });
}
