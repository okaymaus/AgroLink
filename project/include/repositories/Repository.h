#pragma once
#include <vector>
#include <memory>

using namespace std;

// Обикновен шаблон за репозитори
template <typename T>
class Repository {
protected:
    vector<shared_ptr<T>> items;

public:
    virtual ~Repository() = default;

    // Добавяне на елемент
    void add(shared_ptr<T> item) {
        if (item) {
            items.push_back(item);
        }
    }

    // Изтриване по ID
    bool removeById(int id) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if ((*it)->getId() == id) {
                items.erase(it);
                return true;
            }
        }
        return false;
    }

    // Намиране по ID
    shared_ptr<T> findById(int id) const {
        for (const auto& item : items) {
            if (item->getId() == id) {
                return item;
            }
        }
        return nullptr;
    }

    // Връщане на всички елементи
    vector<shared_ptr<T>> getAll() const {
        return items;
    }

    // Изчистване на списъка
    void clear() {
        items.clear();
    }
};
