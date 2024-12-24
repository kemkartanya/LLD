#include <iostream>
#include <algorithm>
using namespace std;

class Target {
 public:
  virtual ~Target() = default;
  virtual string Request() const {
    return "Target: The default target's behavior.";
  }
};

class Adaptee {
 public:
  string SpecificRequest() const {
    return ".eetpadA eht fo roivaheb laicepS";
  }
};

class Adapter : public Target, public Adaptee {
 public:
  Adapter() {}
  string Request() const override {
    string to_reverse = SpecificRequest();
    reverse(to_reverse.begin(), to_reverse.end());
    return "Adapter: (TRANSLATED) " + to_reverse;
  }
};

void ClientCode(const Target *target) {
  cout << target->Request();
}

int main() {
    cout << "Client: I can work just fine with the Target objects:\n";
    Target *target = new Target;
    ClientCode(target);
    cout << "\n\n";
    
    Adaptee *adaptee = new Adaptee;
    cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    cout << "Adaptee: " << adaptee->SpecificRequest();
    cout << "\n\n";
    
    cout << "Client: But I can work with it via the Adapter:\n";
    Adapter *adapter = new Adapter;
    ClientCode(adapter);
    cout << "\n";

    delete target;
    delete adaptee;
    delete adapter;
    return 0;
}
