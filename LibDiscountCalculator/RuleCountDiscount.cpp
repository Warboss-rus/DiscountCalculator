#include "RuleCountDiscount.h"
#include "IProduct.h"
#include <algorithm>
#include <iterator>

namespace libdiscountcalculator
{

CRuleCountDiscount::CRuleCountDiscount(size_t count, double discountPercent)
	:m_count(count), m_discountPercent(discountPercent)
{

}

IRule::Discounts CRuleCountDiscount::GetDiscounts(std::vector<ProductPtr> const& products)
{
	Discounts result;
	if (products.size() >= m_count)
	{
		std::transform(products.begin(), products.end(), std::back_inserter(result), [this](ProductPtr const& product) {
			return std::make_pair(product, m_discountPercent);
		});
		return result;
	}
	return result;
}

}