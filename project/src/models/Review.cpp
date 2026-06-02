#include "models/Review.h"
#include <sstream>

using namespace std;

Review::Review() : id(0), customerId(0), producerId(0), rating(5), comment("") {}

Review::Review(int id, int customerId, int producerId, int rating, const string& comment)
    : id(id), customerId(customerId), producerId(producerId), rating(rating), comment(comment) {}

int Review::getId() const { return id; }
void Review::setId(int id) { this->id = id; }

int Review::getCustomerId() const { return customerId; }
void Review::setCustomerId(int customerId) { this->customerId = customerId; }

int Review::getProducerId() const { return producerId; }
void Review::setProducerId(int producerId) { this->producerId = producerId; }

int Review::getRating() const { return rating; }
void Review::setRating(int rating) { this->rating = rating; }

string Review::getComment() const { return comment; }
void Review::setComment(const string& comment) { this->comment = comment; }

void Review::serialize(ostream& os) const {
    os << id << "|" << customerId << "|" << producerId << "|" << rating << "|" << comment;
}

void Review::deserialize(istream& is) {
    string token;
    if (getline(is, token, '|')) {
        id = stoi(token);
    }
    if (getline(is, token, '|')) {
        customerId = stoi(token);
    }
    if (getline(is, token, '|')) {
        producerId = stoi(token);
    }
    if (getline(is, token, '|')) {
        rating = stoi(token);
    }
    getline(is, comment, '|');
}
