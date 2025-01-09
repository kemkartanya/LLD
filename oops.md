## Object oriented programming concepts: 

**Class** : blueprint / template, defines properties and behavior of objects

**Encapsulation**: hiding implementation details of an object & only exposing necessary Info through public methods. 

**Inheritance**: allow class to inherit properties & methods from other class ie. parent / super class. 

**Polymorphism**: ability of an object to take multiple forms

**Method overriding**: when subclass provides a specific implementation of a method that is already defined in the parent class. 

**Abstraction**: showing only the necessary info to the outside world while hiding unnecessary details. (abstract base class, abstract methods)

**A pure virtual function** (or abstract function) in C++ is a virtual function for which we can have an implementation, But we must override that function in the derived class, otherwise, the derived class will also become an abstract class. 
A pure virtual function is declared by assigning 0 in the declaration.
virtual function is a member function that is declared in the base class using the keyword virtual and is re-defined (Overridden) in the derived class. It tells the compiler to perform late binding where the compiler matches the object with the right called function and executes it during the runtime. This technique falls under Runtime Polymorphism.
