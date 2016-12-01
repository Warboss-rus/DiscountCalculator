#include "RuleBestOf.h"
#include <numeric>
#include "IProduct.h"

namespace libdiscountcalculator
{

CRuleBestOf::CRuleBestOf(std::vector<RulePtr> const& rules)
	:m_rules(rules)
{
}

IRule::Discounts CRuleBestOf::GetDiscounts(std::vector<ProductPtr> const& products)
{
	Discounts result;
	double resultDiscountSum = 0;
	for (auto& rule : m_rules)
	{
		Discounts discounts = rule->GetDiscounts(products);
		double discountSum = std::accumulate(discounts.begin(), discounts.end(), 0.0, [](double sum, ProductDiscount const& discount) {
			return sum + discount.first->GetBaseCost() * (1.0 - discount.second);
		});
		if (discountSum > resultDiscountSum)
		{
			resultDiscountSum = discountSum;
			result = discounts;
		}
	}
	return result;
}

}