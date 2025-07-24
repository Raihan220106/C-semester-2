#include <iostream>
#include <string>
using namespace std;

// Encapsulation: Class User dengan atribut privat
class User {
private:
    int user_id;
    string name;
    double balance;
public:
    User(int id, string n, double b) : user_id(id), name(n), balance(b) {}

    void getUserInfo() {
        cout << "User: " << name << ", Balance: Rp" << balance << endl;
    }

    void topUp(double amount) {
        balance += amount;
        cout << "Saldo berhasil ditambah. Saldo saat ini: Rp" << balance << endl;
    }

    void pay(double amount) {
        if (balance >= amount) {
            balance -= amount;
            cout << "Pembayaran berhasil. Sisa saldo: Rp" << balance << endl;
        } else {
            cout << "Saldo tidak cukup!" << endl;
        }
    }
};

// Abstraction: Abstract class Transport
class Transport {
protected:
    int transport_id;
    string type;
    int capacity;
public:
    Transport(int id, string t, int c) : transport_id(id), type(t), capacity(c) {}
    virtual void getSchedule() const = 0; // Abstract method
    virtual ~Transport() {} // Virtual destructor
};

// Inheritance: Subclass dari Transport
class Bus : public Transport {
private:
    string route;
public:
    Bus(int id, string r, int c) : Transport(id, "Bus", c), route(r) {}
    void getSchedule() const override {
        cout << "Bus " << transport_id << " beroperasi di rute " << route << endl;
    }
};

class Train : public Transport {
private:
    string line;
public:
    Train(int id, string l, int c) : Transport(id, "Train", c), line(l) {}
    void getSchedule() const override {
        cout << "Kereta " << transport_id << " beroperasi di jalur " << line << endl;
    }
};

// Polymorphism: Implementasi metode yang berbeda untuk setiap transportasi
class BikeSharing : public Transport {
private:
    string station;
public:
    BikeSharing(int id, string s) : Transport(id, "Bike", 1), station(s) {}
    void getSchedule() const override {
        cout << "Sepeda tersedia di stasiun " << station << endl;
    }
};

// Class Payment untuk integrasi pembayaran
class Payment {
private:
    User &user;
public:
    Payment(User &u) : user(u) {}
    void processPayment(double amount) {
        user.pay(amount);
    }
};

int main() {
    User user1(101, "Budi", 50000);
    user1.getUserInfo();

    Bus bus1(201, "A-B", 50);
    Train train1(301, "Blue Line", 200);
    BikeSharing bike1(401, "Station 5");

    bus1.getSchedule();
    train1.getSchedule();
    bike1.getSchedule();

    Payment payment(user1);
    payment.processPayment(15000);

    return 0;
}
