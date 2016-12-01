#include "PriceCalculator.h"
#include "IProduct.h"
#include "IRule.h"
#include <numeric>
#include <iterator>
#include <algorithm>

namespace libdiscountcalculator
{
void CPriceCalculator::AddRule(RulePtr && rule)
{
	m_rules.push_back(std::move(rule));
}

double CPriceCalculator::CalculatePrice(std::vector<ProductPtr> const& products, std::vector<ProductPrice> * prices) const
{
	prices->clear();
	prices->reserve(products.size());
	std::vector<ProductPtr> productsCopy = products;
	double result = std::accumulate(productsCopy.begin(), productsCopy.end(), 0.0, [](double sum, ProductPtr const& product) {return sum + product->GetBaseCost(); });
	for (auto& rule : m_rules)
	{
		auto discounts = rule->GetDiscounts(productsCopy);
		result -= std::accumulate(discounts.begin(), discounts.end(), 0.0, [](double sum, IRule::ProductDiscount const& discount) {
			return sum + discount.first->GetBaseCost() * discount.second;
		});
		for (auto& discount : discounts)//Remove already discounted items from further rules
		{
			auto it = std::find(productsCopy.begin(), productsCopy.end(), discount.first);
			productsCopy.erase(it);
			prices->push_back(make_pair(discount.first, discount.first->GetBaseCost() * (1.0 - discount.second)));
		}
	}
	std::transform(productsCopy.begin(), productsCopy.end(), std::back_inserter(*prices), [](ProductPtr const& product) {
		return std::make_pair(product, product->GetBaseCost());
	});
	return result;
}

}