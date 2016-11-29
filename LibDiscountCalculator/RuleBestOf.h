#pragma once
#include "IRule.h"

namespace libdiscountcalculator
{
class CRuleBestOf : public IRule 
{
public:
	CRuleBestOf(std::vector<RulePtr> const& rules);

	virtual double GetDiscount(std::vector<ProductPtr> const& products) override;
private:
	std::vector<RulePtr> m_rules;
};
}
