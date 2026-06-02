#pragma once
#include "models/User.h"

using namespace std;

// Клас за администратор
class Admin : public User {
public:
    Admin();
    Admin(int id, const string& name, const string& email, const string& password);
    ~Admin() override = default;

    void displayInfo() const override;
    string getRole() const override;

    void serialize(ostream& os) const override;
    void deserialize(istream& is) override;
};
