#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
 
using namespace std;

// Kelas induk Payment
class Payment {
protected:
    std::string id;
    double amount;
    std::string date;
    std::string status;

public:
    // Constructor
    Payment(std::string id, double amount) : id(id), amount(amount) {
        // Mendapatkan tanggal saat ini
        time_t now = time(0);
        tm* ltm = localtime(&now);

        // Format tanggal: DD/MM/YYYY
        date = std::to_string(ltm->tm_mday) + "/" +
               std::to_string(ltm->tm_mon + 1) + "/" +
               std::to_string(ltm->tm_year + 1900);

        status = "PENDING";
    }

    // Getter methods
    std::string getId() const { return id; }
    double getAmount() const { return amount; }
    std::string getDate() const { return date; }
    std::string getStatus() const { return status; }

    // Setter method untuk status
    void setStatus(const std::string& newStatus) { status = newStatus; }

    // Method virtual untuk polymorphism
    virtual bool validatePayment() = 0; // pure virtual method
    virtual bool processPayment() = 0; // pure virtual method
    virtual bool refundPayment() = 0; // pure virtual method

    // Method untuk menampilkan informasi pembayaran
    virtual void displayInfo() const {
        std::cout << "ID Pembayaran: " << id << std::endl;
        std::cout << "Jumlah: Rp " << std::fixed << std::setprecision(2) << amount << std::endl;
        std::cout << "Tanggal: " << date << std::endl;
        std::cout << "Status: " << status << std::endl;
    }

    // Destructor virtual
    virtual ~Payment() {}
};

// Kelas turunan CreditCardPayment
class CreditCardPayment : public Payment {
private:
    std::string cardNumber;
    std::string expiryDate;
    std::string cvv;

public:
    CreditCardPayment(std::string id, double amount, std::string cardNumber,
                     std::string expiryDate, std::string cvv)
        : Payment(id, amount), cardNumber(cardNumber), expiryDate(expiryDate), cvv(cvv) {}

    // Implementasi method validatePayment
    bool validatePayment() override {
        // Validasi kartu kredit
        // Contoh: cek apakah format kartu valid
        if (cardNumber.length() != 16) {
            std::cout << "Validasi gagal: Nomor kartu kredit harus 16 digit." << std::endl;
            return false;
        }

        // Cek format tanggal kadaluarsa (MM/YY)
        if (expiryDate.length() != 5 || expiryDate[2] != '/') {
            std::cout << "Validasi gagal: Format tanggal kadaluarsa harus MM/YY." << std::endl;
            return false;
        }

        // Cek CVV
        if (cvv.length() != 3) {
            std::cout << "Validasi gagal: CVV harus 3 digit." << std::endl;
            return false;
        }

        std::cout << "Validasi kartu kredit berhasil." << std::endl;
        return true;
    }

    // Implementasi method processPayment
    bool processPayment() override {
        if (validatePayment()) {
            // Proses pembayaran kartu kredit
            std::cout << "Memproses pembayaran kartu kredit untuk ID: " << getId() << std::endl;
            std::cout << "Menghubungi gateway pembayaran..." << std::endl;
            // Simulasi proses pembayaran
            setStatus("COMPLETED");
            std::cout << "Pembayaran kartu kredit berhasil." << std::endl;
            return true;
        }
        setStatus("FAILED");
        return false;
    }

    // Implementasi method refundPayment
    bool refundPayment() override {
        if (getStatus() == "COMPLETED") {
            std::cout << "Memproses pengembalian dana ke kartu kredit dengan nomor: "
                      << maskCardNumber() << std::endl;
            // Simulasi proses refund
            setStatus("REFUNDED");
            std::cout << "Pengembalian dana berhasil." << std::endl;
            return true;
        } else {
            std::cout << "Pengembalian dana gagal: Pembayaran harus berstatus COMPLETED" << std::endl;
            return false;
        }
    }

    // Method untuk masking nomor kartu kredit
    std::string maskCardNumber() const {
        if (cardNumber.length() < 4) return cardNumber;

        std::string masked = "";
        for (size_t i = 0; i < cardNumber.length() - 4; i++) {
            masked += "*";
        }
        return masked + cardNumber.substr(cardNumber.length() - 4);
    }

    // Override method displayInfo
    void displayInfo() const override {
        Payment::displayInfo();
        std::cout << "Metode: Kartu Kredit" << std::endl;
        std::cout << "Nomor Kartu: " << maskCardNumber() << std::endl;
        std::cout << "Tanggal Kadaluarsa: " << expiryDate << std::endl;
    }
};

// Kelas turunan BankTransfer
class BankTransfer : public Payment {
private:
    std::string accountNumber;
    std::string bankName;
    std::string transferCode;

public:
    BankTransfer(std::string id, double amount, std::string accountNumber,
                std::string bankName, std::string transferCode)
        : Payment(id, amount), accountNumber(accountNumber), bankName(bankName), transferCode(transferCode) {}

    // Implementasi method validatePayment
    bool validatePayment() override {
        // Validasi transfer bank
        // Cek apakah nomor rekening valid
        if (accountNumber.length() < 8) {
            std::cout << "Validasi gagal: Nomor rekening terlalu pendek." << std::endl;
            return false;
        }

        // Cek kode transfer
        if (transferCode.empty()) {
            std::cout << "Validasi gagal: Kode transfer tidak boleh kosong." << std::endl;
            return false;
        }

        std::cout << "Validasi transfer bank berhasil." << std::endl;
        return true;
    }

    // Implementasi method processPayment
    bool processPayment() override {
        if (validatePayment()) {
            // Proses transfer bank
            std::cout << "Memproses transfer bank untuk ID: " << getId() << std::endl;
            std::cout << "Menghubungi bank " << bankName << "..." << std::endl;
            // Simulasi proses pembayaran
            setStatus("COMPLETED");
            std::cout << "Transfer bank berhasil." << std::endl;
            return true;
        }
        setStatus("FAILED");
        return false;
    }

    // Implementasi method refundPayment
    bool refundPayment() override {
        if (getStatus() == "COMPLETED") {
            std::cout << "Memproses pengembalian dana ke rekening bank " << bankName
                      << " dengan nomor: " << accountNumber << std::endl;
            // Simulasi proses refund
            setStatus("REFUNDED");
            std::cout << "Pengembalian dana berhasil." << std::endl;
            return true;
        } else {
            std::cout << "Pengembalian dana gagal: Pembayaran harus berstatus COMPLETED" << std::endl;
            return false;
        }
    }

    // Override method displayInfo
    void displayInfo() const override {
        Payment::displayInfo();
        std::cout << "Metode: Transfer Bank" << std::endl;
        std::cout << "Nomor Rekening: " << accountNumber << std::endl;
        std::cout << "Nama Bank: " << bankName << std::endl;
        std::cout << "Kode Transfer: " << transferCode << std::endl;
    }
};

// Kelas turunan DigitalWallet
class DigitalWallet : public Payment {
private:
    std::string walletId;
    std::string provider;
    std::string phoneNumber;

public:
    DigitalWallet(std::string id, double amount, std::string walletId,
                 std::string provider, std::string phoneNumber)
        : Payment(id, amount), walletId(walletId), provider(provider), phoneNumber(phoneNumber) {}

    // Implementasi method validatePayment
    bool validatePayment() override {
        // Validasi dompet digital
        if (walletId.empty()) {
            std::cout << "Validasi gagal: ID dompet tidak boleh kosong." << std::endl;
            return false;
        }

        // Cek provider
        if (provider.empty()) {
            std::cout << "Validasi gagal: Provider tidak boleh kosong." << std::endl;
            return false;
        }

        // Cek nomor telepon
        if (phoneNumber.length() < 10) {
            std::cout << "Validasi gagal: Nomor telepon tidak valid." << std::endl;
            return false;
        }

        std::cout << "Validasi dompet digital berhasil." << std::endl;
        return true;
    }

    // Implementasi method processPayment
    bool processPayment() override {
        if (validatePayment()) {
            // Proses pembayaran dompet digital
            std::cout << "Memproses pembayaran dompet digital untuk ID: " << getId() << std::endl;
            std::cout << "Menghubungi provider " << provider << "..." << std::endl;
            // Simulasi proses pembayaran
            setStatus("COMPLETED");
            std::cout << "Pembayaran dompet digital berhasil." << std::endl;
            return true;
        }
        setStatus("FAILED");
        return false;
    }

    // Implementasi method refundPayment
    bool refundPayment() override {
        if (getStatus() == "COMPLETED") {
            std::cout << "Memproses pengembalian dana ke dompet digital " << provider
                      << " dengan ID: " << walletId << std::endl;
            // Simulasi proses refund
            setStatus("REFUNDED");
            std::cout << "Pengembalian dana berhasil." << std::endl;
            return true;
        } else {
            std::cout << "Pengembalian dana gagal: Pembayaran harus berstatus COMPLETED" << std::endl;
            return false;
        }
    }

    // Override method displayInfo
    void displayInfo() const override {
        Payment::displayInfo();
        std::cout << "Metode: Dompet Digital" << std::endl;
        std::cout << "Provider: " << provider << std::endl;
        std::cout << "ID Dompet: " << walletId << std::endl;
        std::cout << "Nomor Telepon: " << phoneNumber << std::endl;
    }
};

// Main function untuk testing
int main() {
    std::cout << "===== SISTEM PEMBAYARAN DIGITAL =====" << std::endl << std::endl;

    // Test CreditCardPayment
    std::cout << "----- PEMBAYARAN KARTU KREDIT -----" << std::endl;
    CreditCardPayment ccPayment("CC001", 1500000, "1234567890123456", "12/25", "123");
    ccPayment.displayInfo();
    ccPayment.processPayment();
    std::cout << "Status setelah proses: " << ccPayment.getStatus() << std::endl;
    ccPayment.refundPayment();
    std::cout << "Status setelah refund: " << ccPayment.getStatus() << std::endl;
    std::cout << std::endl;

    // Test BankTransfer
    std::cout << "----- PEMBAYARAN TRANSFER BANK -----" << std::endl;
    BankTransfer btPayment("BT001", 2000000, "9876543210", "Bank Mandiri", "TRF123456");
    btPayment.displayInfo();
    btPayment.processPayment();
    std::cout << "Status setelah proses: " << btPayment.getStatus() << std::endl;
    btPayment.refundPayment();
    std::cout << "Status setelah refund: " << btPayment.getStatus() << std::endl;
    std::cout << std::endl;

    // Test DigitalWallet
    std::cout << "----- PEMBAYARAN DOMPET DIGITAL -----" << std::endl;
    DigitalWallet dwPayment("DW001", 500000, "user123", "GoPay", "08123456789");
    dwPayment.displayInfo();
    dwPayment.processPayment();
    std::cout << "Status setelah proses: " << dwPayment.getStatus() << std::endl;
    dwPayment.refundPayment();
    std::cout << "Status setelah refund: " << dwPayment.getStatus() << std::endl;

    return 0;
}
