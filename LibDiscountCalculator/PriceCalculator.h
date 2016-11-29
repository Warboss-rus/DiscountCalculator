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
	double CalculatePrice(std::vector<ProductPtr> const& products) const;
private:
	std::vector<RulePtr> m_rules;
};
}