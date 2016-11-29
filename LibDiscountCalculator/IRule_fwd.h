#pragma once
#include <memory>

namespace libdiscountcalculator
{
class IRule;
typedef std::shared_ptr<IRule> RulePtr;
}