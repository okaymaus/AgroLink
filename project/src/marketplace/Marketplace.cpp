#include "marketplace/Marketplace.h"
#include "models/Customer.h"
#include "models/Producer.h"
#include "models/Admin.h"
#include "models/Fruit.h"
#include "models/Vegetable.h"
#include "models/DairyProduct.h"
#include "models/HandmadeProduct.h"
#include <map>
#include <iostream>

using namespace std;

Marketplace::Marketplace() : currentUser(nullptr) {}

bool Marketplace::registerCustomer(const string& name, const string& email, const string& password) {
    int id = userService.getNextId();
    auto customer = make_shared<Customer>(id, name, email, password);
    return userService.registerUser(customer);
}

bool Marketplace::registerProducer(const string& name, const string& email, const string& password, const string& villageName) {
    auto village = productService.getVillageByName(villageName);
    if (!village) {
        cout << "Грешка: Селото '" << villageName << "' не съществува! Админът трябва да го добави първо." << endl;
        return false;
    }
    
    int id = userService.getNextId();
    auto producer = make_shared<Producer>(id, name, email, password, villageName);
    
    if (userService.registerUser(producer)) {
        village->addProducerId(id);
        return true;
    }
    return false;
}

bool Marketplace::registerAdmin(const string& name, const string& email, const string& password) {
    int id = userService.getNextId();
    auto admin = make_shared<Admin>(id, name, email, password);
    return userService.registerUser(admin);
}

bool Marketplace::login(const string& email, const string& password) {
    auto user = userService.authenticate(email, password);
    if (user) {
        currentUser = user;
        return true;
    }
    return false;
}

void Marketplace::logout() {
    currentUser = nullptr;
}

shared_ptr<User> Marketplace::getCurrentUser() const {
    return currentUser;
}

bool Marketplace::addProduct(const string& name, double price, double quantity, const string& category) {
    if (!currentUser || currentUser->getRole() != "Producer") {
        return false;
    }

    auto producer = dynamic_pointer_cast<Producer>(currentUser);
    int pId = productService.getNextProductId();
    
    shared_ptr<Product> product = nullptr;
    if (category == "Fruit" || category == "Плодове") {
        product = make_shared<Fruit>(pId, name, price, quantity, producer->getId(), producer->getVillage());
    } else if (category == "Vegetable" || category == "Зеленчуци") {
        product = make_shared<Vegetable>(pId, name, price, quantity, producer->getId(), producer->getVillage());
    } else if (category == "DairyProduct" || category == "Млечни") {
        product = make_shared<DairyProduct>(pId, name, price, quantity, producer->getId(), producer->getVillage());
    } else if (category == "HandmadeProduct" || category == "Ръчно изработени") {
        product = make_shared<HandmadeProduct>(pId, name, price, quantity, producer->getId(), producer->getVillage());
    }

    if (product) {
        return productService.addProduct(product);
    }
    return false;
}

bool Marketplace::addVillage(const string& name, const string& region, int population) {
    if (!currentUser || currentUser->getRole() != "Admin") {
        return false;
    }
    int vId = productService.getNextVillageId();
    auto village = make_shared<Village>(vId, name, region, population);
    return productService.addVillage(village);
}

vector<shared_ptr<Product>> Marketplace::searchProducts(const string& query) const {
    return productService.searchProducts(query);
}

vector<shared_ptr<Product>> Marketplace::getProductsByCategory(const string& category) const {
    return productService.getProductsByCategory(category);
}

vector<shared_ptr<Product>> Marketplace::getProductsByVillage(const string& villageName) const {
    return productService.getProductsByVillage(villageName);
}

vector<shared_ptr<Product>> Marketplace::getAllProducts() const {
    return productService.getAllProducts();
}

vector<shared_ptr<Village>> Marketplace::getAllVillages() const {
    return productService.getAllVillages();
}

vector<shared_ptr<Product>> Marketplace::getCurrentProducerProducts() const {
    if (!currentUser || currentUser->getRole() != "Producer") {
        return {};
    }
    return productService.getProductsByProducer(currentUser->getId());
}

bool Marketplace::createOrder(const vector<pair<int, double>>& itemsToOrder) {
    if (!currentUser || currentUser->getRole() != "Customer") {
        cout << "Грешка: Трябва да сте влезли като Клиент, за да поръчате." << endl;
        return false;
    }
    if (itemsToOrder.empty()) {
        cout << "Грешка: Количката е празна." << endl;
        return false;
    }

    map<int, vector<shared_ptr<Product>>> ordersByProducer;

    // Валидация на количествата
    for (const auto& item : itemsToOrder) {
        int prodId = item.first;
        double qty = item.second;
        
        auto product = productService.getProductById(prodId);
        if (!product) {
            cout << "Грешка: Продукт с ID " << prodId << " не съществува." << endl;
            return false;
        }
        if (product->getQuantity() < qty) {
            cout << "Грешка: Недостатъчна наличност за '" << product->getName() 
                 << "' (Налични: " << product->getQuantity() << ", Поръчани: " << qty << ")" << endl;
            return false;
        }
    }

    // Намаляване на наличността и групиране по производител
    for (const auto& item : itemsToOrder) {
        int prodId = item.first;
        double qty = item.second;
        
        auto product = productService.getProductById(prodId);
        product->setQuantity(product->getQuantity() - qty);

        shared_ptr<Product> orderedProduct = nullptr;
        string cat = product->getCategory();
        if (cat == "Fruit") {
            orderedProduct = make_shared<Fruit>(product->getId(), product->getName(), product->getPrice(), qty, product->getProducerId(), product->getVillage());
        } else if (cat == "Vegetable") {
            orderedProduct = make_shared<Vegetable>(product->getId(), product->getName(), product->getPrice(), qty, product->getProducerId(), product->getVillage());
        } else if (cat == "DairyProduct") {
            orderedProduct = make_shared<DairyProduct>(product->getId(), product->getName(), product->getPrice(), qty, product->getProducerId(), product->getVillage());
        } else if (cat == "HandmadeProduct") {
            orderedProduct = make_shared<HandmadeProduct>(product->getId(), product->getName(), product->getPrice(), qty, product->getProducerId(), product->getVillage());
        }

        if (orderedProduct) {
            ordersByProducer[product->getProducerId()].push_back(orderedProduct);
        }
    }

    // Създаване на отделна поръчка за всеки производител
    for (const auto& pair : ordersByProducer) {
        int producerId = pair.first;
        const auto& prods = pair.second;
        int orderId = orderService.getNextOrderId();
        
        auto order = make_shared<Order>(orderId, currentUser->getId(), producerId, prods, OrderStatus::Pending);
        orderService.createOrder(order);
    }

    return true;
}

bool Marketplace::updateOrderStatus(int orderId, OrderStatus newStatus) {
    if (!currentUser) return false;
    
    auto order = orderService.getOrderById(orderId);
    if (!order) return false;

    if (currentUser->getRole() == "Producer" && order->getProducerId() == currentUser->getId()) {
        orderService.updateOrderStatus(orderId, newStatus);
        return true;
    }
    
    if (currentUser->getRole() == "Admin") {
        orderService.updateOrderStatus(orderId, newStatus);
        return true;
    }

    return false;
}

vector<shared_ptr<Order>> Marketplace::getCurrentUserOrders() const {
    if (!currentUser) return {};
    if (currentUser->getRole() == "Customer") {
        return orderService.getOrdersByCustomer(currentUser->getId());
    } else if (currentUser->getRole() == "Producer") {
        return orderService.getOrdersByProducer(currentUser->getId());
    }
    if (currentUser->getRole() == "Admin") {
        return orderService.getAllOrders();
    }
    return {};
}

bool Marketplace::leaveReview(int producerId, int rating, const string& comment) {
    if (!currentUser || currentUser->getRole() != "Customer") {
        return false;
    }
    if (rating < 1 || rating > 5) {
        cout << "Грешка: Оценката трябва да бъде между 1 и 5." << endl;
        return false;
    }
    
    int reviewId = reviewService.getNextReviewId();
    auto review = make_shared<Review>(reviewId, currentUser->getId(), producerId, rating, comment);
    return reviewService.addReview(review);
}

vector<shared_ptr<Review>> Marketplace::getProducerReviews(int producerId) const {
    return reviewService.getReviewsByProducer(producerId);
}

double Marketplace::getProducerAverageRating(int producerId) const {
    return reviewService.getAverageRatingForProducer(producerId);
}

vector<shared_ptr<User>> Marketplace::getAllUsers() const {
    if (!currentUser || currentUser->getRole() != "Admin") {
        return {};
    }
    return userService.getAllUsers();
}

void Marketplace::loadData() {
    userService.load("users.txt");
    productService.load("products.txt", "villages.txt");
    orderService.load("orders.txt");
    reviewService.load("reviews.txt");
}

void Marketplace::saveData() const {
    userService.save("users.txt");
    productService.save("products.txt", "villages.txt");
    orderService.save("orders.txt");
    reviewService.save("reviews.txt");
}
