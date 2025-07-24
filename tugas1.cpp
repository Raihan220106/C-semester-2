#include <iostream>
#include <string>
#include <memory>
#include <vector>

// Interface untuk metode pengiriman notifikasi
class INotificationSender {
public:
    virtual void send(const std::string& message) = 0;
    virtual ~INotificationSender() = default;
};

// Abstract class untuk notifikasi
class Notification {
protected:
    std::string message;
    std::unique_ptr<INotificationSender> sender;

public:
    Notification(const std::string& msg, std::unique_ptr<INotificationSender> notifSender)
        : message(msg), sender(std::move(notifSender)) {}

    virtual void send() {
        sender->send(message);
    }

    virtual std::string getType() const = 0;
    virtual ~Notification() = default;
};

// Implementasi konkret untuk Email Notification
class EmailNotificationSender : public INotificationSender {
public:
    void send(const std::string& message) override {
        std::cout << "Mengirim Email: " << message << std::endl;
    }
};

// Implementasi konkret untuk SMS Notification
class SMSNotificationSender : public INotificationSender {
public:
    void send(const std::string& message) override {
        std::cout << "Mengirim SMS: " << message << std::endl;
    }
};

// Implementasi konkret untuk Push Notification
class PushNotificationSender : public INotificationSender {
public:
    void send(const std::string& message) override {
        std::cout << "Mengirim Push Notification: " << message << std::endl;
    }
};

// Turunan konkret dari Notification untuk Email
class EmailNotification : public Notification {
public:
    EmailNotification(const std::string& msg)
        : Notification(msg, std::make_unique<EmailNotificationSender>()) {}

    std::string getType() const override {
        return "Email";
    }
};

// Turunan konkret dari Notification untuk SMS
class SMSNotification : public Notification {
public:
    SMSNotification(const std::string& msg)
        : Notification(msg, std::make_unique<SMSNotificationSender>()) {}

    std::string getType() const override {
        return "SMS";
    }
};

// Turunan konkret dari Notification untuk Push Notification
class PushNotification : public Notification {
public:
    PushNotification(const std::string& msg)
        : Notification(msg, std::make_unique<PushNotificationSender>()) {}

    std::string getType() const override {
        return "Push";
    }
};

// Kelas untuk mengelola notifikasi
class NotificationManager {
private:
    std::vector<std::unique_ptr<Notification>> notifications;

public:
    void addNotification(std::unique_ptr<Notification> notification) {
        notifications.push_back(std::move(notification));
    }

    void sendAllNotifications() {
        for (auto& notification : notifications) {
            std::cout << "Mengirim Notifikasi " << notification->getType() << ": ";
            notification->send();
        }
    }
};

int main() {
    NotificationManager manager;

    // Membuat dan menambahkan berbagai jenis notifikasi
    manager.addNotification(std::make_unique<EmailNotification>("Selamat datang di sistem kami!"));
    manager.addNotification(std::make_unique<SMSNotification>("Transaksi berhasil diproses."));
    manager.addNotification(std::make_unique<PushNotification>("Ada pembaruan baru tersedia."));

    // Mengirim semua notifikasi
    manager.sendAllNotifications();

    return 0;
}
