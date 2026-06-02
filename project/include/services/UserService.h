#pragma once
#include <memory>
#include <vector>
#include <optional>
#include "repositories/Repository.h"
#include "models/User.h"

using namespace std;

// Сервиз за потребители
class UserService {
private:
    Repository<User> userRepo;

public:
    UserService() = default;
    ~UserService() = default;

    bool registerUser(const shared_ptr<User>& user);
    shared_ptr<User> authenticate(const string& email, const string& password) const;
    shared_ptr<User> getUserById(int id) const;
    vector<shared_ptr<User>> getAllUsers() const;
    
    int getNextId() const;
    bool save(const string& filename) const;
    bool load(const string& filename);
};
