#pragma once
#include <string>
#include <iostream>

using namespace std;

// Базов клас за продукт
class Product {
protected:
    int id;
    string name;
    double price;
    double quantity;
    int producerId;
    string village;

public:
    Product();
    Product(int id, const string& name, double price, double quantity, int producerId, const string& village);
    virtual ~Product() = default;

    // Гетъри и сетъри
    int getId() const;
    void setId(int id);

    string getName() const;
    void setName(const string& name);

    double getPrice() const;
    void setPrice(double price);

    double getQuantity() const;
    void setQuantity(double quantity);

    int getProducerId() const;
    void setProducerId(int producerId);

    string getVillage() const;
    void setVillage(const string& village);

    // Виртуални методи
    virtual void displayInfo() const;
    virtual string getCategory() const = 0;

    // Сериализация
    virtual void serialize(ostream& os) const;
    virtual void deserialize(istream& is);
};
