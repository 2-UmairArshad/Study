#include <iostream>
using namespace std;
class Energy 
{
private:
    double joules; 
    double kilowatt;
    double calories;
public:
    Energy(double j = 0) : joules(j) {}
    static Energy fromCalories(double cal) 
    {
        return Energy(cal * 4.184);
    }
    static Energy fromKWh(double kwh) 
    {
        return Energy(kwh * 3.6e6);
    }
    Energy operator+(const Energy& other) const 
    {
        return Energy(joules + other.joules);
    }
    Energy operator-(const Energy& other) const 
    {
        return Energy(joules - other.joules);
    }
    Energy operator*(double factor) const 
    {
        return Energy(joules * factor);
    }
    Energy operator/(double divisor) const 
    {
        return Energy(joules / divisor);
    }
    bool operator==(const Energy& other) const 
    {
        return joules == other.joules;
    }
    bool operator!=(const Energy& other) const 
    {
        return !(*this == other);
    }
    bool operator>(const Energy& other) const 
    {
        return joules > other.joules;
    }
    bool operator<(const Energy& other) const 
    {
        return joules < other.joules;
    }
    Energy& operator+=(const Energy& other) 
    {
        joules += other.joules;
        return *this;
    }
    Energy& operator-=(const Energy& other) 
    {
        joules -= other.joules;
        return *this;
    }
    Energy& operator++() 
    { 
        joules += 10;
        return *this;
    }
    Energy operator++(int) 
    { 
        Energy temp = *this;
        joules += 10;
        return temp;
    }
    Energy& operator--() 
    { 
        joules -= 10;
        return *this;
    }
    Energy operator--(int) 
    { 
        Energy temp = *this;
        joules -= 10;
        return temp;
    }
    friend ostream& operator<<(ostream& os, const Energy& e) {
        os << e.joules << " J";
        return os;
    }
    friend istream& operator>>(istream& is, Energy& e) {
        is >> e.joules;
        return is;
    }
};
int main() 
{
    Energy e1(500), e2 = Energy::fromCalories(100);
    Energy e3 = e1 + e2;
    cout << "e1: " << e1 << endl;
    cout << "e2 (from 100 cal): " << e2 << endl;
    cout << "e3 = e1 + e2: " << e3 << endl;
    e3 += Energy::fromKWh(0.001);
    cout << "After adding 0.001 kWh: " << e3 << endl;
    cout << "Comparison (e1 < e2): " << (e1 < e2) << endl;
    Energy* ePtr = new Energy(1000);
    cout << "Dynamically allocated Energy: " << ePtr->operator++() << endl;
    delete ePtr;
    return 0;
}