#pragma once
#include "IRule.h"
#include <set>

namespace libdiscountcalculator
{
class CRuleExcludeProducts : public IRule
{
public:
	CRuleExcludeProducts(RulePtr const& rule, std::vector<ProductPtr> const& products);

	virtual Discounts GetDiscounts(std::vector<ProductPtr> const& products) override;
private:
	RulePtr m_rule;
	std::set<ProductPtr> m_products;
};
}
