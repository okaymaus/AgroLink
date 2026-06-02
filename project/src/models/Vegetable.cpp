#include "models/Vegetable.h"

using namespace std;

Vegetable::Vegetable() : Product() {}

Vegetable::Vegetable(int id, const string& name, double price, double quantity, int producerId, const string& village)
    : Product(id, name, price, quantity, producerId, village) {}

void Vegetable::displayInfo() const {
    cout << "[Зеленчуци] ";
    Product::displayInfo();
    cout << " (кг)" << endl;
}

string Vegetable::getCategory() const {
    return "Vegetable";
}
