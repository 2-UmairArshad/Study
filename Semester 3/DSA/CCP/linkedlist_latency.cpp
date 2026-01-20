//#include <iostream>
//#include <chrono>
//#include <fstream>
//
//using namespace std;
//using namespace std::chrono;
//
//struct Node {
//    int data;
//    Node* next;
//};
//
//class LinkedListResourcePool {
//    Node* head;
//
//public:
//    LinkedListResourcePool() {
//        head = NULL;
//    }
//
//    void allocate(int value) {
//        Node* temp = new Node;
//        temp->data = value;
//        temp->next = head;
//        head = temp;
//    }
//
//    void deallocate() {
//        if (head == NULL) return;
//
//        Node* temp = head;
//        head = head->next;
//        delete temp;
//    }
//
//    void cleanupResources() {}
//};
//
//int main() {
//    LinkedListResourcePool pool;
//    ofstream file("linkedlist_latency.csv");
//
//    int opCount = 0;
//    for (int i = 0; i < 10000; i++) {
//        auto start = high_resolution_clock::now();
//        pool.allocate(i);
//        auto end = high_resolution_clock::now();
//
//        double time_ms =
//            duration<double, milli>(end - start).count();
//
//        file << opCount++ << "," << time_ms << "\n";
//    }
//    for (int i = 0; i < 100000; i++) {
//        auto start = high_resolution_clock::now();
//        pool.deallocate();
//        pool.allocate(i);
//        auto end = high_resolution_clock::now();
//
//        double time_ms =
//            duration<double, milli>(end - start).count();
//
//        file << opCount++ << "," << time_ms << "\n";
//    }
//
//    file.close();
//    cout << "Linked List latency data written to linkedlist_latency.csv\n";
//    return 0;
//}
