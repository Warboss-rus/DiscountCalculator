#pragma once
#include <memory>

namespace libdiscountcalculator
{
class IRule;
typedef std::unique_ptr<IRule> RulePtr;
}