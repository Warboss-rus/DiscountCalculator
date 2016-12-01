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

	typedef std::pair<ProductPtr, double> ProductDiscount;
	typedef std::vector<ProductDiscount> Discounts;
	virtual Discounts GetDiscounts(std::vector<ProductPtr> const& products) = 0;
};
}