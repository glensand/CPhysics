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

    Plotter::GridProperties gridProperties;
    gridProperties.HorizonLinesCount = 20;
    plot.SetGridProperties(gridProperties);

    //plot.AddGraph(&graphParamsX);
    plot.AddGraph(&graphParamsY);
    //plot.AddGraph(&graphParamsZ);

    while (true)
    {
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

            graphParamsX.DequeX.push_back((double)p.time);
            graphParamsX.DequeY.push_back(1000 * (double)p.x);

            graphParamsY.DequeX.push_back((double)p.time);
            graphParamsY.DequeY.push_back(1000 * (double)p.y);

            graphParamsZ.DequeX.push_back((double)p.time);
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
                point.Back->time = pipe->Read<float>();
                std::lock_guard lock(mu);
                point.Swap();
                added = true;
            }
        });
}
