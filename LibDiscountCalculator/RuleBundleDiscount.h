#pragma once
#include "IRule.h"
#include <vector>
#include "IProduct_fwd.h"

namespace libdiscountcalculator
{
class CRuleBoundDiscount : public IRule
{
public:
	CRuleBoundDiscount(std::vector<ProductPtr> const& products, double discountPercent);

	virtual double GetDiscount(std::vector<ProductPtr> const& products) override;
private:
	std::vector<ProductPtr> m_products;
	double m_discountPercent;
};
}
