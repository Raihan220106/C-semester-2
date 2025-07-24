#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base Class
class User {
protected:
    string username;
public:
    User(string uname) : username(uname) {}
    virtual void displayRole() = 0;
    string getUsername() { return username; }
};

// Inheritance: Customer & Admin
class Customer;
class Admin;

class Product {
private:
    string name, category;
    double price;
    int stock;
public:
    Product(string name, string category, double price, int stock)
        : name(name), category(category), price(price), stock(stock) {}

    string getName() const { return name; }
    double getPrice() const { return price; }
    int getStock() const { return stock; }
    void setStock(int s) { stock = s; }

    void display() {
        cout << "Product: " << name << ", Category: " << category
             << ", Price: $" << price << ", Stock: " << stock << endl;
    }
};

// Composition: ShoppingCart → Products
class ShoppingCart {
private:
    vector<Product*> products;
public:
    void addProduct(Product* product) {
        products.push_back(product);
        cout << product->getName() << " added to cart.\n";
    }

    vector<Product*> getProducts() const {
        return products;
    }
};

// Aggregation: OrderItem
class OrderItem {
private:
    Product* product;
    int quantity;
public:
    OrderItem(Product* p, int q) : product(p), quantity(q) {}
    double getTotal() const { return product->getPrice() * quantity; }
    void display() {
        cout << "- " << product->getName() << " x" << quantity
             << " = $" << getTotal() << endl;
    }
};

// Dependency: Payment
class Payment {
public:
    virtual void pay(double amount) = 0;
};

class CreditCardPayment : public Payment {
public:
    void pay(double amount) override {
        cout << "Paid $" << amount << " with Credit Card.\n";
    }
};

class BankTransferPayment : public Payment {
public:
    void pay(double amount) override {
        cout << "Paid $" << amount << " via Bank Transfer.\n";
    }
};

class EWalletPayment : public Payment {
public:
    void pay(double amount) override {
        cout << "Paid $" << amount << " using E-Wallet.\n";
    }
};

// Order class (aggregation of OrderItems)
class Order {
private:
    vector<OrderItem> items;
    string status;
public:
    void addItem(Product* p, int qty) {
        items.push_back(OrderItem(p, qty));
    }

    double getTotalAmount() const {
        double total = 0;
        for (const auto& item : items)
            total += item.getTotal();
        return total;
    }

    void processOrder(Payment* payment) {
        double total = getTotalAmount();
        payment->pay(total);
        status = "Paid";
    }

    void displayOrder() {
        cout << "Order Summary:\n";
        for (auto& item : items)
            item.display();
        cout << "Total: $" << getTotalAmount() << ", Status: " << status << endl;
    }

    void setStatus(string s) { status = s; }
};

// Customer class
class Customer : public User {
private:
    ShoppingCart cart;
public:
    Customer(string uname) : User(uname) {}

    void addToCart(Product* product) {
        cart.addProduct(product);
    }

    Order createOrder() {
        Order order;
        for (auto* product : cart.getProducts()) {
            order.addItem(product, 1); // default quantity = 1
        }
        return order;
    }

    void displayRole() override {
        cout << "Role: Customer\n";
    }
};

// Admin class
class Admin : public User {
public:
    Admin(string uname) : User(uname) {}

    void manageProduct(Product& p, int newStock) {
        p.setStock(newStock);
        cout << "Admin updated stock of " << p.getName() << " to " << newStock << endl;
    }

    void manageOrder(Order& order, string newStatus) {
        order.setStatus(newStatus);
        cout << "Order status updated to: " << newStatus << endl;
    }

    void displayRole() override {
        cout << "Role: Admin\n";
    }
};

// Main function
int main() {
    // Create Products
    Product p1("Laptop", "Electronics", 999.99, 10);
    Product p2("Sneakers", "Fashion", 79.99, 20);

    // Create Customer and Admin
    Customer cust("john_doe");
    Admin admin("admin_01");

    cust.displayRole();
    admin.displayRole();

    // Customer adds product to cart
    cust.addToCart(&p1);
    cust.addToCart(&p2);

    // Create Order from Cart
    Order order = cust.createOrder();
    order.displayOrder();

    // Payment
    EWalletPayment ewallet;
    order.processOrder(&ewallet);

    // Admin updates stock
    admin.manageProduct(p1, 8);
    admin.manageOrder(order, "Shipped");

    order.displayOrder();
    return 0;
}

