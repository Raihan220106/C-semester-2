#include <iostream>
using namespace std;

// Abstraksi tinta
class Ink {
public:
    virtual void use() = 0;
};

// Tinta Hitam
class BlackInk : public Ink {
public:
    void use() override {
        cout << "Menggunakan tinta hitam.\n";
    }
};

// Printer menerima tinta dari luar
class Printer {
private:
    Ink* ink; // Dependency
public:
    Printer(Ink* i) : ink(i) {} // Dependency disuntik dari luar

    void print() {
        cout << "Mulai mencetak... ";
        ink->use();
    }
};

int main() {
    BlackInk black;
    Printer printer(&black); // Inject dependency

    printer.print(); // Output: Mulai mencetak... Menggunakan tinta hitam.
    return 0;
}

