#include <iostream>
#include <string>
#include <fstream>
using namespace std;
/*Task 1:
class FileHandler 
{
    private:
    fstream file;
    string filename;
    public:
    FileHandler(const string& fname) : filename(fname) 
    {
        file.open(filename, ios::out);
        if (file.is_open()) 
        {
            cout << "File " << filename << " opened successfully.\n";
        } 
        else 
        {
            cerr << "Failed to open file " << filename << "\n";
        }
    }
    ~FileHandler() 
    {
        if (file.is_open()) 
        {
            file.close();
            cout << "File " << filename << " closed.\n";
        }
    }
};
int main() {
    FileHandler fh("test.txt");
    return 0;
}*/
/*Task 2:
class Matrix 
{
    private:
    int** data;
    int rows, cols;
    public:
    Matrix(int r, int c) : rows(r), cols(c) 
    {
        data = new int*[rows];
        for (int i = 0; i < rows; i++) 
        {
            data[i] = new int[cols]{i+1,i+2,i+3};
        }
    }
    Matrix(const Matrix& other) 
    {
        rows=other.rows;
        cols=other.cols;
        data = new int*[rows];
        for (int i = 0; i < rows; i++) 
        {
            data[i] = new int[cols];
            for (int j = 0; j < cols; j++) 
            {
                data[i][j] = other.data[i][j];
            }
        }
    }
    ~Matrix() 
    {
        for (int i = 0; i < rows; i++) 
        {
            delete[] data[i];
        }
        delete[] data;
    }
    void display()
    {
    for(int i=0;i<rows;i++)
        {
            for (int j=0;j<cols;j++)
            cout<<data[i][j];
    cout<<endl;
        }
    }
};
int main() 
{
    Matrix m1(3, 3);
    Matrix m2 = m1;
    cout<<"Matrix 1:\n";
    m1.display();
    cout<<"Matrix 2:\n";
    m2.display();
    return 0;
}*/
/*Task 3:
class String 
{
    private:
    char* str; 
    int length; 
    public:
    String(string s) 
    {
        length = 0;
        while (s[length] != '\0') 
        { 
            length++;
        }
        str = new char[length + 1];
        for (int i = 0; i < length; i++) 
        {
            str[i] = s[i];
        }
        str[length] = '\0'; 
    }
    String(const String& other)
    {
        length = other.length;
        str = new char[length + 1]; 
        for (int i = 0; i < length; i++) 
        {
            str[i] = other.str[i];  
        }
        str[length] = '\0'; 
        delete[] str; 
        length = other.length;
        str = new char[length + 1];
        for (int i = 0; i < length; i++) 
        {
            str[i] = other.str[i];
        }
        str[length] = '\0';
    }
    ~String() 
    {
        delete[] str;
    }
    void display() 
    {
        for (int i = 0; i < length; i++) 
        {
            cout << str[i];
        }
        cout << endl;
    }
};
int main() 
{
    string str;  
    cout<<"Enter a string:";
    getline(cin,str);
    String s1(str);  
    String s2 = s1;  
    cout << "Original String: ";
    s1.display();
    cout << "Copied String: ";
    s2.display();
    cout<<"Enter another string:";
    getline(cin,str);
    String s3(str);
    s2 = s3; 
    cout << "After Assignment, s2: ";
    s2.display();
    return 0; 
}*/
/*Task 4:
class DynamicArray 
{
    private:
    int* arr;
    int size;

    public:
    DynamicArray(int s) : size(s) 
    {
        arr = new int[size]{0};
    }
    DynamicArray(const DynamicArray& other) 
    {
        size = other.size;
        arr = new int[size];
        for (int i = 0; i < size; i++) 
        {
            arr[i] = other.arr[i];
        }
    }
    DynamicArray& operator=(const DynamicArray& other) 
    {
        if (this == &other) return *this;
        delete[] arr;
        size = other.size;
        arr = new int[size];
        for (int i = 0; i < size; i++) 
        {
            arr[i] = other.arr[i];
        }
        return *this;
    }
    ~DynamicArray() 
    {
        delete[] arr;
    }
};
int main() 
{
    DynamicArray d1(5);
    DynamicArray d2 = d1;
    return 0;
}*/
class dayType 
{
    private:
    string days[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    int currentDay;
    public:
    dayType(string day) 
    {
        for (int i = 0; i < 7; i++) 
        {
            if (days[i] == day) 
            {
                currentDay = i;
                break;
            }
        }
    }
    void printDay() 
    {
        cout << "Current Day: " << days[currentDay] << endl;
    }
    string getDay() 
    {
        return days[currentDay];
    }
    string nextDay() 
    {
        return days[(currentDay + 1) % 7];
    }
    string prevDay() 
    {
        return days[(currentDay + 6) % 7];
    }
    string addDays(int n) 
    {
        return days[(currentDay + n) % 7];
    }
};
int main() 
{
    string day;
    int n;
    cout<<"Enter day:";
    getline(cin,day);
    dayType d(day);
    d.printDay();
    cout << "Next Day: " << d.nextDay() << endl;
    cout << "Previous Day: " << d.prevDay() << endl;
    cout << "Enter how many days after you want to see the the day:";
    cin  >> n;
    cout << "Day after " << n << " days: " << d.addDays(n) << endl;
    return 0;
}