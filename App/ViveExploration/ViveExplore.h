/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include <mutex>
#include <thread>

#include "IPlot.h"
#include "Point.h"
#include "../ITask.h"

class Pipe;

enum class PlotStyle
{
    MinMaxFixed,
    AdaptiveRange,
    AllTimeFixed,
};

class ViveExplore : public ITask
{
public:
    ViveExplore(PlotStyle style = PlotStyle::AdaptiveRange);
    virtual ~ViveExplore() override = default;

    virtual void Run(const Params* params = nullptr) override;
    virtual void Clear() override {}
private:

    void RunPipeThread();
    void ProcessNewPoint(std::size_t curIndex);
    void UpdateAdaptiveRange(std::size_t curIndex, const Point& p);
    void UpdateAllTimeFixed(std::size_t curIndex, const Point& p);
    Plotter::GraphParameters GeneratePlotParameters();
    Plotter::GraphParameters GenerateSliceParameters(const Plotter::Color& color);

    std::thread pipeThread;
	Pipe* pipe{ nullptr };
    std::mutex mu;
    bool added{ false };

    struct PointBuffer
    {
        Point Buffer1;
        Point Buffer2;

        Point* Front{ &Buffer1};
        Point* Back{ &Buffer2 };

        void Swap()
        {
            auto* temp = Front;
            Front = Back;
            Back = temp;
        }
    };

    PlotStyle m_style;
    PointBuffer m_point;

    float m_curMin{ FLT_MAX };
    float m_curMax{ FLT_MIN };
    float m_curMedian{ 0 };

    std::vector<Point> m_lastPoints;

    Plotter::GraphParameters m_sliceMin;
    Plotter::GraphParameters m_sliceMax;
    Plotter::GraphParameters m_sliceMedian;
    Plotter::GraphParameters m_figure;

    constexpr static std::size_t SpaceCode{ 32 };
};
