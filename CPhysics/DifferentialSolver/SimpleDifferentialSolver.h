#pragma once

#include "../Solver/ISolver.h"
#include  <vector>
//Кажется, все - таки нужен другой  интерфейс.
//В ISolver метод солв возвращает Real,
//то есть одну цифру, а численное решение задачи Коши
//возвращает набор чисел - сетку и значения функции на каждом узле.



namespace CPhysics
{


struct SimpleDifferentialParams : Params
{
	Real					m_accuracy{ };
	Real					m_leftX{ };
	Real					m_rightX{ };
	Real					m_leftCond{ }; // U(m_leftX) where U is the solution of the differential equation 
	FunctionOfTwoArgs	m_function{ }; // the right half of standard simple differential equation dU/dX = f(x, U(x))
};



	
class ISimpleDifferentialSolver
{
public:
	ISimpleDifferentialSolver() = default;
	virtual	~ISimpleDifferentialSolver() = default;

	virtual bool SuitableParams(const Params * params) const;

	virtual std::string		GetSolverType() const = 0;

	virtual std::vector<std::pair<Real, Real>> Solve(const Params* params) const = 0;

	
};


	
}