/* Copyright (C) 2019 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once
#include "../IPlot.h"

namespace Plotter
{
	
class CVPlot2 : public IPlot
{
public:
	
	CVPlot2() = default;
	virtual  ~CVPlot2() override = default;

	virtual void	AddGraph(const GraphParams* params) override;
	virtual void	Show(bool waitKey = true) override;
	virtual void	Release() override;
	virtual void	Close() override;
	virtual void	Clear() override{ }

private:
	
	//cv::Ptr<cv::plot::Plot2d>
};

}

