/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include <thread>
#include "hope/concurrency/spin_lock.h"

#include "Interface/FigureProperties.h"
#include "Interface/Plot.h"
#include "Point.h"
#include "ITask.h"

class Stream;

enum class PlotStyle
{
    MinMaxFixed,
    AdaptiveRange,
    AllTimeFixed,
    SlippingAverage,
};

class ViveExploreBase : public ITask
{
public:
    ViveExploreBase(PlotStyle style = PlotStyle::AdaptiveRange);
    virtual ~ViveExploreBase() override = default;

    virtual void Run(const Params* params = nullptr) override final;
    virtual void Clear() override final;

protected:
    virtual void ClearPlot() = 0;
    virtual void ProcessKeyImpl(int keyCode) = 0;
    virtual void ProcessNewPointImpl(std::size_t index) = 0;
    virtual void InitializeFigures(Plotter::Plot& plot) = 0;

    Plotter::GraphParameters GeneratePlotParameters() const;
    Plotter::GraphParameters GenerateSliceParameters(const Plotter::Color& color);

    struct Key final
    {
        const int Key1;
        const int Key2;
        bool operator==(int key) const
        {
            return Key1 == key || Key2 == key;
        }
    };

    Point m_lastPoint;
    PlotStyle m_style;

private:
    void ProcessKey(int key);
    void RunStream();
    void StopStream();
    void ProcessNewPoint(std::size_t curIndex);
    void RunDrawing();

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

    PointBuffer m_point;
    hope::concurrency::spin_lock m_spin_lock;
    std::atomic_bool m_pipeActive;
    std::thread m_pipeThread;
    Stream* m_stream{ nullptr };
    bool m_added{ false };

    constexpr static std::size_t SpaceCode{ 32 };
    constexpr static Key Reset{ 82, 114 };
};
