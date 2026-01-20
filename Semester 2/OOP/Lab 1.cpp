#include<iostream>
#include<string>
using namespace std;
/*Task 1:
class Person
{
    private:
    string name;
    int age;
    public:
    string getname()
    {
        return name;
    }
    int getage()
    {
        return age;
    }
    void setname(string personname)
    {
        name=personname;
    }
    void setage(int personage)
    {
        age=personage;
    }
    void getinfo()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
    }
};
int main()
{
    Person P1;
    string personname;
    int personage;
    cout<<"Enter Name:";
    getline(cin,personname);
    cout<<"Enter Age:";
    cin>>personage;
    P1.setname(personname);
    P1.setage(personage);
    P1.getinfo();
}*/
/*Task 2:
class Student
{
    private:
    string name;
    int age;
    public:
    string getname()
    {
        return name;
    }
    int getage()
    {
        return age;
    }
    void setname(string studentname)
    {
        name=studentname;
    }
    void setage(int studentage)
    {
        if(studentage>=1&&studentage<=100)
        {
        age=studentage;
        getinfo();
        }
        else
        cout<<"Invalid input! Enter age between 1 and 100.";
    }
    void getinfo()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"Age: "<<age<<endl;
    }
};
int main()
{
    Student S1;
    string studentname;
    int studentage;
    cout<<"Enter Name:";
    getline(cin,studentname);
    cout<<"Enter Age:";
    cin>>studentage;
    S1.setname(studentname);
    S1.setage(studentage);
}*/
/*Task 3:
class Circle
{
    private:
    int radius;
    int area;
    public:
    int getradius()
    {
        return radius;
    }
    int getarea()
    {
        return area;
    }
    void setradius(int circleradius)
    {
        radius=circleradius;
    }
    void setarea(int circlearea)
    {
        area=3.14*radius*radius;
    }
    void getinfo()
    {
        cout<<"Radius: "<<radius<<endl;
        cout<<"Area: "<<area<<endl;
    }
};
int main()
{
    Circle C1;
    int circleradius,circlearea;
    cout<<"Enter Radius:";
    cin>>circleradius;
    C1.setradius(circleradius);
    C1.setarea(circlearea);
    C1.getinfo();
}*/
/*Task 4:
class PasswordManger
{
    private:
    string password;
    public:
    void setpassword(string p)
    {
        bool flag=true;
        while(flag)
        {
        cout<<"Enter Password:";
        if(p.length()>=8)
        {
        password=p;
        cout<<"Password has been set successfully.";
        flag=false;
        }
        else
        cout<<"Invlaid Input! Enter password greater than 8 digits.";
        }
    }
}
int main()
{
    PasswordManager PM;
    string p;
    PM.setpassword(p);
}*/
/*Task 5:
class Product
{
    private:
    string name;
    int price;
    public:
    string getname()
    {
        return name;
    }
    int getprice()
    {
        return price;
    }
    void setname(string productname)
    {
        cout<<"Enter Name:";
        cin.ignore();
        getline(cin,productname);
        name=productname;
    }
    void setprice(int productprice)
    {
        bool flag=true;
        while (flag)
        {
        cout<<"Enter price:";
        cin>>productprice;
        if(productprice>=0)
        {
        price=productprice;
        flag=false;
        }
        else 
        cout<<"Invalid input! Enter positive price."; 
        }
    }
    void getinfo()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"Price: "<<price<<endl;
    }
};
int main()
{
    Product P1;
    string productname;
    int productprice,choice;
    bool flag=true;
    while(flag)
    {
    cout<<"-----MAIN MENU-----"<<endl;
    cout<<"1. Update Data.\n2. Retrieve Data.\n3. Exit.\nEnter your choice:";
    cin>>choice;
    switch (choice)
    {
    case 1:
        P1.setname(productname);
        P1.setprice(productprice);
        break;
    case 2:
        P1.getinfo();
        break;
    case 3:
        cout<<"Good Bye!";
        flag=false;
        break;
    }
    }
}*/
/*Task: 6
class Employee 
{
    private:
    string name;
    string designation;
    public:
    void setName(string empname) 
    {
        cout<<"Enter name:";
        cin>>empname;
        for (int i = 0; i < empname.length(); i++) 
        {
            if (empname[i] >= 'a' && empname[i] <= 'z') 
            {
                empname[i] = empname[i] - 32; 
            }
        }
        name = empname;
    }
    string getName() 
    {
        return name;
    }
    void setDesignation(string newDesignation) 
    {
        cout<<"Enter designation:";
        cin>>newDesignation;
        designation = newDesignation;
    }
    string getDesignation() 
    {
        return designation;
    }
};
int main() 
{
    Employee E1;
    string empname,empdesignation;
    E1.setName(empname);
    E1.setDesignation(empdesignation);
    cout << "Employee Name: " << E1.getName() << endl;
    cout << "Employee Designation: " << E1.getDesignation() << endl;
    return 0;
}*/
/*Task 7:
class Student
{
    private:
    string name;
    float gpa;
    public:
    string getname()
    {
        return name;
    }
    int getgpa()
    {
        return gpa;
    }
    void setname(string studentname)
    {
        name=studentname;
    }
    void setgpa(float studentgpa)
    {
        cout<<"Enter gpa:";
        cin>>studentgpa;
        if(studentgpa>=0.0&&studentgpa<=4.0)
        {
        gpa=studentgpa;
        getinfo();
        }
        else
        cout<<"Invalid input! Enter GPA between 0.0 and 4.0.";
    }
    void getinfo()
    {
        cout<<"Name: "<<name<<endl;
        cout<<"gpa: "<<gpa<<endl;
    }
};
int main()
{
    Student S1;
    string studentname;
    float studentgpa;
    cout<<"Enter Name:";
    getline(cin,studentname);
    S1.setname(studentname);
    S1.setgpa(studentgpa);
}*/
/*Task 8:
class BankAccount 
{
    private:
    int _accountNumber;
    double _balance;
    public:
    int getaccno()
    {
        return _accountNumber;
    }
    double getBalance() 
    {
        return _balance;
    }
    void setBalance(double amount) 
    {
        bool flag=true;
        while(flag)
        {
        cout<<"Enter Balance:";
        cin>>amount;
        if (amount >= 0) 
        {
            _balance = amount;
            flag=false;
        } 
        else 
        {
            cout << "Error: Balance cannot be negative!" << endl;
        }
        }
    }
    void setaccno(int accno)
    {
        cout<<"Enter account number:";
        cin>> accno;
        _accountNumber=accno;
    }
    void deposit(double amount) 
    {
        bool flag=true;
        while(flag)
        {
        cout<<"Enter amount to deposit:";
        cin>>amount;
        if (amount > 0) 
        {
            _balance += amount;
            cout << "Deposited: " << amount << ". New Balance: " << _balance << endl;
            flag=false;
        } 
        else 
        {
            cout << "Error: Deposit amount must be positive!" << endl;
        }
        }
    }
    void withdraw(double amount) 
    {
        bool flag=true;
        while(flag)
        {
        cout<<"Enter amount to withdraw:";
        cin>>amount;
        if (amount > 0 && _balance >= amount) 
        {
            _balance -= amount;
            cout << "Withdrawn: " << amount << ". New Balance: " << _balance << endl;
            flag=false;
        } 
        else 
        {
            cout << "Error: Insufficient funds or invalid amount!" << endl;
        }
        }
    }
};
int main() 
{
    BankAccount account;
    double amount;
    int accno,choice;
    bool flag=true;
    account.setaccno(accno);
    account.setBalance(amount);
    while(flag)
    {
        cout<<"----Menu----"<<endl;
        cout<<"1. Deposit\n2. Withdraw\n3. Check Account\n4. Exit.\nEnter your choice:";
        cin>>choice;
        switch(choice)
        {
            case 1:
            account.deposit(amount);
            break;
            case 2:
            account.withdraw(amount);
            break;
            case 3:
            cout<<"Account Number:"<<account.getaccno()<<endl;
            cout<<"Current Balance:"<<account.getBalance()<<endl;
            break;
            case 4:
            cout<<"Good Bye!";
            flag=false;
            break;
            default:
            cout<<"Invalid choice!"<<endl;
        }
    }
    return 0;
}*/
/*Task 9:
class Config 
{
    private:
    string key;
    int value;
    public:
    Config(string k) : key(k) {}
    string getKey() const 
    {
        return key;
    }
    void setValue(int v) 
    {
        value = v;
    }
};

int main() {
    Config config("API_KEY");
    int value;
    cout << "Key: " << config.getKey() << endl;
    cout<<"Enter Value:";
    cin>>value;
    config.setValue(value);
    return 0;
}*/
/*Task 10:
class Rectangle
{
    private:
    int length;
    int width;
    int area;
    public:
    int getlength()
    {
        return length;
    }
    int getwidth()
    {
        return width;
    }
    int getarea()
    {
        return area;
    }
    void setlength(int rectanglelength)
    {
        length=rectanglelength;
    }
    void setwidth(int rectanglewidth)
    {
        width=rectanglewidth;
    }
    void setarea(int rectanglearea)
    {
        area=length*width;
    }
    void getinfo()
    {
        cout<<"Length: "<<length<<endl;
        cout<<"Width: "<<width<<endl;
        cout<<"Area: "<<area<<endl;
    }
};
int main()
{
    Rectangle R1;
    int rectanglelength,rectanglewidth,rectanglearea;
    cout<<"Enter length:";
    cin>>rectanglelength;
    cout<<"Enter width:";
    cin>>rectanglewidth;
    R1.setlength(rectanglelength);
    R1.setwidth(rectanglewidth);
    R1.setarea(rectanglearea);
    R1.getinfo();
}*/