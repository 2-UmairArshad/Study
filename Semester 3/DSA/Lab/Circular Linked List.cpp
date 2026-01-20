#include <iostream>
using namespace std;

//class Node {
//public:
//    int data;
//    Node* next;
//    Node(int val) {
//        data = val;
//        next = NULL;
//    }
//};
//
//class CircularLinkedList {
//public:
//    Node* head;
//
//    CircularLinkedList() {
//        head = NULL;
//    }
//
//    void insertEnd(int val) {
//        Node* newNode = new Node(val);
//        if (head == NULL) {
//            head = newNode;
//            newNode->next = head;
//            return;
//        }
//        Node* temp = head;
//        while (temp->next != head) {
//            temp = temp->next;
//        }
//        temp->next = newNode;
//        newNode->next = head;
//    }
//
//    void display() {
//        if (head == NULL) {
//            cout << "List is empty\n";
//            return;
//        }
//        Node* temp = head;
//        do {
//            cout << temp->data << " -> ";
//            temp = temp->next;
//        } while (temp != head);
//        cout << "(back to head)" << endl;
//    }
//    void insertAfterEveryK(int k, int X) {
//        if (head == NULL || k <= 0) {
//            cout << "Invalid list or k value!" << endl;
//            return;
//        }
//
//        Node* temp = head;
//        int count = 1;
//        bool inserted = false;
//
//        do {
//            if (count % k == 0) {
//                Node* newNode = new Node(X);
//                newNode->next = temp->next;
//                temp->next = newNode;
//                temp = newNode;
//                inserted = true;
//            }
//            temp = temp->next;
//            count++;
//        } while (temp != head);
//
//        if (!inserted) {
//            cout << "No insertion performed. k might be larger than list size." << endl;
//        }
//    }
//};
//
//int main() {
//    CircularLinkedList cll;
//
//    cll.insertEnd(10);
//    cll.insertEnd(20);
//    cll.insertEnd(30);
//    cll.insertEnd(40);
//    cll.insertEnd(50);
//
//    cout << "Original List: ";
//    cll.display();
//
//    int k = 2;
//    int X = 99;
//    cout << "\nInserting " << X << " after every " << k << "nd node..." << endl;
//    cll.insertAfterEveryK(k, X);
//
//    cout << "Modified List: ";
//    cll.display();
//
//    return 0;
//}







//class Node {
//public:
//    int data;
//    Node* next;
//    Node(int val) {
//        data = val;
//        next = NULL;
//    }
//};
//
//class CircularLinkedList {
//public:
//    Node* head;
//
//    CircularLinkedList() {
//        head = NULL;
//    }
//
//    void insertEnd(int val) {
//        Node* newNode = new Node(val);
//        if (head == NULL) {
//            head = newNode;
//            newNode->next = head;
//            return;
//        }
//        Node* temp = head;
//        while (temp->next != head) {
//            temp = temp->next;
//        }
//        temp->next = newNode;
//        newNode->next = head;
//    }
//
//    void display() {
//        if (head == NULL) {
//            cout << "List is empty\n";
//            return;
//        }
//        Node* temp = head;
//        do {
//            cout << temp->data << " -> ";
//            temp = temp->next;
//        } while (temp != head);
//        cout << "(back to head)" << endl;
//    }
//
//    void createList(int n) {
//        for (int i = 1; i <= n; i++) {
//            insertEnd(i);
//        }
//    }
//
//    int josephus(int m) {
//        if (head == NULL) {
//            cout << "List is empty!" << endl;
//            return -1;
//        }
//
//        if (m <= 0) {
//            cout << "Invalid m value!" << endl;
//            return -1;
//        }
//
//        if (head->next == head) {
//            int result = head->data;
//            cout << "Only one person remains: " << result << endl;
//            return result;
//        }
//
//        Node* current = head;
//        Node* previous = NULL;
//
//        cout << "Elimination sequence: ";
//
//        while (current->next != current) {
//            for (int i = 1; i < m; i++) {
//                previous = current;
//                current = current->next;
//            }
//
//            cout << current->data;
//            if (current->next != current) {
//                cout << " -> ";
//            }
//
//            previous->next = current->next;
//            Node* toDelete = current;
//
//            if (toDelete == head) {
//                head = current->next;
//            }
//
//            current = current->next;
//            delete toDelete;
//        }
//
//        cout << endl;
//
//        int result = current->data;
//        head = current;
//
//        cout << "The survivor is: " << result << endl;
//        return result;
//    }
//};
//
//int main() {
//    cout << "\nInput: n=5, m=2" << endl;
//    CircularLinkedList josephusList1;
//    josephusList1.createList(5);
//    cout << "Initial circle: ";
//    josephusList1.display();
//
//    return 0;
//}













//class Node {
//public:
//    int data;
//    Node* next;
//    Node(int val) {
//        data = val;
//        next = NULL;
//    }
//};
//
//class CircularLinkedList {
//public:
//    Node* head;
//
//    CircularLinkedList() {
//        head = NULL;
//    }
//
//    void insertEnd(int val) {
//        Node* newNode = new Node(val);
//        if (head == NULL) {
//            head = newNode;
//            newNode->next = head;
//            return;
//        }
//        Node* temp = head;
//        while (temp->next != head) {
//            temp = temp->next;
//        }
//        temp->next = newNode;
//        newNode->next = head;
//    }
//
//    void display() {
//        if (head == NULL) {
//            cout << "List is empty\n";
//            return;
//        }
//        Node* temp = head;
//        do {
//            cout << temp->data << " -> ";
//            temp = temp->next;
//        } while (temp != head);
//        cout << "(back to head)" << endl;
//    }
//
//    void displayWithStart() {
//        if (head == NULL) {
//            cout << "List is empty\n";
//            return;
//        }
//        cout << head->data << " -> ";
//        Node* temp = head->next;
//        while (temp != head) {
//            cout << temp->data << " -> ";
//            temp = temp->next;
//        }
//        cout << "(back to " << head->data << ")" << endl;
//    }
//
//    void splitOddEven(CircularLinkedList& oddList, CircularLinkedList& evenList) {
//        if (head == NULL) {
//            cout << "Original list is empty!" << endl;
//            return;
//        }
//
//        Node* temp = head;
//        int position = 1;
//
//        do {
//            if (position % 2 == 1) {
//                oddList.insertEnd(temp->data);
//            }
//            else { 
//                evenList.insertEnd(temp->data);
//            }
//            temp = temp->next;
//            position++;
//        } while (temp != head);
//
//        cout << "Successfully split the list!" << endl;
//        cout << "Odd positions: " << (position + 1) / 2 << " nodes" << endl;
//        cout << "Even positions: " << position / 2 << " nodes" << endl;
//    }
//
//    void createSampleList() {
//        insertEnd(10);
//        insertEnd(20);
//        insertEnd(30);
//        insertEnd(40);
//        insertEnd(50);
//        insertEnd(60);
//    }
//};
//
//int main() {
//    CircularLinkedList originalList;
//    originalList.createSampleList(); 
//
//    cout << "Original List: ";
//    originalList.displayWithStart();
//
//    CircularLinkedList oddList, evenList;
//    originalList.splitOddEven(oddList, evenList);
//
//    cout << "\nOdd Position List (1st, 3rd, 5th...): ";
//    oddList.displayWithStart();
//
//    cout << "Even Position List (2nd, 4th, 6th...): ";
//    evenList.displayWithStart();
//
//    return 0;
//}