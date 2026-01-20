#include <iostream>
#include <string>
using namespace std;
/*
class Overlaod 
{
private:
    float n;
public:
    Overlaod(float val = 0) : n(val) {}
    Overlaod operator+(const Overlaod& c) 
    { 
        return Overlaod(n + c.n); 
    }
    Overlaod operator-(const Overlaod& c) 
    { 
        return Overlaod(n - c.n); 
    }
    Overlaod operator*(const Overlaod& c) 
    { 
        return Overlaod(n * c.n); 
    }
    Overlaod operator/(const Overlaod& c) 
    { 
        return Overlaod(n / c.n); 
    }
    Overlaod operator+=(const Overlaod& c) 
    { 
        n += c.n; 
        return *this; 
    }
    Overlaod operator-=(const Overlaod& c) 
    { 
        n -= c.n; 
        return *this; 
    }
    Overlaod operator*=(const Overlaod& c) 
    { 
        n *= c.n; 
        return *this; 
    }
    Overlaod operator/=(const Overlaod& c) 
    { 
        n /= c.n; 
        return *this; 
    }
    bool operator==(const Overlaod& c)
    { 
        return n == c.n; 
    }
    bool operator!=(const Overlaod& c)
    { 
        return n != c.n; 
    }
    bool operator<(const Overlaod& c) 
    { 
        return n < c.n; 
    }
    bool operator>(const Overlaod& c) 
    { 
        return n > c.n; 
    }
    bool operator<=(const Overlaod& c) 
    { 
        return n <= c.n; 
    }
    bool operator>=(const Overlaod& c) 
    { 
        return n >= c.n; 
    }

    void display() 
    { 
        cout << n << endl; 
    }
};

int main() 
{
    Overlaod a(5), b(10);
    cout << "a == b: " << (a == b) << endl;
    cout << "a != b: " << (a != b) << endl;
    cout << "a < b: " << (a < b) << endl;
    cout << "a > b: " << (a > b) << endl;
    cout << "a <= b: " << (a <= b) << endl;
    cout << "a >= b: " << (a >= b) << endl;
    return 0;
}*/
class mystring
{
    private:
    string name;
    public:
    mystring(string str = "Null") : name(str) {}
    mystring operator+(const mystring& str)
    {
        return mystring(name + str.name);
    }
    mystring operator-(const mystring& str)
    {
        
    }
    void display()
    {
        cout<<name;
    }
};
int main()
{
    mystring s1("Hello"), s2("World");
    mystring s3 = s1 + s2;
    s3.display();
    return 0;
}