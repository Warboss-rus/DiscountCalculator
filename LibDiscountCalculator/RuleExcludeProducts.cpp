#include "RuleExcludeProducts.h"

namespace libdiscountcalculator
{

CRuleExcludeProducts::CRuleExcludeProducts(RulePtr && rule, std::vector<ProductPtr> const& products)
	:m_rule(std::move(rule)), m_products(products.begin(), products.end())
{
}

IRule::Discounts CRuleExcludeProducts::GetDiscounts(std::vector<ProductPtr> const& products)
{
	std::vector<ProductPtr> productsWithoutExclude;
	productsWithoutExclude.reserve(products.size() - m_products.size());
	for (auto& product : products)
	{
		if (m_products.find(product) == m_products.end())
		{
			productsWithoutExclude.push_back(product);
		}
	}
	return m_rule->GetDiscounts(productsWithoutExclude);
}

}