#pragma once
#include "models/Product.h"

using namespace std;

// Клас за зеленчуци
class Vegetable : public Product {
public:
    Vegetable();
    Vegetable(int id, const string& name, double price, double quantity, int producerId, const string& village);
    ~Vegetable() override = default;

    void displayInfo() const override;
    string getCategory() const override;
};
