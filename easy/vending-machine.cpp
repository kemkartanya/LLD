#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>

using namespace std;

// Strategy Pattern for Payment
class PaymentStrategy {
public:
    virtual void addPayment(float amount) = 0;
    virtual float getBalance() const = 0;
    virtual void resetBalance() = 0;
    virtual void processPayment(float amount) = 0;
    virtual ~PaymentStrategy() = default;
};

class CoinPayment : public PaymentStrategy {
    float balance = 0.0f;

public:
    void addPayment(float amount) override {
        balance += amount;
    }

    float getBalance() const override {
        return balance;
    }

    void resetBalance() override {
        balance = 0.0f;
    }

    void processPayment(float amount) override {
        balance -= amount;
    }
};

class CardPayment : public PaymentStrategy {
    float balance = 0.0f;

public:
    void addPayment(float amount) override {
        balance += amount;
    }

    float getBalance() const override {
        return balance;
    }

    void resetBalance() override {
        balance = 0.0f;
    }

    void processPayment(float amount) override {
        balance -= amount;
    }
};

// Observer Pattern for Display
class DisplayObserver {
public:
    virtual void update(const string& message) = 0;
    virtual ~DisplayObserver() = default;
};

class Display : public DisplayObserver {
public:
    void update(const string& message) override {
        cout << "Display: " << message << endl;
    }

    void displayPrice(float price) const {
        cout << "Price: " << price << endl;
    }

    void displayBalance(float balance) const {
        cout << "Balance: " << balance << endl;
    }
};

// Factory Method for Item Creation
class Item {
    string code;
    float price;
    int quantity;

public:
    Item(string code, float price, int quantity)
        : code(move(code)), price(price), quantity(quantity) {}

    const string& getCode() const { return code; }
    float getPrice() const { return price; }
    int getQuantity() const { return quantity; }

    void decrementQuantity() {
        if (quantity > 0) {
            --quantity;
        }
    }
};

class SnackItem : public Item {
public:
    SnackItem(const string& code, float price, int quantity)
        : Item(code, price, quantity) {}
};

class DrinkItem : public Item {
public:
    DrinkItem(const string& code, float price, int quantity)
        : Item(code, price, quantity) {}
};

class ItemFactory {
public:
    static shared_ptr<Item> createItem(const string& type, const string& code, float price, int quantity) {
        if (type == "snack") {
            return make_shared<SnackItem>(code, price, quantity);
        } else if (type == "drink") {
            return make_shared<DrinkItem>(code, price, quantity);
        } else {
            throw invalid_argument("Invalid item type");
        }
    }
};

// Dispenser Class
class Dispenser {
public:
    void dispenseItem(const shared_ptr<Item>& item) const {
        cout << "Dispensing item: " << item->getCode() << endl;
    }
};

// Coin Acceptor
class CoinAcceptor {
public:
    void acceptCoin(float coinValue, PaymentStrategy& paymentStrategy) const {
        paymentStrategy.addPayment(coinValue);
    }
};

// Card Reader
class CardReader {
public:
    void readCard(float amount, PaymentStrategy& paymentStrategy) const {
        paymentStrategy.addPayment(amount);
    }
};

// Item Database
class ItemDatabase {
    unordered_map<string, shared_ptr<Item>> items;

public:
    void addItem(const shared_ptr<Item>& item) {
        items[item->getCode()] = item;
    }

    shared_ptr<Item> getItem(const string& code) const {
        auto it = items.find(code);
        return it != items.end() ? it->second : nullptr;
    }
};

// Vending Machine
class VendingMachine {
    ItemDatabase itemDatabase;
    unique_ptr<PaymentStrategy> paymentStrategy;
    Dispenser dispenser;
    DisplayObserver& displayObserver;

public:
    explicit VendingMachine(DisplayObserver& observer)
        : displayObserver(observer) {}

    void addItem(const shared_ptr<Item>& item) {
        itemDatabase.addItem(item);
    }

    void selectItem(const string& itemCode) {
        auto item = itemDatabase.getItem(itemCode);
        if (!item) {
            displayObserver.update("Invalid item code");
            return;
        }
        if (item->getQuantity() == 0) {
            displayObserver.update("Item out of stock");
            return;
        }
        displayObserver.update("Price: " + to_string(item->getPrice()));
    }

    void insertCoin(float coinValue) {
        if (dynamic_cast<CoinPayment*>(paymentStrategy.get())) {
            paymentStrategy->addPayment(coinValue);
            displayObserver.update("Balance: " + to_string(paymentStrategy->getBalance()));
        } else {
            displayObserver.update("Invalid payment method.");
        }
    }

    void insertCard(float amount) {
        if (dynamic_cast<CardPayment*>(paymentStrategy.get())) {
            paymentStrategy->addPayment(amount);
            displayObserver.update("Balance: " + to_string(paymentStrategy->getBalance()));
        } else {
            displayObserver.update("Invalid payment method.");
        }
    }

    void cancelTransaction() {
        if (paymentStrategy) {
            paymentStrategy->resetBalance();
        }
        displayObserver.update("Transaction canceled");
    }

    void completeTransaction(const string& itemCode) {
        auto item = itemDatabase.getItem(itemCode);
        if (!item) {
            displayObserver.update("Invalid item code");
            return;
        }
        if (item->getQuantity() == 0) {
            displayObserver.update("Item out of stock");
            return;
        }
        if (!paymentStrategy || paymentStrategy->getBalance() < item->getPrice()) {
            displayObserver.update("Insufficient funds");
            return;
        }
        paymentStrategy->processPayment(item->getPrice());
        item->decrementQuantity();
        dispenser.dispenseItem(item);
        displayObserver.update("Transaction complete");
    }

    void setPaymentStrategy(unique_ptr<PaymentStrategy> strategy) {
        paymentStrategy = move(strategy);
    }
};

// Main Function
int main() {
    Display display;
    VendingMachine vendingMachine(display);

    // Add items to the vending machine
    vendingMachine.addItem(ItemFactory::createItem("snack", "S1", 1.5f, 10));
    vendingMachine.addItem(ItemFactory::createItem("drink", "D1", 2.5f, 5));

    // Select item
    vendingMachine.selectItem("S1");

    // Set payment strategy (coin)
    vendingMachine.setPaymentStrategy(make_unique<CoinPayment>());
    vendingMachine.insertCoin(1.0f);
    vendingMachine.insertCoin(0.5f);

    // Complete the transaction
    vendingMachine.completeTransaction("S1");

    // Cancel the transaction
    vendingMachine.cancelTransaction();

    return 0;
}
