#include "services/ProductService.h"
#include <cctype>

using namespace std;

// Помощна функция за безчувствено търсене (case-insensitive)
static bool containsIgnoreCase(const string& str, const string& query) {
    if (query.empty()) return true;
    if (query.size() > str.size()) return false;

    for (size_t i = 0; i <= str.size() - query.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < query.size(); ++j) {
            if (tolower(str[i + j]) != tolower(query[j])) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

static bool equalsIgnoreCase(const string& s1, const string& s2) {
    if (s1.size() != s2.size()) return false;
    return equal(s1.begin(), s1.end(), s2.begin(), [](char c1, char c2) {
        return tolower(c1) == tolower(c2);
    });
}

bool ProductService::addProduct(const shared_ptr<Product>& product) {
    if (!product) return false;
    productRepo.add(product);

    // Добавяне на производителя към селото
    auto village = getVillageByName(product->getVillage());
    if (village) {
        village->addProducerId(product->getProducerId());
    }
    return true;
}

bool ProductService::removeProduct(int productId) {
    return productRepo.removeById(productId);
}

shared_ptr<Product> ProductService::getProductById(int id) const {
    return productRepo.findById(id);
}

vector<shared_ptr<Product>> ProductService::getAllProducts() const {
    return productRepo.getAll();
}

vector<shared_ptr<Product>> ProductService::getProductsByProducer(int producerId) const {
    vector<shared_ptr<Product>> result;
    auto products = productRepo.getAll();
    for (const auto& prod : products) {
        if (prod && prod->getProducerId() == producerId) {
            result.push_back(prod);
        }
    }
    return result;
}

vector<shared_ptr<Product>> ProductService::getProductsByCategory(const string& category) const {
    vector<shared_ptr<Product>> result;
    auto products = productRepo.getAll();
    for (const auto& prod : products) {
        if (prod && equalsIgnoreCase(prod->getCategory(), category)) {
            result.push_back(prod);
        }
    }
    return result;
}

vector<shared_ptr<Product>> ProductService::getProductsByVillage(const string& villageName) const {
    vector<shared_ptr<Product>> result;
    auto products = productRepo.getAll();
    for (const auto& prod : products) {
        if (prod && equalsIgnoreCase(prod->getVillage(), villageName)) {
            result.push_back(prod);
        }
    }
    return result;
}

vector<shared_ptr<Product>> ProductService::searchProducts(const string& query) const {
    vector<shared_ptr<Product>> result;
    auto products = productRepo.getAll();
    for (const auto& prod : products) {
        if (prod && (containsIgnoreCase(prod->getName(), query) || containsIgnoreCase(prod->getVillage(), query))) {
            result.push_back(prod);
        }
    }
    return result;
}

int ProductService::getNextProductId() const {
    auto products = productRepo.getAll();
    if (products.empty()) return 1;
    
    int maxId = 0;
    for (const auto& p : products) {
        if (p->getId() > maxId) {
            maxId = p->getId();
        }
    }
    return maxId + 1;
}

bool ProductService::addVillage(const shared_ptr<Village>& village) {
    if (!village) return false;
    
    auto existing = getVillageByName(village->getName());
    if (existing) return false;

    villageRepo.add(village);
    return true;
}

shared_ptr<Village> ProductService::getVillageById(int id) const {
    return villageRepo.findById(id);
}

shared_ptr<Village> ProductService::getVillageByName(const string& name) const {
    auto villages = villageRepo.getAll();
    auto it = find_if(villages.begin(), villages.end(), [&name](const auto& v) {
        return equalsIgnoreCase(v->getName(), name);
    });
    if (it != villages.end()) {
        return *it;
    }
    return nullptr;
}

vector<shared_ptr<Village>> ProductService::getAllVillages() const {
    return villageRepo.getAll();
}

int ProductService::getNextVillageId() const {
    auto villages = villageRepo.getAll();
    if (villages.empty()) return 1;
    
    int maxId = 0;
    for (const auto& v : villages) {
        if (v->getId() > maxId) {
            maxId = v->getId();
        }
    }
    return maxId + 1;
}

bool ProductService::save(const string& prodFile, const string& villageFile) const {
    return productRepo.saveToFile(prodFile) && villageRepo.saveToFile(villageFile);
}

bool ProductService::load(const string& prodFile, const string& villageFile) {
    return productRepo.loadFromFile(prodFile) && villageRepo.loadFromFile(villageFile);
}
