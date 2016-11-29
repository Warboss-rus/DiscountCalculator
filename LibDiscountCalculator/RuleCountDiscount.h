#pragma once
#include "IRule.h"

namespace libdiscountcalculator
{
class CRuleCountDiscount : public IRule
{
public:
	CRuleCountDiscount(size_t count, double discountPercent);

	virtual double GetDiscount(std::vector<ProductPtr> const& products) override;
private:
	size_t m_count;
	double m_discountPercent;
};
}
