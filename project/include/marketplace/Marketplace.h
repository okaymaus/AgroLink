#pragma once
#include <memory>
#include <vector>
#include <utility>
#include "services/UserService.h"
#include "services/ProductService.h"
#include "services/OrderService.h"
#include "services/ReviewService.h"

using namespace std;

// Главен координатор на платформата
class Marketplace {
private:
    UserService userService;
    ProductService productService;
    OrderService orderService;
    ReviewService reviewService;
    shared_ptr<User> currentUser;

public:
    Marketplace();
    ~Marketplace() = default;

    // Вход и регистрация
    bool registerCustomer(const string& name, const string& email, const string& password);
    bool registerProducer(const string& name, const string& email, const string& password, const string& villageName);
    bool registerAdmin(const string& name, const string& email, const string& password);
    bool login(const string& email, const string& password);
    void logout();
    shared_ptr<User> getCurrentUser() const;

    // Управление на продукти и села
    bool addProduct(const string& name, double price, double quantity, const string& category);
    bool addVillage(const string& name, const string& region, int population);
    vector<shared_ptr<Product>> searchProducts(const string& query) const;
    vector<shared_ptr<Product>> getProductsByCategory(const string& category) const;
    vector<shared_ptr<Product>> getProductsByVillage(const string& villageName) const;
    vector<shared_ptr<Product>> getAllProducts() const;
    vector<shared_ptr<Village>> getAllVillages() const;
    vector<shared_ptr<Product>> getCurrentProducerProducts() const;

    // Управление на поръчки
    bool createOrder(const vector<pair<int, double>>& itemsToOrder);
    bool updateOrderStatus(int orderId, OrderStatus newStatus);
    vector<shared_ptr<Order>> getCurrentUserOrders() const;

    // Управление на отзиви
    bool leaveReview(int producerId, int rating, const string& comment);
    vector<shared_ptr<Review>> getProducerReviews(int producerId) const;
    double getProducerAverageRating(int producerId) const;

    // Списък потребители за админ
    vector<shared_ptr<User>> getAllUsers() const;

    // Запис и зареждане
    void loadData();
    void saveData() const;
};
