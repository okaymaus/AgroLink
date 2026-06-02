#include "models/HandmadeProduct.h"

using namespace std;

HandmadeProduct::HandmadeProduct() : Product() {}

HandmadeProduct::HandmadeProduct(int id, const string& name, double price, double quantity, int producerId, const string& village)
    : Product(id, name, price, quantity, producerId, village) {}

void HandmadeProduct::displayInfo() const {
    cout << "[Ръчно изработени] ";
    Product::displayInfo();
    cout << " (бр)" << endl;
}

string HandmadeProduct::getCategory() const {
    return "HandmadeProduct";
}
