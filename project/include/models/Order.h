#pragma once
#include <vector>
#include <memory>
#include "models/Product.h"

using namespace std;

enum class OrderStatus {
    Pending,
    Accepted,
    Rejected,
    Completed
};

string orderStatusToString(OrderStatus status);

// Клас за поръчка
class Order {
private:
    int id;
    int customerId;
    int producerId;
    vector<shared_ptr<Product>> products;
    OrderStatus status;

public:
    Order();
    Order(int id, int customerId, int producerId, const vector<shared_ptr<Product>>& products, OrderStatus status = OrderStatus::Pending);
    ~Order() = default;

    // Гетъри и сетъри
    int getId() const;
    void setId(int id);

    int getCustomerId() const;
    void setCustomerId(int customerId);

    int getProducerId() const;
    void setProducerId(int producerId);

    vector<shared_ptr<Product>> getProducts() const;
    void setProducts(const vector<shared_ptr<Product>>& products);

    OrderStatus getStatus() const;
    void setStatus(OrderStatus status);

    // Бизнес логика
    double calculateTotal() const;
    void changeStatus(OrderStatus newStatus);
    void displayOrder() const;

    // Запис и зареждане
    void serialize(ostream& os) const;
    void deserialize(istream& is);
};
