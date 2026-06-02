#pragma once
#include <memory>
#include <vector>
#include "repositories/Repository.h"
#include "models/Order.h"

using namespace std;

// Сервиз за поръчки
class OrderService {
private:
    Repository<Order> orderRepo;

public:
    OrderService() = default;
    ~OrderService() = default;

    bool createOrder(const shared_ptr<Order>& order);
    bool updateOrderStatus(int orderId, OrderStatus newStatus);
    shared_ptr<Order> getOrderById(int id) const;
    vector<shared_ptr<Order>> getOrdersByCustomer(int customerId) const;
    vector<shared_ptr<Order>> getOrdersByProducer(int producerId) const;
    vector<shared_ptr<Order>> getAllOrders() const;
    
    int getNextOrderId() const;
    bool save(const string& filename) const;
    bool load(const string& filename);
};
