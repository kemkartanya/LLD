#include <iostream>
#include <thread>
#include <mutex>
#include <chrono> // For std::chrono::milliseconds

using namespace std;

class Singleton {
private:
    static Singleton* pinstance_; // Singleton instance
    static mutex mutex_;          // Mutex for thread safety

    string value_;

    // Private constructor to prevent external instantiation
    Singleton(const string value) : value_(value) {}
    ~Singleton() {}

public:
    // Delete copy constructor and assignment operator
    Singleton(Singleton& other) = delete;
    void operator=(const Singleton&) = delete;

    // Thread-safe singleton instance creation
    static Singleton* GetInstance(const string& value) {
        static once_flag flag; // Ensures initialization happens only once
        call_once(flag, [&]() {
            pinstance_ = new Singleton(value);
        });
        return pinstance_;
    }

    // Example business logic
    void SomeBusinessLogic() {
        cout << "Doing some business logic.\n";
    }

    // Accessor for singleton value
    string value() const {
        return value_;
    }
};

// Static member definitions
Singleton* Singleton::pinstance_{ nullptr };
mutex Singleton::mutex_;

// Thread functions to demonstrate singleton
void ThreadFoo() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("FOO");
    cout << singleton->value() << "\n";
}

void ThreadBar() {
    this_thread::sleep_for(chrono::milliseconds(1000));
    Singleton* singleton = Singleton::GetInstance("BAR");
    cout << singleton->value() << "\n";
}

int main() {
    cout << "If you see the same value, then singleton was reused (yay!)\n"
         << "If you see different values, then 2 singletons were created (booo!!)\n\n"
         << "RESULT:\n";

    thread t1(ThreadFoo);
    thread t2(ThreadBar);

    t1.join();
    t2.join();

    return 0;
}
