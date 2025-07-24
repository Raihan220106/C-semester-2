#include <iostream>
using namespace std;

// Abstraksi strategi
class Strategy {
public:
    virtual int calculate(int a, int b) = 0;
};

// Strategi penjumlahan
class Add : public Strategy {
public:
    int calculate(int a, int b) override {
        return a + b;
    }
};

// Strategi pengurangan
class Subtract : public Strategy {
public:
    int calculate(int a, int b) override {
        return a - b;
    }
};

// Kalkulator menggunakan strategi
class Calculator {
private:
    Strategy* strategy;
public:
    Calculator(Strategy* s) : strategy(s) {}

    int execute(int a, int b) {
        return strategy->calculate(a, b);
    }
};

int main() {
    Add add;
    Subtract subtract;

    Calculator calc1(&add);
    cout << "Hasil penjumlahan: " << calc1.execute(5, 3) << endl; // 8

    Calculator calc2(&subtract);
    cout << "Hasil pengurangan: " << calc2.execute(5, 3) << endl; // 2

    return 0;
}

