#include<iostream>
#include<string>
using namespace std;
int main();
{
    int *n;
    int b=2;
    n=&b;
    cout<<n;
    n=b;
    cout<<*n;
    b=n;
    cout<<b;
    return 0;
}
