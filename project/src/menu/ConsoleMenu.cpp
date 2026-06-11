#include "menu/ConsoleMenu.h"
#include "models/Producer.h"
#include <iostream>
#include <limits>
#include <iomanip>

using namespace std;

// Помощни функции за четене на данни
static string readString() {
    string str;
    getline(cin, str);
    return str;
}

static double readDouble() {
    double val;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Невалидно число. Опитайте отново: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return val;
}

static int readInt() {
    int val;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Невалидно цяло число. Опитайте отново: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return val;
}

ConsoleMenu::ConsoleMenu(Marketplace& mp) : marketplace(mp) {}

// Главно Меню

MainMenu::MainMenu(Marketplace& mp) : ConsoleMenu(mp) {}

void MainMenu::show() {
    while (true) {
        cout << "\n============================================\n";
        cout << "          ДОБРЕ ДОШЛИ В AGROLINK!          \n";
        cout << "============================================\n";
        cout << "1. Вход в системата (Login)\n";
        cout << "2. Регистрация (Register)\n";
        cout << "3. Изход (Exit)\n";
        cout << "Изберете опция: ";
        
        int choice = readInt();
        if (choice == 1) {
            handleLogin();
        } else if (choice == 2) {
            handleRegister();
        } else if (choice == 3) {
            cout << "Благодарим ви, че използвахте AgroLink! Довиждане.\n";
            marketplace.saveData();
            break;
        } else {
            cout << "Невалидна опция. Моля, изберете отново.\n";
        }
    }
}

void MainMenu::handleLogin() {
    cout << "\n--- ВХОД В СИСТЕМАТА ---\n";
    cout << "Емейл: ";
    string email = readString();
    cout << "Парола: ";
    string password = readString();

    if (marketplace.login(email, password)) {
        auto user = marketplace.getCurrentUser();
        cout << "\nУспешен вход! Добре дошли, " << user->getName() << "!\n";
        
        string role = user->getRole();
        if (role == "Customer") {
            CustomerMenu menu(marketplace);
            menu.show();
        } else if (role == "Producer") {
            ProducerMenu menu(marketplace);
            menu.show();
        } else if (role == "Admin") {
            AdminMenu menu(marketplace);
            menu.show();
        }
    } else {
        cout << "Грешен емейл или парола!\n";
    }
}

void MainMenu::handleRegister() {
    cout << "\n--- РЕГИСТРАЦИЯ ---\n";
    cout << "Име: ";
    string name = readString();
    cout << "Емейл: ";
    string email = readString();
    cout << "Парола: ";
    string password = readString();
    
    cout << "Изберете тип профил:\n";
    cout << "1. Клиент\n";
    cout << "2. Производител\n";
    cout << "3. Администратор\n";
    cout << "Избор: ";
    int type = readInt();

    bool success = false;
    if (type == 1) {
        success = marketplace.registerCustomer(name, email, password);
    } else if (type == 2) {
        cout << "Въведете село: ";
        string village = readString();
        success = marketplace.registerProducer(name, email, password, village);
    } else if (type == 3) {
        success = marketplace.registerAdmin(name, email, password);
    } else {
        cout << "Невалиден избор.\n";
        return;
    }

    if (success) {
        cout << "Регистрацията беше успешна!\n";
        marketplace.saveData();
    } else {
        cout << "Грешка при регистрацията!\n";
    }
}

//Меню Клиент

CustomerMenu::CustomerMenu(Marketplace& mp) : ConsoleMenu(mp) {}

void CustomerMenu::show() {
    while (marketplace.getCurrentUser()) {
        cout << "\n--------------------------------------------\n";
        cout << "             МЕНЮ НА КЛИЕНТА                \n";
        cout << "--------------------------------------------\n";
        cout << "1. Преглед на всички продукти\n";
        cout << "2. Търсене на продукти\n";
        cout << "3. Създаване на поръчка\n";
        cout << "4. Оставяне на отзив\n";
        cout << "5. История на поръчките\n";
        cout << "6. Изход (Logout)\n";
        cout << "Изберете опция: ";

        int choice = readInt();
        if (choice == 1) {
            handleBrowseProducts();
        } else if (choice == 2) {
            handleSearchProducts();
        } else if (choice == 3) {
            handleCreateOrder();
        } else if (choice == 4) {
            handleLeaveReview();
        } else if (choice == 5) {
            handleViewOrderHistory();
        } else if (choice == 6) {
            marketplace.logout();
            cout << "Излязохте успешно.\n";
        } else {
            cout << "Невалидна опция.\n";
        }
    }
}

void CustomerMenu::handleBrowseProducts() {
    cout << "\n--- ВСИЧКИ НАЛИЧНИ ПРОДУКТИ ---\n";
    auto products = marketplace.getAllProducts();
    if (products.empty()) {
        cout << "Няма налични продукти.\n";
        return;
    }
    for (const auto& prod : products) {
        if (prod) {
            prod->displayInfo();
        }
    }
}

void CustomerMenu::handleSearchProducts() {
    cout << "\nВъведете ключова дума за търсене (продукт или село): ";
    string query = readString();
    
    auto results = marketplace.searchProducts(query);
    if (results.empty()) {
        cout << "Няма намерени продукти.\n";
        return;
    }
    
    cout << "\n--- РЕЗУЛТАТИ ---\n";
    for (const auto& prod : results) {
        if (prod) {
            prod->displayInfo();
        }
    }
}

void CustomerMenu::handleCreateOrder() {
    vector<pair<int, double>> cart;
    handleBrowseProducts();
    
    while (true) {
        cout << "\nID на продукт за добавяне (или 0 за край): ";
        int id = readInt();
        if (id == 0) break;
        
        cout << "Количество: ";
        double qty = readDouble();
        
        if (qty <= 0) {
            cout << "Количеството трябва да е над 0.\n";
            continue;
        }
        
        cart.push_back({id, qty});
        cout << "Продуктът е добавен.\n";
    }

    if (cart.empty()) {
        cout << "Количката е празна.\n";
        return;
    }

    if (marketplace.createOrder(cart)) {
        cout << "Поръчката беше създадена успешно!\n";
        marketplace.saveData();
    } else {
        cout << "Грешка при създаване на поръчка.\n";
    }
}

void CustomerMenu::handleLeaveReview() {
    cout << "\nВъведете ID на производител: ";
    int pId = readInt();
    
    cout << "Въведете оценка (1-5): ";
    int rating = readInt();
    
    cout << "Коментар: ";
    string comment = readString();

    if (marketplace.leaveReview(pId, rating, comment)) {
        cout << "Отзивът е добавен!\n";
        marketplace.saveData();
    } else {
        cout << "Грешка при отзива.\n";
    }
}

void CustomerMenu::handleViewOrderHistory() {
    cout << "\n--- ИСТОРИЯ НА ПОРЪЧКИТЕ ---\n";
    auto orders = marketplace.getCurrentUserOrders();
    if (orders.empty()) {
        cout << "Нямате поръчки.\n";
        return;
    }
    for (const auto& ord : orders) {
        if (ord) {
            ord->displayOrder();
            cout << "---------------------------------\n";
        }
    }
}

//Меню Производител

ProducerMenu::ProducerMenu(Marketplace& mp) : ConsoleMenu(mp) {}

void ProducerMenu::show() {
    while (marketplace.getCurrentUser()) {
        cout << "\n--------------------------------------------\n";
        cout << "            МЕНЮ НА ПРОИЗВОДИТЕЛЯ           \n";
        cout << "--------------------------------------------\n";
        cout << "1. Добавяне на продукт\n";
        cout << "2. Преглед на моите продукти\n";
        cout << "3. Управление на поръчките\n";
        cout << "4. Преглед на моите отзиви\n";
        cout << "5. Изход (Logout)\n";
        cout << "Изберете опция: ";

        int choice = readInt();
        if (choice == 1) {
            handleAddProduct();
        } else if (choice == 2) {
            handleViewMyProducts();
        } else if (choice == 3) {
            handleManageOrders();
        } else if (choice == 4) {
            handleViewReviews();
        } else if (choice == 5) {
            marketplace.logout();
            cout << "Излязохте успешно.\n";
        } else {
            cout << "Невалидна опция.\n";
        }
    }
}

void ProducerMenu::handleAddProduct() {
    cout << "\n--- ДОБАВЯНЕ НА ПРОДУКТ ---\n";
    cout << "Име на продукта: ";
    string name = readString();
    cout << "Цена: ";
    double price = readDouble();
    cout << "Количество: ";
    double qty = readDouble();
    
    cout << "Категория (1. Плодове, 2. Зеленчуци, 3. Млечни, 4. Ръчно изработени): ";
    int catChoice = readInt();
    
    string category;
    if (catChoice == 1) category = "Fruit";
    else if (catChoice == 2) category = "Vegetable";
    else if (catChoice == 3) category = "DairyProduct";
    else if (catChoice == 4) category = "HandmadeProduct";
    else {
        cout << "Невалиден избор.\n";
        return;
    }

    if (marketplace.addProduct(name, price, qty, category)) {
        cout << "Продуктът е добавен!\n";
        marketplace.saveData();
    } else {
        cout << "Грешка при добавяне.\n";
    }
}

void ProducerMenu::handleViewMyProducts() {
    cout << "\n--- МОИТЕ ПРОДУКТИ ---\n";
    auto products = marketplace.getCurrentProducerProducts();
    if (products.empty()) {
        cout << "Нямате добавени продукти.\n";
        return;
    }
    for (const auto& prod : products) {
        if (prod) {
            prod->displayInfo();
        }
    }
}

void ProducerMenu::handleManageOrders() {
    cout << "\n--- ПОРЪЧКИ КЪМ МЕН ---\n";
    auto orders = marketplace.getCurrentUserOrders();
    if (orders.empty()) {
        cout << "Няма поръчки към вас.\n";
        return;
    }
    
    for (const auto& ord : orders) {
        if (ord) {
            ord->displayOrder();
            cout << "---------------------------------\n";
        }
    }

    cout << "ID на поръчка за статус промяна (0 за изход): ";
    int orderId = readInt();
    if (orderId == 0) return;

    cout << "Нов статус (1. Приета, 2. Отхвърлена, 3. Завършена): ";
    int statusChoice = readInt();

    OrderStatus newStatus;
    if (statusChoice == 1) newStatus = OrderStatus::Accepted;
    else if (statusChoice == 2) newStatus = OrderStatus::Rejected;
    else if (statusChoice == 3) newStatus = OrderStatus::Completed;
    else {
        cout << "Невалиден избор.\n";
        return;
    }

    if (marketplace.updateOrderStatus(orderId, newStatus)) {
        cout << "Статусът е променен!\n";
        marketplace.saveData();
    } else {
        cout << "Грешка при промяна.\n";
    }
}

void ProducerMenu::handleViewReviews() {
    auto user = marketplace.getCurrentUser();
    if (!user) return;
    
    cout << "\n--- МОИТЕ ОТЗИВИ ---\n";
    double avg = marketplace.getProducerAverageRating(user->getId());
    cout << "Средна оценка: " << fixed << setprecision(1) << avg << " / 5.0\n\n";

    auto reviews = marketplace.getProducerReviews(user->getId());
    if (reviews.empty()) {
        cout << "Няма отзиви.\n";
        return;
    }
    
    for (const auto& rev : reviews) {
        if (rev) {
            cout << "Оценка: " << rev->getRating() << " / 5\n";
            cout << "Коментар: " << rev->getComment() << "\n";
            cout << "---------------------------\n";
        }
    }
}

//Меню Админ

AdminMenu::AdminMenu(Marketplace& mp) : ConsoleMenu(mp) {}

void AdminMenu::show() {
    while (marketplace.getCurrentUser()) {
        cout << "\n--------------------------------------------\n";
        cout << "            МЕНЮ НА АДМИНИСТРАТОРА          \n";
        cout << "--------------------------------------------\n";
        cout << "1. Добавяне на село\n";
        cout << "2. Преглед на потребители\n";
        cout << "3. Преглед на всички поръчки\n";
        cout << "4. Преглед на всички села\n";
        cout << "5. Изход (Logout)\n";
        cout << "Изберете опция: ";

        int choice = readInt();
        if (choice == 1) {
            handleAddVillage();
        } else if (choice == 2) {
            handleViewAllUsers();
        } else if (choice == 3) {
            handleViewAllOrders();
        } else if (choice == 4) {
            cout << "\n--- ВСИЧКИ СЕЛА ---\n";
            auto villages = marketplace.getAllVillages();
            if (villages.empty()) {
                cout << "Няма села.\n";
            } else {
                for (const auto& v : villages) {
                    if (v) {
                        cout << "Село: " << v->getName() 
                             << " | Област: " << v->getRegion() 
                             << " | Население: " << v->getPopulation() 
                             << " | Производители: " << v->getProducerIds().size() << endl;
                    }
                }
            }
        } else if (choice == 5) {
            marketplace.logout();
            cout << "Излязохте успешно.\n";
        } else {
            cout << "Невалидна опция.\n";
        }
    }
}

void AdminMenu::handleAddVillage() {
    cout << "\n--- ДОБАВЯНЕ НА СЕЛО ---\n";
    cout << "Име на селото: ";
    string name = readString();
    cout << "Област: ";
    string region = readString();
    cout << "Население: ";
    int pop = readInt();

    if (marketplace.addVillage(name, region, pop)) {
        cout << "Селото е добавено успешно!\n";
        marketplace.saveData();
    } else {
        cout << "Грешка при добавяне.\n";
    }
}

void AdminMenu::handleViewAllUsers() {
    cout << "\n--- ПОТРЕБИТЕЛИ В СИСТЕМАТА ---\n";
    auto users = marketplace.getAllUsers();
    if (users.empty()) {
        cout << "Няма регистрирани потребители.\n";
        return;
    }
    for (const auto& u : users) {
        if (u) {
            u->displayInfo();
        }
    }
}

void AdminMenu::handleViewAllOrders() {
    cout << "\n--- ВСИЧКИ ПОРЪЧКИ ---\n";
    auto orders = marketplace.getCurrentUserOrders();
    if (orders.empty()) {
        cout << "Няма поръчки.\n";
        return;
    }
    for (const auto& ord : orders) {
        if (ord) {
            ord->displayOrder();
            cout << "---------------------------------\n";
        }
    }
}
