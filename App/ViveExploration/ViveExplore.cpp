#include "ViveExplore.h"

#include <iomanip>
#include <iostream>

#include "Pipe.h"
#include "CVPlot/CVPlot.h"

namespace
{

Plotter::GraphParameters GenerateSliceParams(const Plotter::Color& color)
{
    Plotter::GraphParameters sliceParameters;
    sliceParameters.Style = Plotter::PlotStyle::LINE;
    sliceParameters.Color = color;
    sliceParameters.LineThickness = 2;
    sliceParameters.X.resize(2, 0);
    sliceParameters.Y.resize(2, 0);

    return sliceParameters;
}

}

ViveExplore::ViveExplore(bool useMinMax)
    : m_useMinMax(useMinMax)
{

}

void ViveExplore::Run(const Params* params)
{
    RunPipeThread();

    Plotter::CVPlot plot;

    auto&& sliceMin = GenerateSliceParams({ 0, 255, 0 });
    auto&& sliceMedian = GenerateSliceParams({ 0, 0, 0 });
    auto&& sliceMax = GenerateSliceParams({ 0, 0, 255 });

    Plotter::GraphParameters graphParamsY;
    graphParamsY.PointRadius = 1;
    graphParamsY.Style = Plotter::PlotStyle::POINT_LINE;
    graphParamsY.Color = Plotter::Color{ 255, 0, 0 };
    graphParamsY.UseDeque = true;
    graphParamsY.DequeX.resize(1000, 0);
    graphParamsY.DequeY.resize(1000, 0);

    Plotter::GridProperties gridProperties;
    gridProperties.HorizonLinesCount = 20;
    plot.SetGridProperties(gridProperties);

    if(m_useMinMax)
    {
        plot.AddGraph(&sliceMax);
        plot.AddGraph(&sliceMin);
    }

    plot.AddGraph(&sliceMedian);
    plot.AddGraph(&graphParamsY);

    float curMin{ FLT_MAX };
    float curMax{ FLT_MIN };
    float curMedian{ 0 };

    float localMin{ FLT_MAX };
    float localMax{ FLT_MIN };

    std::size_t curIndex{ 0 };
    constexpr std::size_t IndexBeginCompare{ 3000 };

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
            auto front = graphParamsY.DequeY.front();

            graphParamsY.DequeX.pop_front();
            graphParamsY.DequeY.pop_front();
            curMedian += p.y;
            curMedian -= front / 1000;

            auto pYMm = p.y * 1000;

            graphParamsY.DequeX.push_back((double)p.time);
            graphParamsY.DequeY.push_back(pYMm);
            
            if (curIndex > IndexBeginCompare)
            {
                if (pYMm < curMin)
                    curMin = pYMm;

                if (curMax < pYMm)
                    curMax = pYMm;

                if (std::abs(front - localMin) < DBL_EPSILON)
                {
                    localMin = *std::min_element(std::begin(graphParamsY.DequeY), std::end(graphParamsY.DequeY));
                }
                else
                {
                    if (pYMm < localMin)
                        localMin = pYMm;
                }

                if (std::abs(front - localMax) < DBL_EPSILON)
                {
                    localMax = *std::max_element(std::begin(graphParamsY.DequeY), std::end(graphParamsY.DequeY));
                }
                else
                {
                    if (pYMm > localMax)
                        localMax = pYMm;
                }
            }
            else
            {
                curMax = curMin = curMedian;
                localMax = localMin = curMedian;
            }

            system("cls");

//            std::cout << std::string(100, '\n');
            //std::cout << "Global Min: " << std::setprecision(6) << curMin << std::endl;
            //std::cout << "Global Max: " << std::setprecision(6) << curMax << std::endl;
            //std::cout << "Global Diff: " << std::setprecision(6) << curMax - curMin << std::endl;

            //std::cout << "Last 1000 points Min: " << std::setprecision(6) << localMin << std::endl;
            //std::cout << "Last 1000 points Max: " << std::setprecision(6) << localMax << std::endl;
            //std::cout << "Last 1000 points Diff: " << std::setprecision(6) << localMax - localMin << std::endl;

            sliceMin.Y[0] = sliceMin.Y[1] = (double)curMin;
            sliceMax.Y[0] = sliceMax.Y[1] = (double)curMax;
            sliceMedian.Y[0] = sliceMedian.Y[1] = (double)curMedian;
            sliceMin.X[0] = sliceMax.X[0] = sliceMedian.X[0] = graphParamsY.DequeX.front();
            sliceMin.X[1] = sliceMax.X[1] = sliceMedian.X[1] = graphParamsY.DequeX.back();

            ++curIndex;
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
