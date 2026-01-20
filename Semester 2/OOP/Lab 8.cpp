#include<iostream>
#include<string>
using namespace std;
/*class Employee
{
    private:
    string name;
    int salary;
    public:
    Employee()
    {
        name="";
        salary=0;
    }
    Employee(string n,int s)
    {
        name=n;
        salary=s;
    }
    void display()
    {
        cout<<"Employee:"<<name<<"Salary:"<<salary;
    }
    int getsalary()
    {
        return salary;
    }    
    string getname()
    {
        return name;
    }
    void setname(string s)
    {
        name=s;
    }
    void setsalary(int s)
    {
        salary=s;
    }
};
class Manager :public Employee
{
    public:
    void display()
    {
        cout<<"Manager:"<<getname()<<"Salary:"<<getsalary();
    }
};
int main()
{
    Manager M;
    M.setname("Alice");
    M.setsalary(3000);
    M.display();
}
//Task 2:
#include <iostream>
using namespace std;
class Person
{
    private:
    string name;
    int age;
    public:
    Person(string n, int a) : name(n), age(a) {}
    string getName() 
    { 
        return name; 
    }
    int getAge() 
    { 
        return age; 
    }
};
class Student : public Person 
{
    public:
    Student(string n, int a) : Person(n, a) {}
    void displayInfo() {
        cout << "Student Name: " << getName() << endl;
        cout << "Age: " << getAge() << endl;
    }
};
int main() 
{
    Student s("Umair", 21);
    s.displayInfo();
    return 0;
}
//Task 3:
#include <iostream>
using namespace std;
class Animal 
{
    public:
    virtual void sound() 
    {
        cout << "Some generic animal sound" << endl;
    }
    virtual ~Animal() 
    {}
};
class Dog : public Animal 
{
    public:
    void sound() override 
    {
        cout << "Dog: Woof!" << endl;
    }
};
class Cat : public Animal 
{
    public:
    void sound() override 
    {
        cout << "Cat: Meow!" << endl;
    }
};
int main() 
{
    Animal* animals[2];
    animals[0] = new Dog();
    animals[1] = new Cat();
    for (int i = 0; i < 2; ++i) 
    {
        animals[i]->sound();
        delete animals[i];
    }
    return 0;
}*/
//Task 4:
class Vehicle 
{
    public:
    Vehicle() 
    { 
        cout << "Vehicle Constructor" << endl; 
    }
    ~Vehicle() 
    { 
        cout << "Vehicle Destructor" << endl; 
    }
};
class Car : public Vehicle 
{
    public:
    Car() 
    { 
        cout << "Car Constructor" << endl; 
    }
    ~Car() 
    { 
        cout << "Car Destructor" << endl; 
    }
};
class Bicycle : public Vehicle 
{
    public:
    Bicycle() 
    { 
        cout << "Bicycle Constructor" << endl; 
    }
    ~Bicycle() 
    { 
        cout << "Bicycle Destructor" << endl; 
    }
};
int main() 
{
    cout << "Creating Car:" << endl;
    Car car;
    cout << "\nCreating Bicycle:" << endl;
    Bicycle bicycle;
    return 0;
}/*
//Task 5:
class Vehicle 
{
public:
    virtual void drive() 
    {
        cout << "Driving a generic vehicle." << endl;
    }
    virtual ~Vehicle() 
    {}
};
class Car : public Vehicle 
{
    public:
    void drive() override 
    {
        cout << "Driving a car!" << endl;
    }
};
class Bus : public Vehicle 
{
    public:
    void drive() override 
    {
        cout << "Driving a bus!" << endl;
    }
};
class Truck : public Vehicle 
{
    public:
    void drive() override 
    {
        cout << "Driving a truck!" << endl;
    }
};
int main() 
{
    Vehicle* vehicles[3];
    vehicles[0] = new Car();
    vehicles[1] = new Bus();
    vehicles[2] = new Truck();
    for (int i = 0; i < 3; ++i) 
    {
        vehicles[i]->drive();
        delete vehicles[i];
    }
    return 0;
}
*/