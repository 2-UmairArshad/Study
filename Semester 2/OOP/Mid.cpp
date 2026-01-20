#include <iostream>
#include <string>
using namespace std;
class product 
{
    private:
    string name;
    double price;
    int quantity;
    static int totalproducts;
    public:
    product(string n, double p, int q) : name(n), price(p), quantity(q) 
    { 
        totalproducts++; 
    }
    product(const product &p) : name(p.name), price(p.price), quantity(p.quantity) 
    { 
        totalproducts++; 
    }
    string getname() 
    { 
        return name; 
    }
    double getprice() 
    { 
        return price; 
    }
    int getquantity() 
    { 
        return quantity; 
    }
    void updatequantity(int q) 
    { 
        quantity = q; 
    }
    void updateprice(int q) 
    { 
        price = q; 
    }
    product operator+(const product &p) 
    { 
        quantity=quantity + p.quantity;
        return *this;
    }
    static int gettotalproducts() 
    { 
        return totalproducts; 
    }
    void display()
    {
        cout<<"Name:"<<name<<endl;
        cout<<"Price:"<<price<<endl;
        cout<<"Quantity:"<<quantity<<endl;
    }
    ~product() 
    { 
        totalproducts--; 
    }
};
int product::totalproducts = 0;
int main() 
{
    product *p1 = new product("item1", 10, 20);
    product p2("item2", 15, 30);
    product *p3 = new product(*p1 + p2);
    p2.updateprice(20);
    p2.updatequantity(56);
    cout<< "Display details of 2nd product" << endl;
    p2.display();
    cout << "Total Products: " << product::gettotalproducts() << endl;
    cout << "After Addition: " << p3->getquantity() << endl;
    delete p1;
    delete p3;
    cout << "Total Products after deletion: " << product::gettotalproducts() << endl;
    return 0;
}
