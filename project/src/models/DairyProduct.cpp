#include "models/DairyProduct.h"

using namespace std;

DairyProduct::DairyProduct() : Product() {}

DairyProduct::DairyProduct(int id, const string& name, double price, double quantity, int producerId, const string& village)
    : Product(id, name, price, quantity, producerId, village) {}

void DairyProduct::displayInfo() const {
    cout << "[Млечни] ";
    Product::displayInfo();
    cout << " (кг/бр)" << endl;
}

string DairyProduct::getCategory() const {
    return "DairyProduct";
}
