/* Copyright (C) 2019 - 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

namespace Plotter
{

struct GraphParameters;
struct GridProperties;

class Figure
{
public:

	Figure() = default;
	virtual  ~Figure() = default;

	virtual void	AddGraph(const GraphParameters* params) = 0;
	virtual void	SetGridProperties(const GridProperties& gridProperties) = 0;
	virtual void	Show() = 0;
};

}

