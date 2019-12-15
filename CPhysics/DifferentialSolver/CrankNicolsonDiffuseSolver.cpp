#include "CrankNicolsonDiffuseSolver.h"
#include <opencv2/core/mat.hpp >

namespace
{
std::vector<CPhysics::Real> mult(const cv::Mat &mat, const std::vector<CPhysics::Real> &bVec)
{
	std::vector<CPhysics::Real> bRes;
	bRes.reserve(bVec.size());

	for(size_t i{ 0 }; i < bVec.size(); ++i)
	{
		CPhysics::Real xn{ 0 };
		for (size_t j{ 0 }; j < bVec.size(); ++j)
		{
			xn += mat.at<CPhysics::Real>(i, j) * bVec[j];
		}

		bRes.emplace_back(xn);
	}

	return bRes;
}
	
}

namespace CPhysics
{
//------------------------------------------------------------------------------
IDifferentialSystemSolver::ReturnType CrankNicolsonDiffuseSolver::Solve(const Params* params) const
{
	if (!SuitableParams(params)) return ReturnType{};

	const auto cParams = reinterpret_cast<const CrankNicolsonDiffuseSolverParams*>(params);

	const Real q{ cParams->m_s / (cParams->m_h * cParams->m_h) };
	const auto &f = cParams->m_func;
	
	std::vector<Real> bVec;
	const size_t n{ static_cast<size_t>((cParams->m_rightX - cParams->m_leftX) / cParams->m_h) };
	bVec.reserve(n);

	for (Real x = cParams->m_leftX; x <= cParams->m_rightX + cParams->m_h; x += cParams->m_h)
		bVec.emplace_back(f(x));

	cv::Mat mat = cv::Mat::zeros(bVec.size(), bVec.size(), CV_64F);
	mat.at<Real>(0, 0) = 1.;
	mat.at<Real>(bVec.size() - 1, bVec.size() - 1) = 1.;

	for(size_t i { 0 }; i < bVec.size() - 2; ++i)
	{
		mat.at<Real>(i + 1, i + 1) = 1. + q;
		mat.at<Real>(i + 1, i + 2) = -q / 2.;
		mat.at<Real>(i + 1, i) = -q / 2.;
	}

	const cv::Mat inv = mat.inv();

	ReturnType resMat;
	resMat.reserve(static_cast<size_t>((cParams->m_t + cParams->m_s) / cParams->m_s));
	for(Real x { .0 }; x <= cParams->m_t + cParams->m_s; x += cParams->m_s)
	{
		resMat.emplace_back(bVec);
		for(size_t i { 1 }; i < bVec.size() - 1; ++i)
		{
			bVec[i] = bVec[i] + 0.5 * q * (bVec[i - 1] - 2 * bVec[i] + bVec[i + 1]);
		}

		bVec = mult(inv, bVec);
	}

	return resMat;
}
//------------------------------------------------------------------------------
bool CrankNicolsonDiffuseSolver::SuitableParams(const Params* params) const
{
	const auto cParams = dynamic_cast<const CrankNicolsonDiffuseSolverParams*>(params);

	return cParams != nullptr;
}
//------------------------------------------------------------------------------
std::string CrankNicolsonDiffuseSolver::GetSolverType() const
{
	return "Crank-Nicolson diffuse equation solver";
}
//------------------------------------------------------------------------------	
}
