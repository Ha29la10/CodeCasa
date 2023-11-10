#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Customer {
    string name;
    int roomNumber;
    int duration;
    double bill;

    Customer(const string& n, int room, int dur, double b) : name(n), roomNumber(room), duration(dur), bill(b) {}
};

vector<Customer> customers;

void saveDataToFile() {
    ofstream outFile("customerData.txt");
    if (outFile.is_open()) {
        for (const auto& customer : customers) {
            outFile << customer.name << " " << customer.roomNumber << " " << customer.duration << " " << customer.bill << "\n";
        }
        outFile.close();
    }
}

void displayAllottedRooms() {
    cout << "Total Allotted Rooms: " << customers.size() <<endl;
}

void bookRoom() {
    string name;
    int roomNumber, duration;
    double bill;

    cout << "Enter customer name: ";
    cin >> name;
    cout << "Enter room number: ";
    cin >> roomNumber;
    cout << "Enter duration of stay (in days): ";
    cin >> duration;
    cout << "Enter total bill: ";
    cin >> bill;

    Customer newCustomer(name, roomNumber, duration, bill);
    customers.push_back(newCustomer);
    saveDataToFile();
    cout << "Room booked successfully!" <<endl;
}

void displayCustomerDetails() {
    int roomNumber;
    cout << "Enter room number to search for customer details: ";
    cin >> roomNumber;

    bool found = false;
    for (const auto& customer : customers) {
        if (customer.roomNumber == roomNumber) {
            cout << "Customer Name: " << customer.name << endl;
            cout << "Room Number: " << customer.roomNumber << endl;
            cout << "Duration of Stay: " << customer.duration << " days" <<endl;
            cout << "Total Bill: $" << customer.bill << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Customer with room number " << roomNumber << " not found." << endl;
    }
}

void deleteCustomerRecord() {
    int roomNumber;
    cout << "Enter room number to delete customer record: ";
    cin >> roomNumber;

    for (auto it = customers.begin(); it != customers.end(); ++it) {
        if (it->roomNumber == roomNumber) {
            customers.erase(it);
            saveDataToFile();
            cout << "Customer record deleted successfully." << endl;
            return;
        }
    }
    cout << "Customer with room number " << roomNumber << " not found." << endl;
}

int main() {
    ifstream inFile("customerData.txt");
    if (inFile.is_open()) {
        string name;
        int roomNumber, duration;
        double bill;

        while (inFile >> name >> roomNumber >> duration >> bill) {
            Customer loadedCustomer(name, roomNumber, duration, bill);
            customers.push_back(loadedCustomer);
        }
        inFile.close();
    }

    int choice;
    do {
        cout << "\nHotel Management System\n";
        cout << "1. Book Room\n2. Search Customer Details\n3. Delete Customer Record\n4. Total Allotted Rooms\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookRoom();
                break;
            case 2:
                displayCustomerDetails();
                break;
            case 3:
                deleteCustomerRecord();
                break;
            case 4:
                displayAllottedRooms();
                break;
            case 5:
                cout << "Exiting the system. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}
