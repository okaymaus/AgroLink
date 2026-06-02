#include "models/Customer.h"

using namespace std;

Customer::Customer() : User() {}

Customer::Customer(int id, const string& name, const string& email, const string& password)
    : User(id, name, email, password) {}

void Customer::displayInfo() const {
    cout << "[Потребител - Клиент] ID: " << id
         << ", Име: " << name
         << ", Емейл: " << email << endl;
}

string Customer::getRole() const {
    return "Customer";
}

void Customer::serialize(ostream& os) const {
    User::serialize(os);
}

void Customer::deserialize(istream& is) {
    User::deserialize(is);
}
