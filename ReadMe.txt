Калькулятор скидок v0.1
Простейшая библиотека для подсчета стоимости товаров с учетом скидок, написаная на С++11

Quick start:
1. Собрать список всех продуктов, реализующих интерфейс IProduct.
2. Создать экземпляр класса CPriceCalculator.
3. Добавить в CPriceCalculator правила, описывающие действующие скидки (см. раздел Правила).
4. Вызвать у CPriceCalculator метод CalculatePrice, передав список продуктов в корзине. Будет возвращена сумма заказа.

Структуры и типы:
ProductPtr = shared_ptr<IProduct>
RulePtr = unique_ptr<IRule>
ProductDiscount = pair<ProductPtr, double> - продукт и его скидка в процентах
Discounts = vector<ProductDiscount> - продукты и их скидки, полученные из правила
ProductPrice = pair<ProductPtr, double> - продукт и его цена после скидок

Интерфейсы:
IProduct - базовый интерфейс продукта для расчета стоимости. Методы:
- wstring GetName() const - возвращает имя продукта
- double GetBaseCost() const - возвращает стоимость продукта без скидок
IRule - интерфейс правила для скидки
- Discounts GetDiscounts(vector<ProductPtr> products) const - возвращает продукты, на которые сделана скидка и размер скидки в процентах

Классы:
CProduct - базовая реализация интерфейса IProduct, абстрактный продукт
CPriceCalculator - калькулятор скидок
- void AddRule(RulePtr) - добавляет правило, определяющее скидку
- double CalculatePrice(vector<ProductPtr> products, vector<ProductPrice>* prices = null) const - Принимает список продуктов, возвращает конечную сумму покупки. Опциональный параметр prices позволяет получить стоимость каждого товара в отдельности.

Правила (скидки):
CRuleBestOf - дает лучшую скидку из дочерних.
CRuleBoundDiscount - дает скидку на указанные продукты только если все продукты есть в корзине (для каждого набора).
CRuleCountDiscount - дает скидку если общее количество продуктов равно или превышает заданное значение.
CRuleExcludeProducts - исключает определенные продукты из списка для дочернего правила. Например, если некоторые продукты не учавствуют в CRuleCountDiscount.
CRuleForEachProduct - возвращает до N лучших скидок из дочернего правила, где N - количество указанного продукта в заказе.
CRuleSimpleDiscount - дает скидки на любой (и каждый) из указанных продуктов.

Пример использования можно посмотреть в файле DiscountCalculator.cpp