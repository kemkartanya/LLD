#include <iostream>
using namespace std;

class Subsystem1 {
    public:
    string Operation1() const {
        return "Subsystem1: Ready!\n";
    }
    
    string OperationN() const {
        return "Subsystem1: Go!\n";
    }
};

class Subsystem2 {
    public:
    string Operation1() const {
        return "Subsystem2: Ready!\n";
    }
    
    string OperationZ() const {
        return "Subsystem2: Go!\n";
    }
};

class Facade {
    protected:
    Subsystem1 *subsystem1_;
    Subsystem2 *subsystem2_;
    
    public:
    Facade (Subsystem1 *subsystem1 = nullptr, Subsystem2 *subsystem2 = nullptr){
        this->subsystem1_ = subsystem1 ?: new Subsystem1;
        this->subsystem2_ = subsystem2 ?: new Subsystem2;
    }
    ~Facade() {
        delete subsystem1_;
        delete subsystem2_;
    }
    
    string Operation() {
        string result = "Facade initializes subsystems:\n";
        result += this->subsystem1_->Operation1();
        result += this->subsystem2_->Operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += this->subsystem1_->OperationN();
        result += this->subsystem2_->OperationZ();
        return result;
    }
};

void ClientCode(Facade *facade) {
  // ...
  std::cout << facade->Operation();
  // ...
}

int main() {
    Subsystem1 *subsystem1 = new Subsystem1;
    Subsystem2 *subsystem2 = new Subsystem2;
    Facade *facade = new Facade(subsystem1, subsystem2);
    ClientCode(facade);
    
    delete facade;
    return 0;
}
