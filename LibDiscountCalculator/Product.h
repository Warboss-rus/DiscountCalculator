#pragma once
#include "IProduct.h"

namespace libdiscountcalculator
{
class CProduct : public IProduct
{
public:
	CProduct(std::wstring const& name, double baseCost);
	virtual std::wstring GetName() const override;
	virtual double GetBaseCost() const override;
private:
	std::wstring m_name;
	double m_baseCost;
};
}