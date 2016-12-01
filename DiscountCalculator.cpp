// DiscountCalculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <vector>
#include <iostream>
#include <numeric>
#include <time.h>
#include <algorithm>
#include "LibDiscountCalculator\Product.h"
#include "LibDiscountCalculator\PriceCalculator.h"
#include "LibDiscountCalculator\RuleBundleDiscount.h"
#include "LibDiscountCalculator\RuleBestOf.h"
#include "LibDiscountCalculator\RuleCountDiscount.h"
#include "LibDiscountCalculator\RuleExcludeProducts.h"
#include "LibDiscountCalculator\RuleForEachProduct.h"
#include "LibDiscountCalculator\RuleSimpleDiscount.h"

using namespace std;
using namespace libdiscountcalculator;

int main()
{
	std::srand(static_cast<unsigned int>(time(NULL)));
	vector<ProductPtr> products;
	products.reserve(L'Z' - L'A');
	wcout << L"Products:" << endl;
	for (wchar_t name = L'A'; name <= L'Z'; ++name)
	{
		products.emplace_back(make_shared<CProduct>(wstring(1, name), rand()));
		wcout << products.back()->GetName() << L' ' << products.back()->GetBaseCost() << endl;
	}
	CPriceCalculator calculator;
	auto getProduct = [&products](wchar_t product) { return products.at(product - 'A'); };
	calculator.AddRule(make_unique<CRuleBoundDiscount>(vector<ProductPtr>{ getProduct('A'), getProduct(L'B') }, 0.1));
	calculator.AddRule(make_unique<CRuleBoundDiscount>(vector<ProductPtr>{ getProduct(L'D'), getProduct(L'E') }, 0.05));
	calculator.AddRule(make_unique<CRuleBoundDiscount>(vector<ProductPtr>{ getProduct(L'E'), getProduct(L'F'), getProduct(L'G') }, 0.05));
	calculator.AddRule(make_unique<CRuleForEachProduct>(getProduct(L'A'), 
		make_unique<CRuleSimpleDiscount>(vector<ProductPtr>{ getProduct(L'K'), getProduct(L'L'), getProduct(L'M') }, 0.05))
	);
	vector<RulePtr> rules;
	rules.push_back(make_unique<CRuleCountDiscount>(3, 0.05));
	rules.push_back(make_unique<CRuleCountDiscount>(4, 0.1));
	rules.push_back(make_unique<CRuleCountDiscount>(5, 0.2));
	calculator.AddRule(make_unique<CRuleExcludeProducts>(make_unique<CRuleBestOf>(std::move(rules)), vector<ProductPtr>{getProduct('A'), getProduct('C')}));
	wcout << L"Result:" << endl;
	std::vector<CPriceCalculator::ProductPrice> prices;
	double totalCost = std::accumulate(products.begin(), products.end(), 0.0, [](double sum, ProductPtr const& product) { return sum + product->GetBaseCost(); });
	double costWithDiscount = calculator.CalculatePrice(products, &prices);
	std::sort(prices.begin(), prices.end(), [](CPriceCalculator::ProductPrice const& first, CPriceCalculator::ProductPrice const& second) { 
		return first.first->GetName() < second.first->GetName(); 
	});
	for (auto& pair : prices)
	{
		wcout << pair.first->GetName() << L' ' << pair.second << endl;
	}
	wcout << L"Total cost: " << totalCost << endl;
	wcout << L"With discounts: " << costWithDiscount << endl;
	wcout << L"Saved: " << (totalCost - costWithDiscount) << endl;
	getchar();
	return 0;
}

