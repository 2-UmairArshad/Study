//#include <iostream>
//#include <vector>
//#include <chrono>
//#include <fstream>
//
//using namespace std;
//using namespace std::chrono;
//
//class HeapResourcePool {
//    vector<int> heap;
//
//    void heapifyUp(int i) {
//        while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
//            swap(heap[i], heap[(i - 1) / 2]);
//            i = (i - 1) / 2;
//        }
//    }
//
//    void heapifyDown(int i) {
//        int smallest = i;
//        int l = 2 * i + 1;
//        int r = 2 * i + 2;
//
//        if (l < heap.size() && heap[l] < heap[smallest])
//            smallest = l;
//        if (r < heap.size() && heap[r] < heap[smallest])
//            smallest = r;
//
//        if (smallest != i) {
//            swap(heap[i], heap[smallest]);
//            heapifyDown(smallest);
//        }
//    }
//
//public:
//    void allocate(int value) {
//        heap.push_back(value);
//        heapifyUp(heap.size() - 1);
//    }
//
//    void deallocate() {
//        if (heap.empty()) return;
//
//        heap[0] = heap.back();
//        heap.pop_back();
//        heapifyDown(0);
//    }
//};
//
//int main() {
//    HeapResourcePool pool;
//    ofstream file("heap_latency.csv");
//
//    int op = 0;
//
//    // Ramp-Up Phase (10,000 inserts)
//    for (int i = 0; i < 10000; i++) {
//        auto start = high_resolution_clock::now();
//        pool.allocate(i);
//        auto end = high_resolution_clock::now();
//
//        double ms = duration<double, milli>(end - start).count();
//        file << op++ << "," << ms << "\n";
//    }
//
//    // Peak Phase (100,000 delete + insert)
//    for (int i = 0; i < 100000; i++) {
//        auto start = high_resolution_clock::now();
//        pool.deallocate();
//        pool.allocate(i);
//        auto end = high_resolution_clock::now();
//
//        double ms = duration<double, milli>(end - start).count();
//        file << op++ << "," << ms << "\n";
//    }
//
//    file.close();
//    cout << "Heap pool data written to heap_latency.csv\n";
//    return 0;
//}
