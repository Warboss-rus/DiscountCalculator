#include "PriceCalculator.h"
#include "IProduct.h"
#include "IRule.h"
#include <numeric>

namespace libdiscountcalculator
{
void CPriceCalculator::AddRule(RulePtr const& rule)
{
	m_rules.push_back(rule);
}

double CPriceCalculator::CalculatePrice(std::vector<ProductPtr> const& products) const
{
	std::vector<ProductPtr> productsCopy = products;
	double result = std::accumulate(productsCopy.begin(), productsCopy.end(), 0.0, [](double sum, ProductPtr const& product) {return sum + product->GetBaseCost(); });
	for (auto& rule : m_rules)
	{
		auto discounts = rule->GetDiscounts(productsCopy);
		result -= std::accumulate(discounts.begin(), discounts.end(), 0.0, [](double sum, IRule::ProductDiscount const& discount) {
			return sum + discount.first->GetBaseCost() * (1.0 - discount.second);
		});
		for (auto& discount : discounts)//Remove already discounted items from further rules
		{
			auto it = std::find(productsCopy.begin(), productsCopy.end(), discount.first);
			productsCopy.erase(it);
		}
	}
	return result;
}

}