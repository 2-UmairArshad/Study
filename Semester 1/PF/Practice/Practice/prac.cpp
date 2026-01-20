#include<iostream>
using namespace std;
int main()
{
    int n,s,m=0,i;
    cout<<"Enter how many numbers you want enter:";
    cin>>n;
    int b[n],a[n];
    for ( i = 0; i <n; i++)
    {
       cout<<"Enter numbers:";
       cin>>a[i];
       if (a[i]%2==0)
       {
        b[i]=a[i];
       }
       
    }
    for ( i = 0; i < n; i++)
    {if (b[i]%2==0)
    {
        cout<<b[i]<<" ";
    }
    }
    
    for ( i = 0; i < n; i++)
    {
        for ( s=1; s < n; s++)
        {
            if (b[i]<b[s])
            {
                m=b[s];
            }
            
        }
        
    }
    cout<<endl<<m;
    return 0;
}