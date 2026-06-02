#include "services/OrderService.h"
#include <algorithm>

using namespace std;

bool OrderService::createOrder(const shared_ptr<Order>& order) {
    if (!order) return false;
    orderRepo.add(order);
    return true;
}

bool OrderService::updateOrderStatus(int orderId, OrderStatus newStatus) {
    auto order = orderRepo.findById(orderId);
    if (order) {
        order->changeStatus(newStatus);
        return true;
    }
    return false;
}

shared_ptr<Order> OrderService::getOrderById(int id) const {
    return orderRepo.findById(id);
}

vector<shared_ptr<Order>> OrderService::getOrdersByCustomer(int customerId) const {
    vector<shared_ptr<Order>> result;
    auto orders = orderRepo.getAll();
    for (const auto& ord : orders) {
        if (ord && ord->getCustomerId() == customerId) {
            result.push_back(ord);
        }
    }
    return result;
}

vector<shared_ptr<Order>> OrderService::getOrdersByProducer(int producerId) const {
    vector<shared_ptr<Order>> result;
    auto orders = orderRepo.getAll();
    for (const auto& ord : orders) {
        if (ord && ord->getProducerId() == producerId) {
            result.push_back(ord);
        }
    }
    return result;
}

vector<shared_ptr<Order>> OrderService::getAllOrders() const {
    return orderRepo.getAll();
}

int OrderService::getNextOrderId() const {
    auto orders = orderRepo.getAll();
    if (orders.empty()) return 1;
    
    int maxId = 0;
    for (const auto& o : orders) {
        if (o->getId() > maxId) {
            maxId = o->getId();
        }
    }
    return maxId + 1;
}

bool OrderService::save(const string& filename) const {
    return orderRepo.saveToFile(filename);
}

bool OrderService::load(const string& filename) {
    return orderRepo.loadFromFile(filename);
}
