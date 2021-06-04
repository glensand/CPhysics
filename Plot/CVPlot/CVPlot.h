/* Copyright (C) 2019 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>

#include "../IPlot.h"

#include <string>
#include <set>

namespace Plotter
{

struct FontProperties final
{
	double		Scale{ .4 };
	int			Type{ cv::HersheyFonts::FONT_HERSHEY_SIMPLEX };
	cv::Scalar	Color{ 0, 0, 0 };
};

struct AxisProperties final
{
	cv::Scalar	Color {0, 0, 0};
	int			Thickness{ 2 };
};

class CVPlot final : public IPlot
{
	using GraphList = std::vector<const GraphParameters*>;
public:

				CVPlot() = default;
	virtual		~CVPlot() override = default;

	virtual void AddGraph(const GraphParameters* params) override;
	virtual void Release() override;
    virtual void Show(bool waitKey = true) override;
	virtual void Close() override;
	virtual void Clear() override;
	virtual void SetGridProperties(const GridProperties& gridProperties) override;
	// own methods
	void			EnableDebugPrint(bool enable) { m_debugPrint = enable; }
private:
	void			Present(bool waitKey);
	void			Initialize();
	void			DrawAxis();
	void			DrawGrid();
	void			DrawHorizonLineCoordinate(int yPos, int lineIndex);
	void			DrawVerticalLineCoordinate(int xPos, int lineIndex);
	void			DrawPlots();
	void			DrawLabels();
	void			Print(const std::string &text, int x, int y);
	Color			GenerateColorRand();
	cv::Scalar		DeduceColor(const Color &color);
	static void		OnMouseHandle(int event, int x, int y, int, void* instance);
	void			OnMouseHandleInner(int event, int x, int y);
	std::string		Format(float value) const;

	template<typename TContainer>
    void InitializeMinMax(const TContainer& x, const TContainer& y);

    std::string m_plotName { "Plot" };
	cv::Mat m_plot;
	cv::Size m_plotSize{ 1300, 700 };
	cv::Scalar m_defaultBackgroundColor{ 255, 255, 255 };

	const int m_borderSize{ 65 };

	float m_minX{ 0 };
	float m_maxX{ 0 };
	float m_minY{ FLT_MAX };
	float m_maxY{ FLT_MIN };

	float m_scaleY{ 1.f };
	float m_scaleX{ 1.f };

    bool m_debugPrint{ false };
	
	GraphList m_graphs;
	AxisLabels m_labels;
	GridProperties m_gridProperties;
	std::set<Color> m_usedColors;
};

}

