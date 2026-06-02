#pragma once
#include "marketplace/Marketplace.h"

using namespace std;

// Абстрактен базов клас за меню
class ConsoleMenu {
protected:
    Marketplace& marketplace;

public:
    ConsoleMenu(Marketplace& mp);
    virtual ~ConsoleMenu() = default;
    virtual void show() = 0;
};

// Главно меню (вход/регистрация)
class MainMenu : public ConsoleMenu {
private:
    void handleLogin();
    void handleRegister();

public:
    MainMenu(Marketplace& mp);
    void show() override;
};

// Меню за клиент
class CustomerMenu : public ConsoleMenu {
private:
    void handleBrowseProducts();
    void handleSearchProducts();
    void handleCreateOrder();
    void handleLeaveReview();
    void handleViewOrderHistory();

public:
    CustomerMenu(Marketplace& mp);
    void show() override;
};

// Меню за производител
class ProducerMenu : public ConsoleMenu {
private:
    void handleAddProduct();
    void handleViewMyProducts();
    void handleManageOrders();
    void handleViewReviews();

public:
    ProducerMenu(Marketplace& mp);
    void show() override;
};

// Меню за админ
class AdminMenu : public ConsoleMenu {
private:
    void handleAddVillage();
    void handleViewAllUsers();
    void handleViewAllOrders();

public:
    AdminMenu(Marketplace& mp);
    void show() override;
};
