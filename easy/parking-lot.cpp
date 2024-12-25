#include <iostream>
#include <memory>
#include <map>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

// Enum for Vehicle Type
enum class VehicleType {
    CAR,
    TRUCK,
    ELECTRIC,
    VAN,
    MOTORBIKE
};

string getVehicleTypeDescription(VehicleType type) {
    switch (type) {
        case VehicleType::CAR: return "Car";
        case VehicleType::TRUCK: return "Truck";
        case VehicleType::ELECTRIC: return "Electric Car";
        case VehicleType::VAN: return "Van";
        case VehicleType::MOTORBIKE: return "Motorbike";
        default: return "Unknown";
    }
}

// Enum for Parking Spot Type
enum class ParkingSpotType {
    HANDICAPPED,
    COMPACT,
    LARGE,
    MOTORBIKE,
    ELECTRIC
};

string getParkingSpotTypeDescription(ParkingSpotType type) {
    switch (type) {
        case ParkingSpotType::HANDICAPPED: return "Handicapped";
        case ParkingSpotType::COMPACT: return "Compact";
        case ParkingSpotType::LARGE: return "Large";
        case ParkingSpotType::MOTORBIKE: return "Motorbike";
        case ParkingSpotType::ELECTRIC: return "Electric Charging";
        default: return "Unknown";
    }
}

// Class for Parking Spot
class ParkingSpot {
protected:
    string number;
    bool free = true;
    VehicleType vehicleType;
    ParkingSpotType type;

public:
    ParkingSpot(ParkingSpotType type, const string& number) : type(type), number(number) {}

    bool isFree() const {
        return free;
    }

    string getNumber() const {
        return number;
    }

    ParkingSpotType getType() const {
        return type;
    }

    bool assignVehicle(VehicleType vehicle) {
        if (!free) return false;
        vehicleType = vehicle;
        free = false;
        return true;
    }

    void removeVehicle() {
        free = true;
    }
};

// Specific Parking Spot Types
class HandicappedSpot : public ParkingSpot {
public:
    HandicappedSpot(const string& number) : ParkingSpot(ParkingSpotType::HANDICAPPED, number) {}
};

class CompactSpot : public ParkingSpot {
public:
    CompactSpot(const string& number) : ParkingSpot(ParkingSpotType::COMPACT, number) {}
};

class LargeSpot : public ParkingSpot {
public:
    LargeSpot(const string& number) : ParkingSpot(ParkingSpotType::LARGE, number) {}
};

// Class for Vehicle
class Vehicle {
protected:
    VehicleType type;

public:
    Vehicle(VehicleType type) : type(type) {}
    VehicleType getType() const { return type; }
};

class Car : public Vehicle {
public:
    Car() : Vehicle(VehicleType::CAR) {}
};

class Truck : public Vehicle {
public:
    Truck() : Vehicle(VehicleType::TRUCK) {}
};

// Singleton Parking Lot Class
class ParkingLot {
private:
    static unique_ptr<ParkingLot> instance;
    map<string, shared_ptr<ParkingSpot>> parkingSpots;

    ParkingLot() {}

public:
    static ParkingLot& getInstance() {
        if (!instance) {
            instance = make_unique<ParkingLot>();
        }
        return *instance;
    }

    void addParkingSpot(const shared_ptr<ParkingSpot>& spot) {
        parkingSpots[spot->getNumber()] = spot;
    }

    shared_ptr<ParkingSpot> findFreeSpot(ParkingSpotType type) {
        for (const auto& [key, spot] : parkingSpots) {
            if (spot->getType() == type && spot->isFree()) {
                return spot;
            }
        }
        return nullptr;
    }

    void parkVehicle(Vehicle& vehicle) {
        shared_ptr<ParkingSpot> spot;
        switch (vehicle.getType()) {
            case VehicleType::CAR:
                spot = findFreeSpot(ParkingSpotType::COMPACT);
                break;
            case VehicleType::TRUCK:
                spot = findFreeSpot(ParkingSpotType::LARGE);
                break;
            default:
                cout << "No suitable parking spot found for " << getVehicleTypeDescription(vehicle.getType()) << endl;
                return;
        }

        if (spot) {
            spot->assignVehicle(vehicle.getType());
            cout << "Vehicle parked at spot: " << spot->getNumber() << endl;
        } else {
            cout << "Parking full for " << getVehicleTypeDescription(vehicle.getType()) << endl;
        }
    }
};

unique_ptr<ParkingLot> ParkingLot::instance = nullptr;

// Main function
int main() {
    ParkingLot& parkingLot = ParkingLot::getInstance();

    parkingLot.addParkingSpot(make_shared<CompactSpot>("C1"));
    parkingLot.addParkingSpot(make_shared<LargeSpot>("L1"));

    Car car;
    Truck truck;

    parkingLot.parkVehicle(car);
    parkingLot.parkVehicle(truck);

    return 0;
}
