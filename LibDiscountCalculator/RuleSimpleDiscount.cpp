#include "RuleSimpleDiscount.h"

namespace libdiscountcalculator
{

CRuleSimpleDiscount::CRuleSimpleDiscount(std::vector<ProductPtr> const& products, double discount)
	:m_products(products.begin(), products.end()), m_discount(discount)
{

}

libdiscountcalculator::IRule::Discounts CRuleSimpleDiscount::GetDiscounts(std::vector<ProductPtr> const& products)
{
	Discounts result;
	for (auto& product : products)
	{
		if (m_products.find(product) != m_products.end())
		{
			result.push_back(std::make_pair(product, m_discount));
		}
	}
	return result;
}

}