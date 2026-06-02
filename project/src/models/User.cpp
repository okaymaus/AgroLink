#include "models/User.h"
#include <sstream>

using namespace std;

User::User() : id(0), name(""), email(""), password("") {}

User::User(int id, const string& name, const string& email, const string& password)
    : id(id), name(name), email(email), password(password) {}

int User::getId() const { return id; }
void User::setId(int id) { this->id = id; }

string User::getName() const { return name; }
void User::setName(const string& name) { this->name = name; }

string User::getEmail() const { return email; }
void User::setEmail(const string& email) { this->email = email; }

string User::getPassword() const { return password; }
void User::setPassword(const string& password) { this->password = password; }

void User::serialize(ostream& os) const {
    os << getRole() << "|" << id << "|" << name << "|" << email << "|" << password;
}

void User::deserialize(istream& is) {
    string token;
    
    // Ролята вече е прочетена от репозиторито
    if (getline(is, token, '|')) {
        id = stoi(token);
    }
    getline(is, name, '|');
    getline(is, email, '|');
    getline(is, password, '|');
}
