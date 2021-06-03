#include "ViveExplore.h"
#include "Pipe.h"
#include "CVPlot/CVPlot.h"

void ViveExplore::Run(const Params* params)
{
    RunPipeThread();

    Plotter::CVPlot plot;
    Plotter::GraphParameters graphParamsX;

    graphParamsX.PointRadius = 1;
    graphParamsX.Style = Plotter::PlotStyle::POINT_LINE;
    graphParamsX.Color = Plotter::Color{0, 0, 255};
    graphParamsX.UseDeque = true;

    Plotter::GraphParameters graphParamsY;
    graphParamsY.PointRadius = 1;
    graphParamsY.Style = Plotter::PlotStyle::POINT_LINE;
    graphParamsY.Color = Plotter::Color{ 255, 0, 0 };
    graphParamsY.UseDeque = true;

    Plotter::GraphParameters graphParamsZ;
    graphParamsZ.PointRadius = 1;
    graphParamsZ.Style = Plotter::PlotStyle::POINT_LINE;
    graphParamsZ.Color = Plotter::Color{ 0, 255, 0 };
    graphParamsZ.UseDeque = true;

    //plot.AddGraph(&graphParamsX);
    plot.AddGraph(&graphParamsY);
    //plot.AddGraph(&graphParamsZ);

    auto start = std::chrono::high_resolution_clock::now();

    while (true)
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto&& deltaTime = (double)std::chrono::duration_cast<std::chrono::microseconds>(now - start).count() / 100000.0;

        bool newAdded;
        Point p{ };
        {
            std::lock_guard lock(mu);
            newAdded = added;
            p = *point.Front;
        }

        if(newAdded)
        {
            if (graphParamsX.DequeX.size() > 1000)
            {
                graphParamsX.DequeX.pop_front();
                graphParamsX.DequeY.pop_front();

                graphParamsY.DequeX.pop_front();
                graphParamsY.DequeY.pop_front();

                graphParamsZ.DequeX.pop_front();
                graphParamsZ.DequeY.pop_front();
            }

            graphParamsX.DequeX.push_back(deltaTime);
            graphParamsX.DequeY.push_back(1000 * (double)p.x);

            graphParamsY.DequeX.push_back(deltaTime);
            graphParamsY.DequeY.push_back(1000 * (double)p.y);

            graphParamsZ.DequeX.push_back(deltaTime);
            graphParamsZ.DequeY.push_back(1000 * (double)p.z);
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

                point.Back->x = pipe->Read<float>();
                point.Back->y = pipe->Read<float>();
                point.Back->z = pipe->Read<float>();
                std::lock_guard lock(mu);
                point.Swap();
                added = true;
            }
        });
}
