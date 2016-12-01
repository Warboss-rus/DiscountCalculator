#include "RuleBundleDiscount.h"
#include <intsafe.h>
#include <algorithm>
#include <numeric>
#include "IProduct.h"
#include <iterator>

namespace libdiscountcalculator
{

CRuleBoundDiscount::CRuleBoundDiscount(std::vector<ProductPtr> const& products, double discountPercent)
	:m_products(products), m_discountPercent(discountPercent)
{
}

IRule::Discounts CRuleBoundDiscount::GetDiscounts(std::vector<ProductPtr> const& products)
{
	size_t count = SIZE_T_MAX;
	for (auto& product : m_products)
	{
		count = std::min<size_t>(count, std::count(products.begin(), products.end(), product));
	}
	Discounts result;
	if (count > 0)
	{
		for (size_t i = 0; i < count; ++i)
		{
			std::transform(m_products.begin(), m_products.end(), std::back_inserter(result), [this](ProductPtr const& product) {
				return std::make_pair(product, m_discountPercent);
			});
		}
	}
	return result;
}

}