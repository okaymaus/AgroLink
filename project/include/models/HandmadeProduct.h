#pragma once
#include "models/Product.h"

using namespace std;

// Клас за ръчно изработени стоки
class HandmadeProduct : public Product {
public:
    HandmadeProduct();
    HandmadeProduct(int id, const string& name, double price, double quantity, int producerId, const string& village);
    ~HandmadeProduct() override = default;

    void displayInfo() const override;
    string getCategory() const override;
};
