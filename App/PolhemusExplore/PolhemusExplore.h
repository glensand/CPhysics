/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include <chrono>

#include "ViveExploration/Point.h"
#include "Interface/FigureProperties.h"
#include "Interface/Plot.h"

#include "ITask.h"


class PolhemusExplore : public ITask
{
public:
    PolhemusExplore();
    virtual ~PolhemusExplore() override = default;

    virtual void Run(const Params* params = nullptr) override final;
    virtual void Clear() override final;

protected:
    virtual void ProcessKeyImpl(int keyCode) {}

    Plotter::GraphParameters GeneratePlotParameters() const;

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

private:
    void ClearPlot();
    void ProcessKey(int key);
    void ProcessNewPoint(std::size_t curIndex);
    void RunDrawing();
    void ProcessNewPointImpl(std::size_t index);
    void InitializeFigures(Plotter::Plot& plot);
    void UpdateAdaptiveRangeFigure(std::deque<double>& x, std::deque<double>& y, float curValue);

    Plotter::GraphParameters m_figureY;
    Plotter::GraphParameters m_figureX;
    Plotter::GraphParameters m_figureZ;

    std::chrono::time_point<std::chrono::system_clock> m_startTime;

    constexpr static std::size_t SpaceCode{ 32 };
    constexpr static Key Reset{ 82, 114 };
};

