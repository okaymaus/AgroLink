#pragma once
#include "models/Product.h"

using namespace std;

// Клас за плодове
class Fruit : public Product {
public:
    Fruit();
    Fruit(int id, const string& name, double price, double quantity, int producerId, const string& village);
    ~Fruit() override = default;

    void displayInfo() const override;
    string getCategory() const override;
};
