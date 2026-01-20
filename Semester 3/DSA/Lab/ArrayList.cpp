#include <iostream>
using namespace std;

class ArrayList {
private:
    int* data;
    int size;
    int capacity;

public:
    ArrayList(int cap = 5) {
        capacity = cap;
        size = 0;
        data = new int[capacity];
    }

    void add(int value) {
        if (size == capacity) {
            resize();
        }
        data[size++] = value;
    }

    void insert(int index, int value) {
        if (index < 0 || index > size) {
            cout << "Invalid index\n";
            return;
        }
        if (size == capacity) 
            resize();

        for (int i = size; i > index; i--)
            data[i] = data[i - 1];
        data[index] = value;
        size++;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index\n";
            return;
        }
        for (int i = index; i < size - 1; i++)
            data[i] = data[i + 1];
        size--;
    }

    int get(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index\n";
            return -1;
        }
        return data[index];
    }

    void print() {
        for (int i = 0; i < size; i++)
            cout << data[i] << " ";
        cout << endl;
    }

    void resize() {
        int newCap = capacity * 2;
        int* newData = new int[newCap];
        for (int i = 0; i < size; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCap;
    }

    void searchAndDelete(int value) {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (data[i] == value) {
                remove(i);
                found = true;
                i--; 
            }
        }
        if (found) {
            cout << "Element found and deleted. Updated list: ";
            print();
        }
        else {
            cout << "Element not found!" << endl;
        }
    }
};

int main() {
    ArrayList list;
    int n, value, searchValue;

    cout << "How many elements do you want to add? ";
    cin >> n;

    cout << "Enter " << n << " integers:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> value;
        list.add(value);
    }

    cout << "Current list: ";
    list.print();

    cout << "Enter a value to search and delete: ";
    cin >> searchValue;

    list.searchAndDelete(searchValue);

    return 0;
}
//class ArrayList {
//private:
//    int* data;
//    int size;
//    int capacity;
//
//public:
//    ArrayList(int cap = 5) {
//        capacity = cap;
//        size = 0;
//        data = new int[capacity];
//    }
//
//    void add(int value) {
//        if (size == capacity) {
//            resize();
//        }
//        data[size++] = value;
//    }
//
//    void insert(int index, int value) {
//        if (index < 0 || index > size) {
//            cout << "Invalid index\n";
//            return;
//        }
//        if (size == capacity) resize();
//
//        for (int i = size; i > index; i--)
//            data[i] = data[i - 1];
//        data[index] = value;
//        size++;
//    }
//
//    void remove(int index) {
//        if (index < 0 || index >= size) {
//            cout << "Invalid index\n";
//            return;
//        }
//        for (int i = index; i < size - 1; i++)
//            data[i] = data[i + 1];
//        size--;
//    }
//
//    int get(int index) {
//        if (index < 0 || index >= size) {
//            cout << "Invalid index\n";
//            return -1;
//        }
//        return data[index];
//    }
//
//    void print() {
//        for (int i = 0; i < size; i++)
//            cout << data[i] << " ";
//        cout << endl;
//    }
//
//    void resize() {
//        int newCap = capacity * 2;
//        int* newData = new int[newCap];
//        for (int i = 0; i < size; i++)
//            newData[i] = data[i];
//        delete[] data;
//        data = newData;
//        capacity = newCap;
//    }
//
//    void countEvenOdd() {
//        int even = 0, odd = 0;
//
//        for (int i = 0; i < size; i++) {
//            if (data[i] % 2 == 0) {
//                even++;
//            }
//            else {
//                odd++;
//            }
//        }
//
//        cout << "Even numbers: " << even << endl;
//        cout << "Odd numbers: " << odd << endl;
//    }
//};
//
//int main() {
//    ArrayList list;
//    int n, value;
//
//    cout << "How many elements do you want to add? ";
//    cin >> n;
//
//    cout << "Enter " << n << " integers:" << endl;
//    for (int i = 0; i < n; i++) {
//        cin >> value;
//        list.add(value);
//    }
//
//    cout << "Current list: ";
//    list.print();
//
//    list.countEvenOdd();
//
//    return 0;
//}