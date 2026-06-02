#include "models/Admin.h"

using namespace std;

Admin::Admin() : User() {}

Admin::Admin(int id, const string& name, const string& email, const string& password)
    : User(id, name, email, password) {}

void Admin::displayInfo() const {
    cout << "[Потребител - Админ] ID: " << id
         << ", Име: " << name
         << ", Емейл: " << email << endl;
}

string Admin::getRole() const {
    return "Admin";
}

void Admin::serialize(ostream& os) const {
    User::serialize(os);
}

void Admin::deserialize(istream& is) {
    User::deserialize(is);
}
