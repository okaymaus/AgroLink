#include "models/Fruit.h"

using namespace std;

Fruit::Fruit() : Product() {}

Fruit::Fruit(int id, const string& name, double price, double quantity, int producerId, const string& village)
    : Product(id, name, price, quantity, producerId, village) {}

void Fruit::displayInfo() const {
    cout << "[Плодове] ";
    Product::displayInfo();
    cout << " (кг)" << endl;
}

string Fruit::getCategory() const {
    return "Fruit";
}
