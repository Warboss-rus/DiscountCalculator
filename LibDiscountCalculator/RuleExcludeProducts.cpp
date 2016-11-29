#include "RuleExcludeProducts.h"

namespace libdiscountcalculator
{

CRuleExcludeProducts::CRuleExcludeProducts(RulePtr const& rule, std::vector<ProductPtr> const& products)
	:m_rule(rule), m_products(products.begin(), products.end())
{
}

double CRuleExcludeProducts::GetDiscount(std::vector<ProductPtr> const& products)
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
	return m_rule->GetDiscount(productsWithoutExclude);
}

}