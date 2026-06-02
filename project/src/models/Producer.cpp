#include "models/Producer.h"

using namespace std;

Producer::Producer() : User(), village("") {}

Producer::Producer(int id, const string& name, const string& email, const string& password, const string& village)
    : User(id, name, email, password), village(village) {}

string Producer::getVillage() const { return village; }
void Producer::setVillage(const string& village) { this->village = village; }

void Producer::displayInfo() const {
    cout << "[Потребител - Производител] ID: " << id
         << ", Име: " << name
         << ", Село: " << village
         << ", Емейл: " << email << endl;
}

string Producer::getRole() const {
    return "Producer";
}

void Producer::serialize(ostream& os) const {
    User::serialize(os);
    os << "|" << village;
}

void Producer::deserialize(istream& is) {
    User::deserialize(is);
    getline(is, village, '|');
}
