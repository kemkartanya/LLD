## Practice Qs for LLD Interviews

Object oriented programming concepts: 

Class : blueprint / template, defines properties and behavior of objects

Encapsulation: hiding implementation details of an object & only exposing necessary Info through public methods. 

Inheritance: allow class to inherit properties & methods from other class ie. parent / super class. 

Polymorphism: ability of an object to take multiple forms
Method overriding: when subclass provides a specific implementation of a method that is already defined in the parent class. 

Abstraction: showing only the necessary info to the outside world while hiding unnecessary details. (abstract base class, abstract methods)
A pure virtual function (or abstract function) in C++ is a virtual function for which we can have an implementation, But we must override that function in the derived class, otherwise, the derived class will also become an abstract class. A pure virtual function is declared by assigning 0 in the declaration.
virtual function is a member function that is declared in the base class using the keyword virtual and is re-defined (Overridden) in the derived class. It tells the compiler to perform late binding where the compiler matches the object with the right called function and executes it during the runtime. This technique falls under Runtime Polymorphism.

SOLID principles : 
Single Responsibility: class should have single responsibility 
Open for extension, but closed for modification (add to existing function NOT change)
Liskov Substitution: If S is a subtype of T, then objects of type T in a program may be replaced with objects of S without altering any of the desirable properties of that program. (Inheritance)
Interface segregation: Clients should not be forced to depend on methods that they do not use. 
Dependency Inversion: High level modules should not depend on low-level modules. Both should depend on the abstraction. Abstraction should not depend on details. Details should depend on abstractions. 

High level module (or class) : class that executes an action with a tool 
Low level module (or class) : the tool that is needed to execute the action
Abstraction: represents an interface that connects the two classes. 
Details: how the tool works 








DRY principle: every piece of knowledge must have a single, unambiguous, authoritative representation with a system. 

YAGNI principle : You Aren’t Gonna Need It
Always implement things when you actually need them, never when you just foresee that you might need them. 

KISS principle : Keep It Simple, Stupid
It suggests that software should be designed to be easy to understand, modify, and extend, rather than complex and convoluted. 

Creational Patterns: 
Singleton, Factory Method, Abstract Factory, Builder, Prototype 

Structural Patterns: 
Adaptar, Bridge, Facade, Decorator, Composite, Flyweight, Proxy

Behavioral Patterns: 
Chain of responsibility, Strategy, Iterator, Observer, Template Method, Command, State, Mediator, Memento, State, Visitor

Singleton Pattern is a creational design pattern that guarantees a class has only one instance and provides a global point of access to it.




Factory Method is a creational design pattern that provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created. 

Abstract Factory is a creational design pattern that lets you produce families of related objects without specifying their concrete classes.

Builder is a creational design pattern that lets you construct complex objects step by step. The pattern allows you to produce different types and representations of an object using the same construction code.

Prototype is a creational design pattern that lets you copy existing objects without making your code dependent on their classes.

Adapter is a structural design pattern that allows objects with incompatible interfaces to collaborate.

Bridge is a structural design pattern that lets you split a large class or a set of closely related classes into two separate hierarchies—abstraction and implementation—which can be developed independently of each other.

Decorator is a structural design pattern that lets you attach new behaviors to objects by placing these objects inside special wrapper objects that contain the behaviors.

Facade is a structural design pattern that provides a simplified interface to a library, a framework, or any other complex set of classes.

Flyweight is a structural design pattern that lets you fit more objects into the available amount of RAM by sharing common parts of state between multiple objects instead of keeping all of the data in each object.

Proxy is a structural design pattern that lets you provide a substitute or placeholder for another object. A proxy controls access to the original object, allowing you to perform something either before or after the request gets through to the original object.

Chain of Responsibility is a behavioral design pattern that lets you pass requests along a chain of handlers. Upon receiving a request, each handler decides either to process the request or to pass it to the next handler in the chain.

Command is a behavioral design pattern that turns a request into a stand-alone object that contains all information about the request. This transformation lets you pass requests as a method argument, delay or queue the request's execution, and support undoable operations.

Iterator is a behavioral design pattern that lets you traverse elements of a collection without exposing its underlying representation (list, stack, tree, etc.).

Mediator is a behavioral design pattern that lets you reduce chaotic dependencies between objects. The pattern restricts direct communications between the objects and forces them to collaborate only via a mediator object.

Memento is a behavioral design pattern that lets you save and restore the previous state of an object without revealing the details of its implementation.

Observer is a behavioral design pattern that lets you define a subscription mechanism to notify multiple objects about any events that happen to the object they’re observing.

State is a behavioral design pattern that lets an object alter its behavior when its internal state changes. It appears as if the object changed its class.

Strategy is a behavioral design pattern that lets you define a family of algorithms, put each of them into a separate class, and make their objects interchangeable.

Template Method is a behavioral design pattern that defines the skeleton of an algorithm in the superclass but lets subclasses override specific steps of the algorithm without changing its structure.

Visitor is a behavioral design pattern that lets you separate algorithms from the objects on which they operate.

Design patterns: https://refactoring.guru/design-patterns/cpp
My code in C++: https://github.com/kemkartanya/LLD

SudoCode Best for theory:
Design Patterns - YouTube 
Low Level Design Primer Course - YouTube

Practice Ques: https://github.com/ashishps1/awesome-low-level-design (See Ques here & see video on it on youtube & then write code yourself to github)

Credits: GeeksForGeeks
