// DiscountCalculator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <memory>
#include <vector>
#include <iostream>
#include <numeric>
#include <time.h>
#include "LibDiscountCalculator\Product.h"
#include "LibDiscountCalculator\PriceCalculator.h"
#include "LibDiscountCalculator\RuleBundleDiscount.h"
#include "LibDiscountCalculator\RuleBestOf.h"
#include "LibDiscountCalculator\RuleCountDiscount.h"
#include "LibDiscountCalculator\RuleExcludeProducts.h"

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
	auto getProduct = [&products](wchar_t product) { return products.at(product - 'A'); };
	vector<RulePtr> rules = {
		make_shared<CRuleBoundDiscount>(vector<ProductPtr>{ getProduct('A'), getProduct(L'B') } , 0.1),
		make_shared<CRuleBoundDiscount>(vector<ProductPtr>{ getProduct(L'D'), getProduct(L'E') } , 0.05),
		make_shared<CRuleBoundDiscount>(vector<ProductPtr>{ getProduct(L'E'), getProduct(L'F'), getProduct(L'G') } , 0.05),
		//TODO: A & [K, L, M]
		make_shared<CRuleExcludeProducts>(make_shared<CRuleBestOf>(vector<RulePtr>{
			make_shared<CRuleCountDiscount>(3, 0.05),
			make_shared<CRuleCountDiscount>(4, 0.1),
			make_shared<CRuleCountDiscount>(5, 0.2),
		}, vector<ProductPtr>{getProduct('A'), getProduct('C')})),
	};
	CPriceCalculator calculator;
	wcout << L"Rules:" << endl;
	for (auto& rule : rules)
	{
		calculator.AddRule(rule);
	}
	double totalCost = std::accumulate(products.begin(), products.end(), 0.0, [](double sum, ProductPtr const& product) {return sum + product->GetBaseCost(); });
	double costWithDiscount = calculator.CalculatePrice(products);
	wcout << L"Total cost: " << totalCost << endl;
	wcout << L"With discounts: " << costWithDiscount << endl;
	wcout << L"Saved: " << (totalCost - costWithDiscount) << endl;
	getchar();
	return 0;
}

