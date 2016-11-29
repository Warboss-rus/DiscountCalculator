#pragma once
#include "IProduct_fwd.h"
#include <string>

namespace libdiscountcalculator
{
class IProduct
{
public:
	virtual ~IProduct() = default;

	virtual std::wstring GetName() const = 0;
	virtual double GetBaseCost() const = 0;
};
}