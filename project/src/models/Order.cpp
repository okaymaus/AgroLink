#include "models/Order.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include "models/Fruit.h"

using namespace std;

string orderStatusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::Pending: return "Pending";
        case OrderStatus::Accepted: return "Accepted";
        case OrderStatus::Rejected: return "Rejected";
        case OrderStatus::Completed: return "Completed";
    }
    return "Unknown";
}

OrderStatus stringToOrderStatus(const string& str) {
    if (str == "Accepted") return OrderStatus::Accepted;
    if (str == "Rejected") return OrderStatus::Rejected;
    if (str == "Completed") return OrderStatus::Completed;
    return OrderStatus::Pending;
}

Order::Order() : id(0), customerId(0), producerId(0), status(OrderStatus::Pending) {}

Order::Order(int id, int customerId, int producerId, const vector<shared_ptr<Product>>& products, OrderStatus status)
    : id(id), customerId(customerId), producerId(producerId), products(products), status(status) {}

int Order::getId() const { return id; }
void Order::setId(int id) { this->id = id; }

int Order::getCustomerId() const { return customerId; }
void Order::setCustomerId(int customerId) { this->customerId = customerId; }

int Order::getProducerId() const { return producerId; }
void Order::setProducerId(int producerId) { this->producerId = producerId; }

vector<shared_ptr<Product>> Order::getProducts() const { return products; }
void Order::setProducts(const vector<shared_ptr<Product>>& products) { this->products = products; }

OrderStatus Order::getStatus() const { return status; }
void Order::setStatus(OrderStatus status) { this->status = status; }

double Order::calculateTotal() const {
    double total = 0.0;
    for (const auto& product : products) {
        if (product) {
            total += product->getPrice() * product->getQuantity();
        }
    }
    return total;
}

void Order::changeStatus(OrderStatus newStatus) {
    this->status = newStatus;
}

void Order::displayOrder() const {
    cout << "Поръчка ID: " << id 
         << " | Статус: " << orderStatusToString(status)
         << " | Общо: " << fixed << setprecision(2) << calculateTotal() << " лв." << endl;
    cout << "  Продукти:" << endl;
    for (const auto& product : products) {
        if (product) {
            cout << "   - " << product->getName() 
                 << " (Цена: " << product->getPrice() << " лв., Количество: " << product->getQuantity() << ")" << endl;
        }
    }
}

void Order::serialize(ostream& os) const {
    os << id << "|" << customerId << "|" << producerId << "|" << orderStatusToString(status) << "|";
    for (size_t i = 0; i < products.size(); ++i) {
        if (!products[i]) continue;
        os << products[i]->getId() << ";"
           << products[i]->getName() << ";"
           << products[i]->getPrice() << ";"
           << products[i]->getQuantity();
        if (i < products.size() - 1) {
            os << ",";
        }
    }
}

void Order::deserialize(istream& is) {
    string token;
    
    if (getline(is, token, '|')) {
        id = stoi(token);
    }
    if (getline(is, token, '|')) {
        customerId = stoi(token);
    }
    if (getline(is, token, '|')) {
        producerId = stoi(token);
    }
    if (getline(is, token, '|')) {
        status = stringToOrderStatus(token);
    }
    
    products.clear();
    string allProductsToken;
    if (getline(is, allProductsToken, '|')) {
        if (allProductsToken.empty()) return;
        stringstream ss(allProductsToken);
        string singleProductToken;
        while (getline(ss, singleProductToken, ',')) {
            if (singleProductToken.empty()) continue;
            stringstream prodSS(singleProductToken);
            string pId, pName, pPrice, pQty;
            
            getline(prodSS, pId, ';');
            getline(prodSS, pName, ';');
            getline(prodSS, pPrice, ';');
            getline(prodSS, pQty, ';');
            
            if (!pId.empty() && !pName.empty() && !pPrice.empty() && !pQty.empty()) {
                auto stubProd = make_shared<Fruit>(
                    stoi(pId), pName, stod(pPrice), stod(pQty), producerId, ""
                );
                products.push_back(stubProd);
            }
        }
    }
}
