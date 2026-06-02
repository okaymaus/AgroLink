#include "services/ReviewService.h"
#include <numeric>

using namespace std;

bool ReviewService::addReview(const shared_ptr<Review>& review) {
    if (!review) return false;
    reviewRepo.add(review);
    return true;
}

vector<shared_ptr<Review>> ReviewService::getReviewsByProducer(int producerId) const {
    vector<shared_ptr<Review>> result;
    auto reviews = reviewRepo.getAll();
    for (const auto& rev : reviews) {
        if (rev && rev->getProducerId() == producerId) {
            result.push_back(rev);
        }
    }
    return result;
}

double ReviewService::getAverageRatingForProducer(int producerId) const {
    auto reviews = getReviewsByProducer(producerId);
    if (reviews.empty()) return 0.0;
    
    double sum = 0.0;
    for (const auto& rev : reviews) {
        sum += rev->getRating();
    }
    return sum / reviews.size();
}

int ReviewService::getNextReviewId() const {
    auto reviews = reviewRepo.getAll();
    if (reviews.empty()) return 1;
    
    int maxId = 0;
    for (const auto& r : reviews) {
        if (r->getId() > maxId) {
            maxId = r->getId();
        }
    }
    return maxId + 1;
}

bool ReviewService::save(const string& filename) const {
    return reviewRepo.saveToFile(filename);
}

bool ReviewService::load(const string& filename) {
    return reviewRepo.loadFromFile(filename);
}
