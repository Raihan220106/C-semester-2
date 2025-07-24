#include <iostream>
using namespace std;

// Abstraksi mobil
class Car {
public:
    virtual void drive() = 0;
};

class SportsCar : public Car {
public:
    void drive() override {
        cout << "Mengemudi mobil sport!\n";
    }
};

class FamilyCar : public Car {
public:
    void drive() override {
        cout << "Mengemudi mobil keluarga.\n";
    }
};

// Factory
class CarFactory {
public:
    static Car* createCar(string type) {
        if (type == "sport") return new SportsCar();
        else return new FamilyCar();
    }
};

int main() {
    Car* myCar = CarFactory::createCar("sport");
    myCar->drive(); // Output: Mengemudi mobil sport!

    delete myCar;
    return 0;
}

