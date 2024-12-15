#include <iostream>
#include <unordered_map>
#include <string>
#include <memory> // For std::shared_ptr

// Forward declarations
class Unit;
class Product;
class Location;

// Enumerations for Status and Size
enum class Status { INVENTORY, TRANSIT, DELIVERY };

enum class Size { S, M, L };

// Product Class
class Product {
public:
    std::string id;
    double price;
    std::string description;
    double weight;
    Size size;

    Product(std::string id, double price, std::string description, double weight, Size size)
        : id(id), price(price), description(description), weight(weight), size(size) {}
};

// Unit Class
class Unit {
public:
    std::string id;
    std::string productId;
    std::string locationId;
    Status status;

    Unit(std::string id, std::string productId)
        : id(id), productId(productId), locationId(""), status(Status::INVENTORY) {}
};

// Location Class
class Location {
public:
    std::string id;
    Size type;

    Location(std::string id, Size type) : id(id), type(type) {}

    // Overloading hash function for unordered_map
    bool operator==(const Location& other) const {
        return id == other.id;
    }
};

// Custom hash function for Location
struct LocationHash {
    std::size_t operator()(const Location& loc) const {
        return std::hash<std::string>()(loc.id);
    }
};

// InventorySystem Class
class InventorySystem {
private:
    static std::unordered_map<std::string, std::shared_ptr<Product>> productMap;
    static std::unordered_map<Location, std::shared_ptr<Unit>, LocationHash> locationMap;

public:
    static void addProduct(std::shared_ptr<Product> product) {
        productMap[product->id] = product;
    }

    static std::shared_ptr<Product> getProduct(const std::string& productId) {
        return productMap[productId];
    }

    static void placeUnit(std::shared_ptr<Unit> unit) {
        for (auto& entry : locationMap) {
            // Simulating a lock mechanism (not implemented)
            if (entry.second == nullptr) {
                unit->locationId = entry.first.id;
                entry.second = unit;
                break;
            }
            // Release lock simulation
        }
    }

    static void removeUnit(const std::shared_ptr<Product>& product) {
        for (auto it = locationMap.begin(); it != locationMap.end(); ++it) {
            // Simulating a lock mechanism (not implemented)
            if (it->second != nullptr && it->second->productId == product->id) {
                locationMap.erase(it);
                break;
            }
            // Release lock simulation
        }
    }

    static const std::unordered_map<Location, std::shared_ptr<Unit>, LocationHash>& getShelvesStatus() {
        return locationMap;
    }

    static void updateStatus(std::shared_ptr<Unit> unit, Status status) {
        unit->status = status;
    }
};

// Static members initialization
std::unordered_map<std::string, std::shared_ptr<Product>> InventorySystem::productMap;
std::unordered_map<Location, std::shared_ptr<Unit>, LocationHash> InventorySystem::locationMap;

// Order Class
class Order {
public:
    std::unordered_map<std::shared_ptr<Product>, int> productCount;
};

// User Class
class User {
public:
    void addProduct(std::shared_ptr<Product> product) {
        InventorySystem::addProduct(product);
    }

    void executeOrder(const Order& order) {
        for (const auto& item : order.productCount) {
            for (int i = 0; i < item.second; ++i) {
                InventorySystem::removeUnit(item.first);
            }
        }
    }
};

// Main Function for Example Usage
int main() {
    // Create Products
    auto product1 = std::make_shared<Product>("P001", 10.5, "Sample Product 1", 2.0, Size::M);
    auto product2 = std::make_shared<Product>("P002", 20.0, "Sample Product 2", 3.0, Size::L);

    // Add Products
    User user;
    user.addProduct(product1);
    user.addProduct(product2);

    // Create Units
    auto unit1 = std::make_shared<Unit>("U001", "P001");
    auto unit2 = std::make_shared<Unit>("U002", "P002");

    // Place Units in InventorySystem
    InventorySystem::placeUnit(unit1);
    InventorySystem::placeUnit(unit2);

    // Check Shelf Status
    for (const auto& shelf : InventorySystem::getShelvesStatus()) {
        std::cout << "Location: " << shelf.first.id
                  << " | Unit: " << (shelf.second ? shelf.second->id : "Empty") << std::endl;
    }

    return 0;
}
