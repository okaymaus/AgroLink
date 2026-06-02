#pragma once
#include <string>
#include <iostream>

using namespace std;

// Клас за отзив
class Review {
private:
    int id;
    int customerId;
    int producerId;
    int rating;
    string comment;

public:
    Review();
    Review(int id, int customerId, int producerId, int rating, const string& comment);
    ~Review() = default;

    // Гетъри и сетъри
    int getId() const;
    void setId(int id);

    int getCustomerId() const;
    void setCustomerId(int customerId);

    int getProducerId() const;
    void setProducerId(int producerId);

    int getRating() const;
    void setRating(int rating);

    string getComment() const;
    void setComment(const string& comment);

    void serialize(ostream& os) const;
    void deserialize(istream& is);
};
