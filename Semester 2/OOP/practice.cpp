/*Mid B
#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    int id;
    string title;
    string author;
    string isbn;
    double price;

public:
    Book(int id, string title, string author, string isbn, double price)
        : id(id), title(title), author(author), isbn(isbn), price(price) {}
    
    Book(const Book &b) {
        id = b.id;
        title = b.title;
        author = b.author;
        isbn = b.isbn;
        price = b.price;
    }
    
    Book& operator=(const Book &b) {
        if (this != &b) {
            id = b.id;
            title = b.title;
            author = b.author;
            isbn = b.isbn;
            price = b.price;
        }
        return *this;
    }
    
    friend ostream& operator<<(ostream &out, const Book &b) {
        out << "Book ID: " << b.id << " | Title: " << b.title << " | Author: " << b.author << " | ISBN: " << b.isbn << " | Price: $" << b.price;
        return out;
    }
};

class Member {
private:
    static int counter;
    int id;
    string name;
    Book *borrowedBook;

public:
    Member(string name) : name(name) {
        id = ++counter;
        borrowedBook = nullptr;
    }
    
    void borrowBook(const Book &book) {
        if (borrowedBook) delete borrowedBook;
        borrowedBook = new Book(book);
    }
    
    void returnBook() {
        delete borrowedBook;
        borrowedBook = nullptr;
    }
    
    Book* operator->() {
        return borrowedBook;
    }
    
    friend ostream& operator<<(ostream &out, const Member &m) {
        out << "Member ID: " << m.id << " | Name: " << m.name;
        if (m.borrowedBook) out << " | Borrowed Book: " << *(m.borrowedBook);
        else out << " | No borrowed books.";
        return out;
    }
    
    ~Member() {
        delete borrowedBook;
    }
};

int Member::counter = 0;

int main() {
    Book book1(1, "C++ Programming", "Bjarne Stroustrup", "12345", 50.0);
    Book book2(2, "Design Patterns", "Erich Gamma", "67890", 45.0);
    
    Member member1("Alice");
    Member member2("Bob");
    
    member1.borrowBook(book1);
    member2.borrowBook(book2);
    
    cout << member1 << endl;
    cout << member2 << endl;
    
    member1.returnBook();
    cout << member1 << endl;
    
    return 0;
}*/
/*Mid A
#include <iostream>
#include <string>
using namespace std;

class Device {
private:
    string deviceName;
    int deviceID;
    bool status;
    static int deviceCount;

public:
    Device() : deviceName("Unknown"), deviceID(0), status(false) { deviceCount++; }
    Device(string name, int id, bool stat) : deviceName(name), deviceID(id), status(stat) { deviceCount++; }
    Device(const Device &d) : deviceName(d.deviceName), deviceID(d.deviceID), status(d.status) { deviceCount++; }
    ~Device() { deviceCount--; }

    void turnOn() { status = true; }
    void turnOff() { status = false; }
    void displayStatus() const { cout << "Device: " << deviceName << " | ID: " << deviceID << " | Status: " << (status ? "On" : "Off") << endl; }
    static int getDeviceCount() { return deviceCount; }
    string getDeviceType() const { return "Smart Device"; }

    Device operator+(const Device &d) { return (this->deviceID == d.deviceID) ? Device(deviceName, deviceID, status) : *this; }
    bool operator==(const Device &d) const { return this->deviceID == d.deviceID; }
};

int Device::deviceCount = 0;

class SmartHomeSystem {
private:
    Device* devices[100];
    int deviceCount;

public:
    SmartHomeSystem() : deviceCount(0) {}
    void addDevice(string name, int id, bool stat) { 
        if (deviceCount < 100) {
            devices[deviceCount++] = new Device(name, id, stat); 
        }
    }
    void removeDevice(int id) {
        for (int i = 0; i < deviceCount; i++) {
            if (devices[i]->operator==(Device("", id, false))) {
                delete devices[i];
                for (int j = i; j < deviceCount - 1; j++) {
                    devices[j] = devices[j + 1];
                }
                deviceCount--;
                break;
            }
        }
    }
    void displayDevices() const { 
        for (int i = 0; i < deviceCount; i++) {
            devices[i]->displayStatus(); 
        }
    }
    void displayTotalDevices() const { cout << "Total Devices: " << Device::getDeviceCount() << endl; }
    ~SmartHomeSystem() { 
        for (int i = 0; i < deviceCount; i++) delete devices[i]; 
    }
};

int main() {
    SmartHomeSystem home;
    home.addDevice("Living Room Light", 101, false);
    home.addDevice("Kitchen Thermostat", 102, true);
    home.displayDevices();
    home.displayTotalDevices();
    home.removeDevice(101);
    home.displayDevices();
    home.displayTotalDevices();
    return 0;
}
*/
/*Assessment B
#include <iostream>
using namespace std;

class Distance {
private:
    int kilometers;
    int meters;
    void normalize() {
        if (meters >= 1000) {
            kilometers += meters / 1000;
            meters %= 1000;
        } else if (meters < 0) {
            kilometers -= (-meters + 999) / 1000;
            meters = (meters % 1000 + 1000) % 1000;
        }
    }

public:
    Distance(int km = 0, int m = 0) : kilometers(km), meters(m) { normalize(); }
    Distance operator+(const Distance &d) const { return Distance(kilometers + d.kilometers, meters + d.meters); }
    Distance operator-(const Distance &d) const { return Distance(kilometers - d.kilometers, meters - d.meters); }
    Distance operator*(int factor) const { return Distance(kilometers * factor, meters * factor); }
    Distance operator/(int divisor) const { return Distance((kilometers * 1000 + meters) / divisor, (kilometers * 1000 + meters) % divisor); }
    bool operator==(const Distance &d) const { return kilometers == d.kilometers && meters == d.meters; }
    bool operator>(const Distance &d) const { return (kilometers * 1000 + meters) > (d.kilometers * 1000 + d.meters); }
    bool operator<(const Distance &d) const { return (kilometers * 1000 + meters) < (d.kilometers * 1000 + d.meters); }
    Distance& operator+=(const Distance &d) { kilometers += d.kilometers; meters += d.meters; normalize(); return *this; }
    Distance& operator-=(const Distance &d) { kilometers -= d.kilometers; meters -= d.meters; normalize(); return *this; }
    friend ostream& operator<<(ostream &out, const Distance &d) { return out << d.kilometers << " km " << d.meters << " m"; }
    friend istream& operator>>(istream &in, Distance &d) { in >> d.kilometers >> d.meters; d.normalize(); return in; }
};

int main() {
    Distance *d1 = new Distance(5, 1200);
    Distance *d2 = new Distance(3, 800);
    cout << *d1 << endl;
    cout << *d2 << endl;
    Distance d3 = *d1 + *d2;
    cout << d3 << endl;
    cout << (*d1 > *d2 ? "d1 is greater" : "d2 is greater") << endl;
    delete d1;
    delete d2;
    return 0;
}
*/