#include "services/UserService.h"

using namespace std;

bool UserService::registerUser(const shared_ptr<User>& user) {
    if (!user) return false;
    
    // Проверка за дублиране на емейл
    auto users = userRepo.getAll();
    auto it = find_if(users.begin(), users.end(), [&user](const auto& u) {
        return u->getEmail() == user->getEmail();
    });
    
    if (it != users.end()) {
        return false;
    }
    
    userRepo.add(user);
    return true;
}

shared_ptr<User> UserService::authenticate(const string& email, const string& password) const {
    auto users = userRepo.getAll();
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i]->getEmail() == email && users[i]->getPassword() == password) {
            return users[i];
        }
    }
    return nullptr;
}

shared_ptr<User> UserService::getUserById(int id) const {
    return userRepo.findById(id);
}

vector<shared_ptr<User>> UserService::getAllUsers() const {
    return userRepo.getAll();
}

int UserService::getNextId() const {
    auto users = userRepo.getAll();
    if (users.empty()) return 1;
    
    int maxId = 0;
    for (const auto& u : users) {
        if (u->getId() > maxId) {
            maxId = u->getId();
        }
    }
    return maxId + 1;
}

bool UserService::save(const string& filename) const {
    return userRepo.saveToFile(filename);
}

bool UserService::load(const string& filename) {
    return userRepo.loadFromFile(filename);
}
