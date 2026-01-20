#include<iostream>
#include<string>
using namespace std;
/*Task 1:
class point
{
    private:
    int x;
    int y;
    public:
    point()
    {
        x=0;
        y=0;
    }
    void getinfo()
    {
        cout<<"x="<<x<<endl;
        cout<<"y="<<y<<endl;
    }
};
int main()
{
    point obj1;
    cout<<"Default Constructor:\n";
    obj1.getinfo();
}*/
/*Task 2:
class point
{
    private:
    int x;
    int y;
    public:
    point(int a, int b)
    {
        x=a;
        y=b;
    }
    void getinfo()
    {
        cout<<"x="<<x<<endl;
        cout<<"y="<<y<<endl;
    }
};
int main()
{
    point obj2(100,100);
    cout<<"Parametrized Constructor:\n";
    obj2.getinfo();
}*/
/*Task 3:
class point
{
    private:
    int x;
    int y;
    public:
     point(int a, int b)
    {
        x=a;
        y=b;
    }
    point(const point&obj)
    {
        x=obj.x;
        y=obj.y;
    }
    void getinfo()
    {
        cout<<"x="<<x<<endl;
        cout<<"y="<<y<<endl;
    }
};
int main()
{
    point obj2(100,100);
    cout<<"Parametrized Constructor:\n";
    obj2.getinfo();
    point obj3=obj2;
    cout<<"Copy Constructor:\n";
    obj3.getinfo();
}*/
/*Task 4:
class point
{
    private:
    int x;
    int y;
    public:
    point(int a, int b)
    {
        x=a;
        y=b;
    }
    point(const point&obj)
    {
        x=obj.x;
        y=obj.y;
    }
    ~point()
    {
        cout<<"Object Destroyed.";
    }
    void getinfo()
    {
        cout<<"x="<<x<<endl;
        cout<<"y="<<y<<endl;
    }
};
int main()
{
    point obj2(100,100);
    cout<<"Parametrized Constructor:\n";
    obj2.getinfo();
    point obj3=obj2;
    cout<<"Copy Constructor:\n";
    obj3.getinfo();
}*/
/*Task 5
class rectangle
{
    private:
    int length;
    int width;
    int area;
    int perimeter;
    public:
    rectangle()
    {
        length=0;
        width=0;
        area=0;
        perimeter=0;
    }
    rectangle(int a, int b)
    {
        length=a;
        width=b;
        area=length*width;
        perimeter=2*(length*width);
    }
    rectangle(const rectangle&obj)
    {
        length=obj.length;
        width=obj.width;
        area=length*width;
        perimeter=2*(length*width);
    }
    void getinfo()
    {
        cout<<"length="<<length<<endl;
        cout<<"width="<<width<<endl;
        cout<<"Area="<<area<<endl;
        cout<<"Perimeter="<<perimeter<<endl;
    }
};
int main()
{
    rectangle obj1;
    cout<<"Default Constructor:\n";
    obj1.getinfo();
    rectangle obj2(100,100);
    cout<<"Parametrized Constructor:\n";
    obj2.getinfo();
    rectangle obj3=obj2;
    cout<<"Copy Constructor:\n";
    obj3.getinfo();
}*/
/*
// Task 6: Circle Class
class Circle 
{
    private:
    double radius;
    string color;
    public:
    Circle() 
    {
        radius = 1.0;
        color = "Red";
    }
    Circle(double r, string c) 
    {
        radius = r;
        color = c;
    }
    void display() 
    {
        cout << "Circle\n Radius: " << radius << "\n Color: " << color << endl;
    }
};

int main() 
{
    Circle circles[2] = { Circle(), Circle(5.5, "Blue") };
    for (int i = 0; i < 2; i++) {
        circles[i].display();
    }
}*/
/*
// Task 7: Person Class
class Person 
{
    private:
    string name;
    int age;
    string gender;
    public:
    Person(string n, int a) {
        name = n;
        age = a;
        gender = "Not Specified";
    }
    Person(string n, int a, string g) {
        name = n;
        age = a;
        gender = g;
    }
    Person(const Person &p) {
        name = p.name;
        age = p.age;
        gender = p.gender;
    }
    Person() {
        name = "Unknown";
        age = 0;
        gender = "Not Specified";
    }
    void display() {
        cout << "Person - Name: " << name << ", Age: " << age << ", Gender: " << gender << endl;
    }
};

int main()
{
    Person St1("Ali", 2);
    Person St2("Kiran", 34, "Female");
    Person St3 = St1;
    Person St4;

    St1.display();
    St2.display();
    St3.display();
    St4.display();
}*/
/*
// Task 8: AccountDetail Class
class AccountDetail {
    private:
    string name;
    int age;
    double balance;
    public:
    AccountDetail(string n, int a, double b) 
    {
        name = n;
        age = a;
        balance = b;
    }
    AccountDetail(const AccountDetail &acc) 
    {
        name = acc.name;
        age = acc.age;
        balance = acc.balance;
    }
    void display() 
    {
        cout << "AccountDetail \n Name: " << name << "\n Age: " << age << "\n Balance: $" << balance << endl;
    }
};

int main()
{
    AccountDetail acc1("Umair", 13, 5000.75);
    AccountDetail acc2 = acc1;

    acc1.display();
    acc2.display();
}*/
