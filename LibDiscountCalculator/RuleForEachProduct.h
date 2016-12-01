#pragma once
#include "IRule.h"

namespace libdiscountcalculator
{
class CRuleForEachProduct : public IRule
{
public:
	CRuleForEachProduct(ProductPtr const& product, RulePtr && rule);
	virtual Discounts GetDiscounts(std::vector<ProductPtr> const& products) override;
private:
	ProductPtr m_product;
	RulePtr m_rule;
};
}