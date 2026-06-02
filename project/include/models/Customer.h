#pragma once
#include "models/User.h"

using namespace std;

// Клас за клиент
class Customer : public User {
public:
    Customer();
    Customer(int id, const string& name, const string& email, const string& password);
    ~Customer() override = default;

    void displayInfo() const override;
    string getRole() const override;

    void serialize(ostream& os) const override;
    void deserialize(istream& is) override;
};
