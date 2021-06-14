/* Copyright (C) 2019 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include <opencv2/core.hpp>

#include "Interface/Plot.h"

namespace Plotter
{
class Figure;
struct Color;

class CvPlot final : public Plot
{
public:

	CvPlot() = default;
	virtual	~CvPlot() override = default;

	virtual const FigureList& CreateFigure(std::size_t cols, std::size_t rows) override;
    virtual void Show(bool waitKey = true) override;
	virtual void Close() override;
	virtual void Clear() override;

	virtual void EnableDebugPrint(bool enable) override{ m_debugPrint = enable; }
    virtual int	 GetLastKey() const override { return m_lastKey; }

private:
	void Present(bool waitKey);
	static void OnMouseHandle(int event, int x, int y, int, void* instance);
	void OnMouseHandleInner(int event, int x, int y);

    const std::string m_plotName { "Plot" };
	const cv::Size m_plotSize{ 1400, 800 };
	const cv::Scalar m_defaultBackgroundColor{ 255, 255, 255 };
	const int m_borderSize{ 15 };

	FigureList m_figures;

	cv::Mat m_plot;

	int m_lastKey;
	bool m_debugPrint{ false };
};

}

