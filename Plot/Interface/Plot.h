/* Copyright (C) 2021 Gleb Bezborodov - All Rights Reserved
 * You may use, distribute and modify this code under the
 * terms of the MIT license.
 *
 * You should have received a copy of the MIT license with
 * this file. If not, please write to: bezborodoff.gleb@gmail.com, or visit : https://github.com/glensand/CPhysics
 */

#pragma once

#include <vector>

namespace Plotter
{

class Figure;

class Plot
{
public:
	using FigureList = std::vector<Figure*>;

	Plot() = default;
	virtual  ~Plot() = default;

	virtual const FigureList& CreateFigure(std::size_t col, std::size_t rows) = 0;

	virtual void Show(bool waitKey = true) = 0;
	virtual void Clear() = 0;
	virtual void Close() = 0;

	virtual void EnableDebugPrint(bool enable) = 0;
	virtual int	 GetLastKey() const = 0;
};

}

