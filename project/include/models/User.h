#pragma once
#include <string>
#include <iostream>

using namespace std;

// Абстрактен базов клас за потребител
class User {
protected:
    int id;
    string name;
    string email;
    string password;

public:
    User();
    User(int id, const string& name, const string& email, const string& password);
    virtual ~User() = default;

    // Гетъри и сетъри
    int getId() const;
    void setId(int id);

    string getName() const;
    void setName(const string& name);

    string getEmail() const;
    void setEmail(const string& email);

    string getPassword() const;
    void setPassword(const string& password);

    // Чисто виртуални методи
    virtual void displayInfo() const = 0;
    virtual string getRole() const = 0;

    // Запис и зареждане от файл
    virtual void serialize(ostream& os) const;
    virtual void deserialize(istream& is);
};
