#include <iostream>
using namespace std;

class Product {
    public: 
    virtual ~Product() {}
    virtual string Operation() const = 0;
};

class ConcreteProduct1 : public Product {
    public:
    string Operation() const override {
        return "{Result of the ConcreteProduct1}";
    }
};

class ConcreteProduct2 : public Product {
    public:
    string Operation() const override {
        return "{Result of the ConcreteProduct2}";
    }
};

class Creator {
    public:
    virtual ~Creator() {}
    virtual Product* FactoryMethod() const = 0;
    
    string someOperation() const {
        Product* product = this->FactoryMethod();
        
        string result = "Creator: The same creator's code has just worked with " + product->Operation();
        delete product;
        return result;
    }
};

class ConcreteCreator1 : public Creator {
    public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct1();
    }
};

class ConcreteCreator2 : public Creator {
    public:
    Product* FactoryMethod() const override {
        return new ConcreteProduct2();
    }
};

void ClientCode(const Creator& creator) {
    cout<<"Client: I am not aware of the creator's class, but it still works.\n"<<creator.someOperation()<<endl;
}

int main() {
    cout << "App: Launched with the ConcreteCreator1.\n";
    Creator* creator = new ConcreteCreator1();
    ClientCode(*creator);
    cout<<endl;
    cout << "App: Launched with the ConcreteCreator2.\n";
    Creator* creator2 = new ConcreteCreator2();
    ClientCode(*creator2);
    
    delete creator;
    delete creator2;
    return 0;
}
