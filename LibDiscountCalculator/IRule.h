#pragma once
#include "IRule_fwd.h"
#include "IProduct_fwd.h"
#include <vector>

namespace libdiscountcalculator
{
class IRule
{
public:
	virtual ~IRule() = default;

	virtual double GetDiscount(std::vector<ProductPtr> const& products) = 0;
};
}