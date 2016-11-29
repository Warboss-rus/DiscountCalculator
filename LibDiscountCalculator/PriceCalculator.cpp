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
	double result = std::accumulate(products.begin(), products.end(), 0.0, [](double sum, ProductPtr const& product) {return sum + product->GetBaseCost(); });
	for (auto& rule : m_rules)
	{
		result -= rule->GetDiscount(products);
	}
	return result;
}

}