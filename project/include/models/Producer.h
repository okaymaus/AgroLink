#pragma once
#include "models/User.h"

using namespace std;

// Клас за производител
class Producer : public User {
private:
    string village;

public:
    Producer();
    Producer(int id, const string& name, const string& email, const string& password, const string& village);
    ~Producer() override = default;

    string getVillage() const;
    void setVillage(const string& village);

    void displayInfo() const override;
    string getRole() const override;

    void serialize(ostream& os) const override;
    void deserialize(istream& is) override;
};
