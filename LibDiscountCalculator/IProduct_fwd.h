#pragma once
#include <memory>

namespace libdiscountcalculator
{
class IProduct;
typedef std::shared_ptr<IProduct> ProductPtr;
}