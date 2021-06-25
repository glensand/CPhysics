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

#include "Interface/FigureProperties.h"
#include "Interface/Plot.h"
#include "Point.h"
#include "PointTransformer.h"
#include "../ITask.h"

class Stream;

enum class PlotStyle
{
    MinMaxFixed,
    AdaptiveRange,
    AllTimeFixed,
};

class ViveExplore : public ITask
{
    struct Graph3Set final
    {
        Plotter::GraphParameters& X;
        Plotter::GraphParameters& Y;
        Plotter::GraphParameters& Z;
    };

public:
    ViveExplore(PlotStyle style = PlotStyle::AdaptiveRange);
    virtual ~ViveExplore() override = default;

    virtual void Run(const Params* params = nullptr) override;
    void ClearPlot();
    virtual void Clear() override;
private:

    void ProcessKey(int keyCode);
    void RunStream();
    void StopStream();
    void ProcessNewPoint(std::size_t curIndex);
    void UpdateAdaptiveRange();
    void UpdateAdaptiveRangeFigure(std::deque<double>& x, std::deque<double>& y, float& median, float curValue);
    void AddSliceGraphPoint(Graph3Set&& graph, double averageT, const Point& point);
    void UpdateAllTimeFixed();
    void InitializeFigures(Plotter::Plot& plot);
    void RunDrawing();
    Plotter::GraphParameters GeneratePlotParameters() const;
    Plotter::GraphParameters GenerateSliceParameters(const Plotter::Color& color);

    std::thread m_pipeThread;
	Stream* m_stream{ nullptr };
    std::mutex m_mutex;
    bool m_added{ false };

    struct PointBuffer final
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

    Point m_curMedian{ 0, 0, 0 };

    std::vector<Point> m_lastPoints;
    Point m_lastPoint;
    PointTransformer m_transformer;
    std::vector<Vector3> m_planeList;

    Plotter::GraphParameters m_sliceMinY;
    Plotter::GraphParameters m_sliceMinX;
    Plotter::GraphParameters m_sliceMinZ;

    Plotter::GraphParameters m_sliceMaxY;
    Plotter::GraphParameters m_sliceMaxX;
    Plotter::GraphParameters m_sliceMaxZ;

    Plotter::GraphParameters m_sliceMedianY;
    Plotter::GraphParameters m_sliceMedianZ;
    Plotter::GraphParameters m_sliceMedianX;

    Plotter::GraphParameters m_figureY;
    Plotter::GraphParameters m_figureX;
    Plotter::GraphParameters m_figureZ;

    constexpr static std::size_t SpaceCode{ 32 };

    struct Key final
    {
        const int Key1;
        const int Key2;
        bool operator==(int key) const
        {
            return Key1 == key || Key2 == key;
        }
    };

    std::atomic_bool m_pipeActive;
    constexpr static Key Calibrate{ 99, 67 };
    constexpr static Key Undo{ 85, 117 };
    constexpr static Key Reset{ 82, 114 };
};
