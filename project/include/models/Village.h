#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Клас за село
class Village {
private:
    int id;
    string name;
    string region;
    int population;
    vector<int> producerIds;

public:
    Village();
    Village(int id, const string& name, const string& region, int population);
    ~Village() = default;

    // Гетъри и сетъри
    int getId() const;
    void setId(int id);

    string getName() const;
    void setName(const string& name);

    string getRegion() const;
    void setRegion(const string& region);

    int getPopulation() const;
    void setPopulation(int population);

    vector<int> getProducerIds() const;
    void setProducerIds(const vector<int>& ids);
    void addProducerId(int producerId);

    void serialize(ostream& os) const;
    void deserialize(istream& is);
};
