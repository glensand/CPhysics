/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include "ViveExploration/ViveExploreBase.h"

class ViveExploreFilter final : public ViveExploreBase
{
public:
    ViveExploreFilter(PlotStyle style = PlotStyle::AdaptiveRange);
    virtual ~ViveExploreFilter() override = default;
    
private:
	virtual void ClearPlot() override;
    virtual void ProcessKeyImpl(int keyCode) override;
    virtual void ProcessNewPointImpl(std::size_t curIndex) override;
    virtual void InitializeFigures(Plotter::Plot& plot) override;

    Plotter::GraphParameters m_figureY;
    Plotter::GraphParameters m_figureYFiltered;
};
