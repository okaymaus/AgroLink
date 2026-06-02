#include "models/Product.h"
#include <sstream>
#include <iomanip>

using namespace std;

Product::Product() : id(0), name(""), price(0.0), quantity(0.0), producerId(0), village("") {}

Product::Product(int id, const string& name, double price, double quantity, int producerId, const string& village)
    : id(id), name(name), price(price), quantity(quantity), producerId(producerId), village(village) {}

int Product::getId() const { return id; }
void Product::setId(int id) { this->id = id; }

string Product::getName() const { return name; }
void Product::setName(const string& name) { this->name = name; }

double Product::getPrice() const { return price; }
void Product::setPrice(double price) { this->price = price; }

double Product::getQuantity() const { return quantity; }
void Product::setQuantity(double quantity) { this->quantity = quantity; }

int Product::getProducerId() const { return producerId; }
void Product::setProducerId(int producerId) { this->producerId = producerId; }

string Product::getVillage() const { return village; }
void Product::setVillage(const string& village) { this->village = village; }

void Product::displayInfo() const {
    cout << "ID: " << id
         << " | Име: " << name
         << " | Цена: " << fixed << setprecision(2) << price << " лв."
         << " | Наличност: " << quantity
         << " | Село: " << village;
}

void Product::serialize(ostream& os) const {
    os << getCategory() << "|" << id << "|" << name << "|" << price << "|" << quantity << "|" << producerId << "|" << village;
}

void Product::deserialize(istream& is) {
    string token;
    
    if (getline(is, token, '|')) {
        id = stoi(token);
    }
    getline(is, name, '|');
    if (getline(is, token, '|')) {
        price = stod(token);
    }
    if (getline(is, token, '|')) {
        quantity = stod(token);
    }
    if (getline(is, token, '|')) {
        producerId = stoi(token);
    }
    getline(is, village, '|');
}
