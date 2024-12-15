#include <iostream>
using namespace std;

class InventorySystem {
  static map<string, Product> productList;
  static map<Location, Unit> locationMap;
  
  public:
  static void addProduct(Product product) {
      productList.insert({product.id, product});
  }
  
  static Product getProduct(string productId) {
      return productList[productId];
  }
  
  static void placeUnit(Unit unit) {
      for(auto entry: LocationMap) {
          // if (SimpleStrategy.works())
          // get lockk on entry.getKey()
          if(entry.second == null) {
              unit.locationId = entry.first.id;
          }
          // release lock
      }
  }
  
  static void removeUnit(Product product) {
      for(auto entry: LocationMap) {
          // if (SimpleStrategy.works())
          // get lockk on entry.getKey()
          if(entry.second != null && product.id == entry.second.productId) {
              // remove Unit
              locationMap.remove(entry.first);
          }
          // release lock
      }
  }
  
  static map<Location, Unit> getShelvesStatus() {
      return locationMap;
  }
  
  static void updateStatus(Unit unit, Status status) {
      unit.status = status;
  }
};

class SmartStrategy {
    
};

class SimpleStrategy {
    
};

class Unit {
    string id;
    string productId;
    string locationId;
    Status status;
};

class Location {
    string id;
    Size size;
};

enum Status {
    INVENTORY, TRANSIT, DELIVERY
}

class Product {
    string id;
    double price;
    string description;
    double weight;
    Size size;
    
    public:
    Product(string id, double price, string description, double weight, Size size) {
        this->id = id;
        this->price = price;
        this->description = description;
        this->weight = weight;
        this->size = size;
    }
};

enum Size {
    S, M, L;
}

class User {
    public:
    void addProduct() {
        InventorySystem.addProduct(new Product("", 0, "", 0, Size.L));
    }
    
    void executeOrder(Order order) {
        for(auto item: order.productCount) {
            for(int i = 0; i < item.second; i++) {
                InventorySystem.removeUnit(item.first);
            }
        }
    }
};

class Order {
    map<Product, int> productCount;
};

int main() {
    cout << "Inventory Management System";
    return 0;
}
