#pragma once
#include <vector>
#include "IRule_fwd.h"
#include "IProduct_fwd.h"

namespace libdiscountcalculator
{
class CPriceCalculator
{
public:
	void AddRule(RulePtr const& rule);

	typedef std::pair<ProductPtr, double> ProductPrice;
	double CalculatePrice(std::vector<ProductPtr> const& products, std::vector<ProductPrice> * prices = nullptr) const;
private:
	std::vector<RulePtr> m_rules;
};
}