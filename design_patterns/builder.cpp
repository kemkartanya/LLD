#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Product1 {
    public:
    vector<string> parts_;
    void ListParts() {
        cout<<"Product Parts: ";
        for(size_t i = 0; i < parts_.size(); i++) {
            if(parts_[i] == parts_.back()) {
                cout<<parts_[i];
            } else {
                cout<<parts_[i]<<", ";
            }
        }
        cout<<"\n\n";
    }
};

class Builder{
    public:
    virtual ~Builder(){}
    virtual void ProducePartA() const =0;
    virtual void ProducePartB() const =0;
    virtual void ProducePartC() const =0;
};

class ConcreteBuilder1 : public Builder{
    private:
    Product1* product;
    
    public:
    ConcreteBuilder1(){
        this->Reset();
    }
    ~ConcreteBuilder1(){
        delete product;
    }
    
    void Reset(){
        this->product= new Product1();
    }
    
    void ProducePartA() const override{
        this->product->parts_.push_back("PartA1");
    }

    void ProducePartB() const override{
        this->product->parts_.push_back("PartB1");
    }

    void ProducePartC() const override{
        this->product->parts_.push_back("PartC1");
    }
    
    Product1* GetProduct() {
        Product1* result= this->product;
        this->Reset();
        return result;
    }
};

class Director {
    private:
    Builder* builder;
    
    public:
    void set_builder(Builder* builder){
        this->builder=builder;
    }
    
    void BuildMinimalViableProduct(){
        this->builder->ProducePartA();
    }
    
    void BuildFullFeaturedProduct(){
        this->builder->ProducePartA();
        this->builder->ProducePartB();
        this->builder->ProducePartC();
    }
};

void ClientCode(Director& director) {
    ConcreteBuilder1* builder = new ConcreteBuilder1();
    director.set_builder(builder);
    cout << "Standard basic product:\n"; 
    director.BuildMinimalViableProduct();
    
    Product1* p= builder->GetProduct();
    p->ListParts();
    delete p;

    cout << "Standard full featured product:\n"; 
    director.BuildFullFeaturedProduct();

    p= builder->GetProduct();
    p->ListParts();
    delete p;

    // Remember, the Builder pattern can be used without a Director class.
    cout << "Custom product:\n";
    builder->ProducePartA();
    builder->ProducePartC();
    p=builder->GetProduct();
    p->ListParts();
    delete p;

    delete builder;
}

int main() {
    Director* director= new Director();
    ClientCode(*director);
    delete director;
    return 0;
}
