#pragma once
#include <memory>
#include <vector>
#include "repositories/Repository.h"
#include "models/Review.h"

using namespace std;

// Сервиз за отзиви
class ReviewService {
private:
    Repository<Review> reviewRepo;

public:
    ReviewService() = default;
    ~ReviewService() = default;

    bool addReview(const shared_ptr<Review>& review);
    vector<shared_ptr<Review>> getReviewsByProducer(int producerId) const;
    double getAverageRatingForProducer(int producerId) const;
    
    int getNextReviewId() const;
    bool save(const string& filename) const;
    bool load(const string& filename);
};
