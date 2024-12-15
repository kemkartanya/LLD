#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

// Forward declaration
class User;
class Car;
class Reservation;
class Location;

// Enum for car type
enum class CarType { SEDAN, HATCHBACK, SUV };

// Enum for car status
enum class CarStatus { BOOKED, AVAILABLE, RUNNING, NO_OPS };

// Class to represent a geographical location
class Location {
public:
    string name;
    long zipcode;
    double latitude;
    double longitude;

    Location(string n, long z, double lat, double lon)
        : name(n), zipcode(z), latitude(lat), longitude(lon) {}
};

// Car class encapsulating car details
class Car {
private:
    string carName;
    string brand;
    int bookingPrice; // Per day rental price
    float kmDriven;
    int manufactureYear;
    long chassisNumber;

    CarType type;
    CarStatus status;
    Location location;

public:
    Car(string name, string br, int price, float km, int year, long chassis,
        CarType t, Location loc)
        : carName(name), brand(br), bookingPrice(price), kmDriven(km),
          manufactureYear(year), chassisNumber(chassis), type(t), location(loc),
          status(CarStatus::AVAILABLE) {}

    // Getters
    CarType getType() const { return type; }
    CarStatus getStatus() const { return status; }
    Location getLocation() const { return location; }
    string getName() const { return carName; }
    int getPrice() const { return bookingPrice; }

    // Mark car as reserved
    void reserve() { status = CarStatus::BOOKED; }

    // Update car details
    void updateDetails(int price, float km, CarStatus newStatus) {
        bookingPrice = price;
        kmDriven = km;
        status = newStatus;
    }
};

// User class representing a customer
class User {
private:
    string name;
    string email;
    string licenseNumber;
    string pan;
    Location userLocation;

public:
    User(string n, string e, string license, string p, Location loc)
        : name(n), email(e), licenseNumber(license), pan(p), userLocation(loc) {}

    string getName() const { return name; }
    string getLicenseNumber() const { return licenseNumber; }
};

// Reservation class to handle bookings
class Reservation {
private:
    User user;
    Car car;
    Location pickupLocation;
    Location dropLocation;
    int rentalPrice;

public:
    Reservation(User u, Car c, Location pickup, Location drop, int price)
        : user(u), car(c), pickupLocation(pickup), dropLocation(drop),
          rentalPrice(price) {}

    void displayReservationDetails() const {
        cout << "Reservation Details:\n";
        cout << "User: " << user.getName() << "\n";
        cout << "Car: " << car.getName() << "\n";
        cout << "Pickup Location: " << pickupLocation.name << "\n";
        cout << "Drop Location: " << dropLocation.name << "\n";
        cout << "Rental Price: " << rentalPrice << " USD\n";
    }
};

// Service to handle car reservations
class CarReservationService {
private:
    vector<Car> cars;             // List of available cars
    vector<Reservation> bookings; // Active reservations

public:
    // Add a new car
    void addCar(const Car &car) { cars.push_back(car); }

    // Find cars by type
    void getCarsByType(CarType type) {
        for (const auto &car : cars) {
            if (car.getType() == type) {
                cout << "Car: " << car.getName() << ", Price: " << car.getPrice() << "\n";
            }
        }
    }

    // Reserve a car
    void reserveCar(User &user, Car &car, Location pickup, Location drop) {
        if (car.getStatus() == CarStatus::AVAILABLE) {
            car.reserve();
            int price = car.getPrice();
            bookings.emplace_back(user, car, pickup, drop, price);
            cout << "Car reserved successfully!\n";
        } else {
            cout << "Car is not available.\n";
        }
    }

    // Display all reservations
    void displayAllReservations() const {
        for (const auto &res : bookings) {
            res.displayReservationDetails();
        }
    }
};

// Notification service to handle alerts
class NotificationService {
public:
    static void sendConfirmation(const User &user) {
        cout << "Notification sent to " << user.getName() << " for booking confirmation.\n";
    }
};

// Payment service to handle payments
class PaymentService {
public:
    static void processPayment(const User &user, int amount) {
        cout << "Payment of " << amount << " USD received from " << user.getName() << ".\n";
    }
};

// Main function
int main() {
    // Create locations
    Location loc1("New Delhi", 110001, 28.6139, 77.2090);
    Location loc2("Bangalore", 560001, 12.9716, 77.5946);

    // Create cars
    Car car1("City", "Honda", 50, 15000, 2020, 123456, CarType::SEDAN, loc1);
    Car car2("Swift", "Maruti", 40, 20000, 2021, 654321, CarType::HATCHBACK, loc2);

    // Create users
    User user1("John Doe", "john@example.com", "DL12345", "ABCDE1234F", loc1);

    // Reservation service
    CarReservationService carService;
    carService.addCar(car1);
    carService.addCar(car2);

    // Find cars by type
    cout << "Available Sedans:\n";
    carService.getCarsByType(CarType::SEDAN);

    // Reserve a car
    carService.reserveCar(user1, car1, loc1, loc2);

    // Process payment
    PaymentService::processPayment(user1, car1.getPrice());

    // Send notification
    NotificationService::sendConfirmation(user1);

    // Display reservations
    cout << "\nAll Reservations:\n";
    carService.displayAllReservations();

    return 0;
}
