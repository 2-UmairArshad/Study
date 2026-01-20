/*#include <iostream>
using namespace std;
class Employee 
{
    private:
    string name;
    double salary;

    public:
    void setEmployee(string n, double s) 
    {
        name = n;
        salary = s;
    }
    string getName() 
    {
        return name;
    }
    double getSalary() 
    {
        return salary;
    }
    void giveRaise(double percentage) 
    {
        salary += (salary * percentage / 100);
    }
    Employee compareSalary(Employee e) 
    {
        return (salary > e.salary)?*this:e;
    }
};
int main() 
{
    Employee e1, e2;
    e1.setEmployee("Alice", 50000);
    e2.setEmployee("Bob", 55000);
    Employee higherSalaryEmp = e1.compareSalary(e2);
    cout << "Higher Salary Employee: " << higherSalaryEmp.getName() << endl;
    return 0;
}*/
/*
#include <iostream>
using namespace std;

class Complex {
private:
    double real, imag;

public:
    void setValues(double r, double i) {
        real = r;
        imag = i;
    }

    Complex add(Complex c) {
        Complex result;
        result.real = real + c.real;
        result.imag = imag + c.imag;
        return result;
    }

    Complex subtract(Complex c) {
        Complex result;
        result.real = real - c.real;
        result.imag = imag - c.imag;
        return result;
    }

    Complex multiply(Complex c) {
        Complex result;
        result.real = (real * c.real) - (imag * c.imag);
        result.imag = (real * c.imag) + (imag * c.real);
        return result;
    }

    void display() {
        cout << real << " + " << imag << "i" << endl;
    }
};

int main() {
    Complex c1, c2, result;
    c1.setValues(3, 4);
    c2.setValues(1, 2);

    result = c1.add(c2);
    cout << "Addition: ";
    result.display();

    result = c1.subtract(c2);
    cout << "Subtraction: ";
    result.display();

    result = c1.multiply(c2);
    cout << "Multiplication: ";
    result.display();

    return 0;
}*/
/*#include <iostream>
using namespace std;

class Book {
private:
    string title, author;
    double price;

public:
    void setBook(string t, string a, double p) {
        title = t;
        author = a;
        price = p;
    }

    string getTitle() { return title; }
    string getAuthor() { return author; }
    double getPrice() { return price; }

    Book applyDiscount(double percent) {
        price -= price * (percent / 100);
        return *this;
    }

    Book comparePrice(Book b) {
        return (price <= b.price) ? *this : b;
    }
};

int main() {
    Book b1, b2;
    b1.setBook("Book A", "Author A", 500);
    b2.setBook("Book B", "Author B", 450);

    Book cheaper = b1.comparePrice(b2);
    cout << "Cheaper Book: " << cheaper.getTitle() << " by " << cheaper.getAuthor() << " at $" << cheaper.getPrice() << endl;

    return 0;
}
*/
/*#include <iostream>
using namespace std;

class Car {
private:
    string brand;
    int speed, fuel;

public:
    void setDetails(string b, int s, int f) {
        brand = b;
        speed = s;
        fuel = f;
    }

    Car& accelerate(int increment) {
        speed += increment;
        return *this;
    }

    Car& refuel(int amount) {
        fuel += amount;
        return *this;
    }

    void display() {
        cout << "Car: " << brand << " | Speed: " << speed << " km/h | Fuel: " << fuel << " L" << endl;
    }

    static int maxSpeed() {
        return 300; // Example max speed
    }
};

int main() {
    Car car;
    car.setDetails("Toyota", 60, 50);
    car.accelerate(20).refuel(10);
    car.display();
    
    cout << "Max Speed: " << Car::maxSpeed() << " km/h" << endl;

    return 0;
}*/
/*#include <iostream>
using namespace std;

class Product {
private:
    string name;
    double price;
    int stock;

public:
    void setProduct(string n, double p, int s) {
        name = n;
        price = p;
        stock = s;
    }

    double getPrice() { return price; }
    int getStock() { return stock; }

    Product buy(int quantity) {
        if (quantity <= stock) {
            stock -= quantity;
        } else {
            cout << "Not enough stock available!" << endl;
        }
        return *this;
    }

    void applyDiscount(double percent) {
        price -= price * (percent / 100);
    }

    static double taxRate() {
        return 5.0; // Example tax rate
    }
};

int main() {
    Product p;
    p.setProduct("Laptop", 1000, 10);
    p.buy(3);
    
    cout << "Remaining Stock: " << p.getStock() << endl;
    cout << "Tax Rate: " << Product::taxRate() << "%" << endl;

    return 0;
}
*/