#include "RuleBestOf.h"
#include <algorithm>

namespace libdiscountcalculator
{

CRuleBestOf::CRuleBestOf(std::vector<RulePtr> const& rules)
	:m_rules(rules)
{
}

double CRuleBestOf::GetDiscount(std::vector<ProductPtr> const& products)
{
	double result = 0;
	for (auto& rule : m_rules)
	{
		result = std::max(result, rule->GetDiscount(products));
	}
	return result;
}

}