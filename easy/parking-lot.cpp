#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <ctime>

using namespace std;

enum class PaymentType {
    CASH,
    CREDIT_CARD,
    DEBIT_CARD,
    UPI
};

enum class ParkingSpaceType {
    BIKE_PARKING,
    CAR_PARKING,
    TRUCK_PARKING
};

enum class VehicleType {
    BIKE,
    CAR,
    TRUCK
};

enum class ParkingTicketStatus {
    PAID,
    ACTIVE
};

enum class PaymentStatus {
    UNPAID,
    PENDING,
    COMPLETED,
    DECLINED,
    CANCELLED,
    REFUNDED
};

class Address {
public:
    string country;
    string state;
    string city;
    string street;
    string pinCode;
};

class ParkingSpace {
public:
    int spaceId;
    bool isFree;
    double costPerHour;
    Vehicle* vehicle; // Pointer to Vehicle class
    ParkingSpaceType parkingSpaceType;
};

class ParkingDisplayBoard {
public:
    map<ParkingSpaceType, int> freeSpotsAvailableMap;

    void updateFreeSpotsAvailable(ParkingSpaceType parkingSpaceType, int spaces) {
        freeSpotsAvailableMap[parkingSpaceType] = spaces;
    }
};

class ParkingFloor {
public:
    int levelId;
    vector<ParkingSpace> parkingSpaces;
    ParkingDisplayBoard parkingDisplayBoard;
};

class Account {
public:
    string name;
    string email;
    string password;
    string empId;
    Address address;
};

class ParkingAttendant;

class Gate {
public:
    int gateId;
    ParkingAttendant* parkingAttendant; // Pointer to ParkingAttendant class
};

class Entrance : public Gate {
public:
    ParkingTicket* getParkingTicket(Vehicle* vehicle);
};

class Exit : public Gate {
public:
    ParkingTicket* payForParking(ParkingTicket* parkingTicket, PaymentType paymentType);
};

class Admin : public Account {
public:
    bool addParkingFloor(ParkingLot* parkingLot, ParkingFloor* floor);
    bool addParkingSpace(ParkingFloor* floor, ParkingSpace* parkingSpace);
    bool addParkingDisplayBoard(ParkingFloor* floor, ParkingDisplayBoard* parkingDisplayBoard);
    // Additional methods as required
};

class Payment;

class ParkingAttendant : public Account {
public:
    Payment* paymentService;

    bool processVehicleEntry(Vehicle* vehicle);
    PaymentInfo* processPayment(ParkingTicket* parkingTicket, PaymentType paymentType);
};

class Vehicle {
public:
    string licenseNumber;
    VehicleType vehicleType;
    ParkingTicket* parkingTicket;
    PaymentInfo* paymentInfo;
};

class ParkingTicket {
public:
    int ticketId;
    int levelId;
    int spaceId;
    time_t vehicleEntryDateTime;
    time_t vehicleExitDateTime;
    ParkingSpaceType parkingSpaceType;
    double totalCost;
    ParkingTicketStatus parkingTicketStatus;

    void updateTotalCost();
    void updateVehicleExitTime(time_t vehicleExitDateTime);
};

class Payment {
public:
    PaymentInfo* makePayment(ParkingTicket* parkingTicket, PaymentType paymentType);
};

class PaymentInfo {
public:
    double amount;
    time_t paymentDate;
    int transactionId;
    ParkingTicket* parkingTicket;
    PaymentStatus paymentStatus;
};

class ParkingLot {
public:
    vector<ParkingFloor> parkingFloors;
    vector<Entrance> entrances;
    vector<Exit> exits;

    Address address;
    string parkingLotName;

    bool isParkingSpaceAvailableForVehicle(Vehicle* vehicle);
    bool updateParkingAttendant(ParkingAttendant* parkingAttendant, int gateId);
};
