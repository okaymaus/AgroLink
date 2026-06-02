#include "models/Village.h"
#include <sstream>

using namespace std;

Village::Village() : id(0), name(""), region(""), population(0) {}

Village::Village(int id, const string& name, const string& region, int population)
    : id(id), name(name), region(region), population(population) {}

int Village::getId() const { return id; }
void Village::setId(int id) { this->id = id; }

string Village::getName() const { return name; }
void Village::setName(const string& name) { this->name = name; }

string Village::getRegion() const { return region; }
void Village::setRegion(const string& region) { this->region = region; }

int Village::getPopulation() const { return population; }
void Village::setPopulation(int population) { this->population = population; }

vector<int> Village::getProducerIds() const { return producerIds; }
void Village::setProducerIds(const vector<int>& ids) { this->producerIds = ids; }

void Village::addProducerId(int producerId) {
    bool found = false;

    for (size_t i = 0; i < producerIds.size(); ++i) {
        if (producerIds[i] == producerId) {
            found = true;
            break;
        }
    }

    if (!found) {
        producerIds.push_back(producerId);
    }
}

void Village::serialize(ostream& os) const {
    os << id << "|" << name << "|" << region << "|" << population << "|";
    for (size_t i = 0; i < producerIds.size(); ++i) {
        os << producerIds[i];
        if (i < producerIds.size() - 1) {
            os << ",";
        }
    }
}

void Village::deserialize(istream& is) {
    string token;
    
    if (getline(is, token, '|')) {
        id = stoi(token);
    }
    getline(is, name, '|');
    getline(is, region, '|');
    if (getline(is, token, '|')) {
        population = stoi(token);
    }
    
    producerIds.clear();
    string idsToken;
    if (getline(is, idsToken, '|')) {
        if (idsToken.empty()) return;
        stringstream ss(idsToken);
        string idVal;
        while (getline(ss, idVal, ',')) {
            if (!idVal.empty()) {
                producerIds.push_back(stoi(idVal));
            }
        }
    }
}
