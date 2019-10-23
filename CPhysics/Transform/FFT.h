#pragma once

#include "ITransform.h"

namespace CPhysics
{

class FFT final : public ITransform
{
public:
	FFT() = default;
	virtual ~FFT() = default;

	std::vector<std::complex<Real>> Transform(const std::vector<std::complex<Real>>& x) const override;
	std::vector<std::complex<Real>> TransformReal(const std::vector<Real>& x) const override;
};
	
};