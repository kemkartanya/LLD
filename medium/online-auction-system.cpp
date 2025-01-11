#include <iostream>
#include <chrono>
#include <mutex>
#include <vector>
#include <thread>
#include <map>
#include <string>
#include <memory>
using namespace std;

class User {
private:
    string id, username, email;

public:
    User(string id, string username, string email) 
        : id(id), username(username), email(email) {}

    string getId() const { return id; }
};

class Bid {
private:
    string id;
    shared_ptr<User> bidder;
    double amount;
    chrono::system_clock::time_point timestamp;

public:
    Bid(string id, shared_ptr<User> bidder, double amount) 
        : id(id), bidder(bidder), amount(amount), timestamp(chrono::system_clock::now()) {}

    double getAmount() const { return amount; }
    shared_ptr<User> getBidder() const { return bidder; }
};

enum class AuctionStatus {
    ACTIVE,
    CLOSED
};

class AuctionListing {
private:
    string id;
    string itemName;
    string description;
    double startingPrice;
    long duration; // in milliseconds
    shared_ptr<User> seller;
    AuctionStatus status;
    double currentHighestBid;
    shared_ptr<User> currentHighestBidder;
    vector<shared_ptr<Bid>> bids;
    mutex mutex_;

public:
    AuctionListing(string id, string itemName, string description, double startingPrice, long duration, shared_ptr<User> seller)
        : id(id), itemName(itemName), description(description), startingPrice(startingPrice),
          duration(duration), seller(seller), status(AuctionStatus::ACTIVE), 
          currentHighestBid(startingPrice), currentHighestBidder(nullptr) {}

    void placeBid(shared_ptr<Bid> bid) {
        lock_guard<mutex> lock(mutex_);
        if (status == AuctionStatus::ACTIVE && bid->getAmount() > currentHighestBid) {
            currentHighestBid = bid->getAmount();
            currentHighestBidder = bid->getBidder();
            bids.push_back(bid);
            notifyObservers();
        }
    }

    void closeAuction() {
        lock_guard<mutex> lock(mutex_);
        if (status == AuctionStatus::ACTIVE) {
            status = AuctionStatus::CLOSED;
            notifyObservers();
        }
    }

    string getId() const { return id; }
    string getItemName() const { return itemName; }
    string getDescription() const { return description; }
    long getDuration() const { return duration; }

private:
    void notifyObservers() {
        // Placeholder for notifying bidders about updates.
    }
};

class AuctionSystem {
private:
    static unique_ptr<AuctionSystem> instance;
    map<string, shared_ptr<User>> users;
    map<string, shared_ptr<AuctionListing>> auctionListings;
    mutex mutex_;

    AuctionSystem() = default;

public:
    static AuctionSystem& getInstance() {
        static AuctionSystem instance;
        return instance;
    }

    void registerUser(shared_ptr<User> user) {
        lock_guard<mutex> lock(mutex_);
        users[user->getId()] = user;
    }

    shared_ptr<User> getUser(const string& userId) {
        lock_guard<mutex> lock(mutex_);
        auto it = users.find(userId);
        if (it != users.end()) {
            return it->second;
        }
        return nullptr;
    }

    void createAuctionListing(shared_ptr<AuctionListing> auctionListing) {
        lock_guard<mutex> lock(mutex_);
        auctionListings[auctionListing->getId()] = auctionListing;
        startAuctionTimer(auctionListing);
    }

    vector<shared_ptr<AuctionListing>> searchAuctionListings(const string& keyword) {
        lock_guard<mutex> lock(mutex_);
        vector<shared_ptr<AuctionListing>> matchingListings;
        for (const auto& pair : auctionListings) {
            const auto& listing = pair.second;
            if (listing->getItemName().find(keyword) != string::npos || 
                listing->getDescription().find(keyword) != string::npos) {
                matchingListings.push_back(listing);
            }
        }
        return matchingListings;
    }

    void placeBid(const string& auctionListingId, shared_ptr<Bid> bid) {
        lock_guard<mutex> lock(mutex_);
        auto it = auctionListings.find(auctionListingId);
        if (it != auctionListings.end()) {
            it->second->placeBid(bid);
        }
    }

private:
    void startAuctionTimer(shared_ptr<AuctionListing> auctionListing) {
        thread timerThread([auctionListing]() {
            this_thread::sleep_for(chrono::milliseconds(auctionListing->getDuration()));
            auctionListing->closeAuction();
        });
        timerThread.detach();
    }
};

unique_ptr<AuctionSystem> AuctionSystem::instance = nullptr;

int main() {
    auto& auctionSystem = AuctionSystem::getInstance();

    // Register users
    auto user1 = make_shared<User>("1", "John Doe", "john@example.com");
    auto user2 = make_shared<User>("2", "Jane Smith", "jane@example.com");
    auctionSystem.registerUser(user1);
    auctionSystem.registerUser(user2);

    // Create auction listings
    auto listing1 = make_shared<AuctionListing>("1", "Item 1", "Description 1", 100.0, 60000, user1);
    auto listing2 = make_shared<AuctionListing>("2", "Item 2", "Description 2", 50.0, 120000, user2);
    auctionSystem.createAuctionListing(listing1);
    auctionSystem.createAuctionListing(listing2);

    // Search auction listings
    vector<shared_ptr<AuctionListing>> searchResults = auctionSystem.searchAuctionListings("Item");
    cout << "Search Results:\n";
    for (const auto& listing : searchResults) {
        cout << " - " << listing->getItemName() << "\n";
    }

    // Place bids
    auto bid1 = make_shared<Bid>("1", user2, 150.0);
    auto bid2 = make_shared<Bid>("2", user1, 200.0);
    auctionSystem.placeBid(listing1->getId(), bid1);
    auctionSystem.placeBid(listing1->getId(), bid2);

    this_thread::sleep_for(chrono::milliseconds(1000));

    return 0;
}
