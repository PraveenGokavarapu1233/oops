#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Guest {
private:
    string name;
    string phoneNumber;

public:
    Guest(const string& name, const string& phoneNumber) : name(name), phoneNumber(phoneNumber) {}

    const string& getName() const {
        return name;
    }

    const string& getPhoneNumber() const {
        return phoneNumber;
    }

    void display() const {
        cout << "Name: " << name << endl;
        cout << "Phone Number: " << phoneNumber << endl;
    }
};

class Room {
private:
    int roomNumber;
    bool booked;
    Guest* guest;

public:
    Room(int roomNumber) : roomNumber(roomNumber), booked(false), guest(nullptr) {}

    int getRoomNumber() const {
        return roomNumber;
    }

    bool isBooked() const {
        return booked;
    }

    void bookRoom(Guest* guest) {
        this->guest = guest;
        booked = true;
    }

    void releaseRoom() {
        booked = false;
        guest = nullptr;
    }

    void display() const {
        cout << "Room Number: " << roomNumber << endl;
        if (booked) {
            cout << "Status: Booked" << endl;
            cout << "Guest Information:" << endl;
            guest->display();
        } else {
            cout << "Status: Available" << endl;
        }
    }
};

class Hotel {
private:
    string hotelName;
    vector<Room*> rooms;

public:
    Hotel(const string& hotelName, int numRooms) : hotelName(hotelName) {
        for (int i = 1; i <= numRooms; ++i) {
            rooms.push_back(new Room(i));
        }
    }

    ~Hotel() {
        for (auto room : rooms) {
            delete room;
        }
        rooms.clear();
    }

    const string& getName() const {
        return hotelName;
    }

    void displayRoomStatus() const {
        cout << "Rooms in " << hotelName << ":" << endl;
        for (auto room : rooms) {
            room->display();
            cout << "---------------------" << endl;
        }
    }

    Room* findAvailableRoom() {
        for (auto room : rooms) {
            if (!room->isBooked()) {
                return room;
            }
        }
        return nullptr;
    }

    void bookRoom(Room* room, Guest* guest) {
        if (!room->isBooked()) {
            room->bookRoom(guest);
            cout << "Room " << room->getRoomNumber() << " has been booked for ";
            cout << guest->getName() << endl;
        } else {
            cout << "Room " << room->getRoomNumber() << " is already booked." << endl;
        }
    }
};

int main() {
    Hotel hotel("Grand Hotel", 20); // Create a hotel with 20 rooms

    int choice;
    string name, phoneNumber;
    Guest* guest = nullptr;
    Room* room = nullptr;

    cout << "Welcome to " << hotel.getName() << "!" << endl;

    do {
        cout << "\nMenu:\n";
        cout << "1. Check Room Availability\n";
        cout << "2. Book a Room\n";
        cout << "3. Display Room Status\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // Clear input buffer
        cin.ignore();

        switch (choice) {
        case 1:
            room = hotel.findAvailableRoom();
            if (room) {
                cout << "Room " << room->getRoomNumber() << " is available." << endl;
            } else {
                cout << "All rooms are booked." << endl;
            }
            break;

        case 2:
            cout << "Enter guest name: ";
            cin >> name;
            cout << "Enter guest phone number: ";
            cin >> phoneNumber;
            guest = new Guest(name, phoneNumber);
            room = hotel.findAvailableRoom();
            if (room) {
                hotel.bookRoom(room, guest);
            } else {
                cout << "All rooms are booked." << endl;
            }
            break;

        case 3:
            hotel.displayRoomStatus();
            break;

        case 4:
            cout << "Exiting the program." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 4);

    // Clean up
    delete guest;
    return 0;
}
