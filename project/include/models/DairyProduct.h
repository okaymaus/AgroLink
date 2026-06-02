#pragma once
#include "models/Product.h"

using namespace std;

// Клас за млечни продукти
class DairyProduct : public Product {
public:
    DairyProduct();
    DairyProduct(int id, const string& name, double price, double quantity, int producerId, const string& village);
    ~DairyProduct() override = default;

    void displayInfo() const override;
    string getCategory() const override;
};
