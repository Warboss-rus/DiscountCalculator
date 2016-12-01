#pragma once
#include "IRule.h"
#include <set>

namespace libdiscountcalculator
{
class CRuleSimpleDiscount : public IRule 
{
public:
	CRuleSimpleDiscount(std::vector<ProductPtr> const& products, double discount);
	virtual Discounts GetDiscounts(std::vector<ProductPtr> const& products) override;
private:
	std::set<ProductPtr> m_products;
	double m_discount;
};
}
