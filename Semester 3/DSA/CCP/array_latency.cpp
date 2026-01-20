//#include <iostream>
//#include <chrono>
//#include <fstream>
//
//using namespace std;
//using namespace std::chrono;
//
//class ArrayResourcePool {
//    int* arr;
//    int capacity;
//    int size;
//
//public:
//    ArrayResourcePool() {
//        capacity = 100;
//        size = 0;
//        arr = new int[capacity];
//        for (int i = 0; i < capacity; i++)
//            arr[i] = -1;
//    }
//
//    void resize() {
//        int newcap = capacity * 2;
//        int* temp = new int[newcap];
//
//        for (int i = 0; i < newcap; i++)
//            temp[i] = -1;
//
//        for (int i = 0; i < capacity; i++)
//            temp[i] = arr[i];
//
//        delete[] arr;
//        arr = temp;
//        capacity = newcap;
//    }
//
//    void allocate(int value) {
//        if (size == capacity)
//            resize();
//
//        arr[size++] = value;
//    }
//
//    void deallocate(int index) {
//        if (index >= 0 && index < size)
//            arr[index] = -1;
//    }
//
//    void cleanupResources() {
//        int* temp = new int[capacity];
//        int newsize = 0;
//
//        for (int i = 0; i < capacity; i++) {
//            if (arr[i] != -1)
//                temp[newsize++] = arr[i];
//        }
//
//        delete[] arr;
//        arr = temp;
//        size = newsize;
//    }
//};
//
//int main() {
//    ArrayResourcePool pool;
//    ofstream file("array_latency.csv");
//
//    int op = 0;
//
//    for (int i = 0; i < 10000; i++) {
//        auto start = high_resolution_clock::now();
//        pool.allocate(i);
//        auto end = high_resolution_clock::now();
//
//        double ms = duration<double, milli>(end - start).count();
//        file << op++ << "," << ms << "\n";
//    }
//
//    for (int i = 0; i < 100000; i++) {
//        auto start = high_resolution_clock::now();
//        pool.deallocate(i % 5000);
//        pool.allocate(i);
//        auto end = high_resolution_clock::now();
//
//        double ms = duration<double, milli>(end - start).count();
//        file << op++ << "," << ms << "\n";
//    }
//
//    auto start = high_resolution_clock::now();
//    pool.cleanupResources();
//    auto end = high_resolution_clock::now();
//
//    double ms = duration<double, milli>(end - start).count();
//    file << op++ << "," << ms << "\n";
//
//    file.close();
//    cout << "array pool data written to array_latency.csv\n";
//    return 0;
//}
