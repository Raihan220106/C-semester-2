#include <iostream>
#include <vector>
using namespace std;

class User {
protected:
    string nama, email;
public:
    virtual void login() = 0; // Abstract Method
    void setNama(string n) { nama = n; }
    string getNama() { return nama; }
};

class Petani : public User {
private:
    vector<string> hasilPanen;
public:
    void login() override {
        cout << "Petani " << nama << " berhasil login.\n";
    }
    void tambahHasil(string produk) {
        hasilPanen.push_back(produk);
    }
};

class Produk {
private:
    string namaProduk;
    double harga;
public:
    Produk(string nama, double hrg) : namaProduk(nama), harga(hrg) {}
    double getHarga() const { return harga; }
    string getNama() const { return namaProduk; }
};

class Transaksi {
private:
    Produk* produk;
public:
    Transaksi(Produk* p) : produk(p) {}
    void proses() {
        cout << "Memproses transaksi produk: " << produk->getNama() << endl;
    }
};

int main() {
    Petani petani;
    petani.setNama("Budi");
    petani.login();

    Produk p1("Bawang Merah", 12000.0);
    Transaksi t(&p1);
    t.proses();

    return 0;
}

