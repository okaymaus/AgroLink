#pragma once
#include <memory>
#include <vector>
#include <string>
#include "repositories/Repository.h"
#include "models/Product.h"
#include "models/Village.h"

using namespace std;

// Сервиз за продукти
class ProductService {
private:
    Repository<Product> productRepo;
    Repository<Village> villageRepo;

public:
    ProductService() = default;
    ~ProductService() = default;

    // Методи за продукти
    bool addProduct(const shared_ptr<Product>& product);
    bool removeProduct(int productId);
    shared_ptr<Product> getProductById(int id) const;
    vector<shared_ptr<Product>> getAllProducts() const;
    vector<shared_ptr<Product>> getProductsByProducer(int producerId) const;
    vector<shared_ptr<Product>> getProductsByCategory(const string& category) const;
    vector<shared_ptr<Product>> getProductsByVillage(const string& villageName) const;
    vector<shared_ptr<Product>> searchProducts(const string& query) const;
    
    int getNextProductId() const;

    // Методи за села
    bool addVillage(const shared_ptr<Village>& village);
    shared_ptr<Village> getVillageById(int id) const;
    shared_ptr<Village> getVillageByName(const string& name) const;
    vector<shared_ptr<Village>> getAllVillages() const;
    
    int getNextVillageId() const;

    // Запис и зареждане
    bool save(const string& prodFile, const string& villageFile) const;
    bool load(const string& prodFile, const string& villageFile);
};
