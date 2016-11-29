#include "Product.h"

namespace libdiscountcalculator
{

CProduct::CProduct(std::wstring const& name, double baseCost)
	: m_name(name), m_baseCost(baseCost)
{
}

std::wstring CProduct::GetName() const
{
	return m_name;
}

double CProduct::GetBaseCost() const
{
	return m_baseCost;
}

}