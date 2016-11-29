#include "RuleBundleDiscount.h"
#include <intsafe.h>
#include <algorithm>
#include <numeric>
#include "IProduct.h"

namespace libdiscountcalculator
{

CRuleBoundDiscount::CRuleBoundDiscount(std::vector<ProductPtr> const& products, double discountPercent)
	:m_products(products), m_discountPercent(discountPercent)
{
}

double CRuleBoundDiscount::GetDiscount(std::vector<ProductPtr> const& products)
{
	size_t count = SIZE_T_MAX;
	for (auto& product : m_products)
	{
		count = std::min<size_t>(count, std::count(products.begin(), products.end(), product));
	}
	double discountedProductsPrice = std::accumulate(m_products.begin(), m_products.end(), 0.0, [](double sum, ProductPtr const& product) { 
		return sum + product->GetBaseCost(); 
	});
	return count * m_discountPercent * discountedProductsPrice;
}

}