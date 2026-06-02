#include "marketplace/Marketplace.h"
#include "menu/ConsoleMenu.h"
#include <iostream>
#include <fstream>

using namespace std;

void seedInitialData(Marketplace& marketplace) {
    cout << "Зареждане на първоначални данни за демонстрация..." << endl;
    
    // Регистрация на админ
    marketplace.registerAdmin("Администратор", "admin@agrolink.bg", "admin123");
    
    // Влизане като админ за добавяне на села
    marketplace.login("admin@agrolink.bg", "admin123");
    marketplace.addVillage("Татарево", "Пловдив", 520);
    marketplace.addVillage("Бачково", "Пловдив", 310);
    marketplace.addVillage("Широка лъка", "Смолян", 480);
    marketplace.logout();

    // Регистрация на производители
    marketplace.registerProducer("Иван Георгиев", "ivan@gmail.com", "ivan123", "Татарево");
    marketplace.registerProducer("Мария Петрова", "maria@gmail.com", "maria123", "Бачково");
    marketplace.registerProducer("Стоян Смолянов", "stoyan@gmail.com", "stoyan123", "Широка лъка");

    // Регистрация на клиенти
    marketplace.registerCustomer("Георги Димитров", "gosho@gmail.com", "gosho123");
    marketplace.registerCustomer("Елена Николова", "elena@gmail.com", "elena123");

    // Добавяне на продукти от Иван
    marketplace.login("ivan@gmail.com", "ivan123");
    marketplace.addProduct("Розови домати", 3.80, 50.0, "Vegetable");
    marketplace.addProduct("Сладки череши", 4.50, 30.0, "Fruit");
    marketplace.logout();

    // Добавяне на продукти от Мария
    marketplace.login("maria@gmail.com", "maria123");
    marketplace.addProduct("Домашно овче сирене", 18.00, 15.0, "DairyProduct");
    marketplace.addProduct("Кисело мляко (овче)", 3.20, 25.0, "DairyProduct");
    marketplace.logout();

    // Добавяне на продукти от Стоян
    marketplace.login("stoyan@gmail.com", "stoyan123");
    marketplace.addProduct("Плетени вълнени терлици", 12.00, 10.0, "HandmadeProduct");
    marketplace.addProduct("Буркан боров мед", 9.50, 20.0, "HandmadeProduct");
    marketplace.logout();

    // Записване на първоначалните данни
    marketplace.saveData();
    cout << "Първоначалните данни са заредени успешно." << endl;
}

int main() {
    // Поддръжка на кирилица в конзолата на Windows
#ifdef _WIN32
    system("chcp 65001 > nul");
#endif

    Marketplace marketplace;
    
    // Проверка дали има съществуващи данни
    ifstream checkFile("users.txt");
    if (!checkFile.good()) {
        seedInitialData(marketplace);
    } else {
        marketplace.loadData();
    }
    checkFile.close();

    MainMenu menu(marketplace);
    menu.show();

    return 0;
}
