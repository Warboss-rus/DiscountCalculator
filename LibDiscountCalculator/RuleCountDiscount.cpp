#include "RuleCountDiscount.h"
#include <numeric>
#include "IProduct.h"

namespace libdiscountcalculator
{

CRuleCountDiscount::CRuleCountDiscount(size_t count, double discountPercent)
	:m_count(count), m_discountPercent(discountPercent)
{

}

double CRuleCountDiscount::GetDiscount(std::vector<ProductPtr> const& products)
{
	if (products.size() >= m_count)
	{
		return m_discountPercent * std::accumulate(products.begin(), products.end(), 0.0, [](double sum, ProductPtr const& product) {return sum + product->GetBaseCost(); });
	}
	return 0.0;
}

}