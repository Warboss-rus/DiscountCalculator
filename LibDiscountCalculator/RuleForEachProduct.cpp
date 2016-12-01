#include "RuleForEachProduct.h"
#include <algorithm>
#include "IProduct.h"

namespace libdiscountcalculator
{
CRuleForEachProduct::CRuleForEachProduct(ProductPtr const& product, RulePtr const& rule)
	:m_product(product), m_rule(rule)
{

}

IRule::Discounts CRuleForEachProduct::GetDiscounts(std::vector<ProductPtr> const& products)
{
	size_t count = std::count(products.begin(), products.end(), m_product);
	Discounts discounts = m_rule->GetDiscounts(products);
	std::sort(discounts.begin(), discounts.end(), [](ProductDiscount const& first, ProductDiscount const& second) {
		return first.first->GetBaseCost() * first.second < second.first->GetBaseCost() * second.second;
	});
	return Discounts(discounts.begin(), discounts.begin() + std::min(count, discounts.size()));
}
}