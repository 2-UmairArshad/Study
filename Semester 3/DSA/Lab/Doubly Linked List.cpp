#include <iostream> 
using namespace std;
//-----------------TASK 1------------------							
//class Node {
//public:
//    int data;
//    Node* next;
//    Node* prev;
//    Node(int val) {
//        data = val;
//        next = NULL;
//        prev = NULL;
//    }
//};
//class DoublyLinkedList {
//public:
//    Node* head;
//    DoublyLinkedList() {
//        head = NULL;
//    }
//    void insertAtStart(int val) {
//        Node* newNode = new Node(val);
//        if (head == NULL) {
//            head = newNode;
//        }
//        else {
//            newNode->next = head;
//            head->prev = newNode;
//            head = newNode;
//        }
//    }
//    void insertAtEnd(int val) {
//        Node* newNode = new Node(val);
//        if (head == NULL) {
//            head = newNode;
//            return;
//        }
//        Node* temp = head;
//        while (temp->next != NULL) {
//            temp = temp->next;
//        }
//        temp->next = newNode;
//        newNode->prev = temp;
//    }
//    void insertAfter(int key, int val) {
//        Node* newNode = new Node(val);
//        if (head == NULL) {
//            head = newNode;
//            return;
//        }
//        Node* temp = head;
//        while (temp != NULL && temp->data != key) {
//            temp = temp->next;
//        }
//        if (temp == NULL) {
//            cout << "Node not found.\n";
//            return;
//        }
//        newNode->next = temp->next;
//        newNode->prev = temp;
//        if (temp->next != NULL) {
//            temp->next->prev = newNode;
//        }
//        temp->next = newNode;
//    }
//    void insertBefore(int key, int val) {
//        Node* newNode = new Node(val);
//        if (head == NULL) {
//            head = newNode;
//            return;
//        }
//        Node* temp = head;
//        while (temp != NULL && temp->data != key) {
//            temp = temp->next;
//        }
//        if (temp == NULL) {
//            cout << "Node not found.\n";
//            return;
//        }
//        newNode->prev = temp->prev;
//        newNode->next = temp;
//
//        if (temp->prev != NULL) {
//            temp->prev->next = newNode;
//        }
//        else {
//            head = newNode;
//        }
//
//        temp->prev = newNode;
//    }
//    void deleteNode(int key) {
//        if (head == NULL) {
//            cout << "List is empty.\n";
//            return;
//        }
//        Node* temp = head;
//        while (temp != NULL && temp->data != key) {
//            temp = temp->next;
//        }
//        if (temp == NULL) {
//            cout << "Node not found.\n";
//            return;
//        }
//        if (temp->prev != NULL) {
//            temp->prev->next = temp->next;
//        }
//        else {
//            head = temp->next;
//        }
//
//        if (temp->next != NULL) {
//            temp->next->prev = temp->prev;
//        }
//
//        delete temp;
//    }
//    void reverseDisplay() {
//        if (head == NULL) {
//            cout << "List is empty.\n";
//            return;
//        }
//        Node* temp = head;
//        while (temp->next != NULL) {
//            temp = temp->next;
//        }
//        while (temp != NULL) {
//            cout << temp->data << " <> ";
//            temp = temp->prev;
//        }
//        cout << "NULL\n";
//    }
//    void display() {
//        Node* temp = head;
//        while (temp != NULL) {
//            cout << temp->data << " <> ";
//            temp = temp->next;
//        }
//        cout << "NULL\n";
//    }
//};
//int main() {
//    DoublyLinkedList list;
//    list.insertAtStart(1);
//    list.insertAtEnd(2);
//    list.insertAtEnd(3);
//    list.insertAtEnd(4);
//    list.insertAtEnd(5);
//    list.display();
//    list.insertAfter(2, 8);
//    list.insertBefore(2, 9);
//    list.deleteNode(3);
//    list.display();
//    list.reverseDisplay();
//    return 0;
//}

//----------------TASK 2--------------
//class Node {
//public:
//    int data;
//    Node* next;
//    Node* prev;
//    Node(int val) {
//        data = val;
//        next = NULL;
//        prev = NULL;
//    }
//};
//class CircularDoublyLinkedList {
//public:
//    Node* head;
//    CircularDoublyLinkedList() {
//        head = NULL;
//    }
//    void insertBeforeValue(int key, int val) {
//        if (head == NULL) {
//            cout << "List is empty.\n";
//            return;
//        }
//        Node* temp = head;
//        do {
//            if (temp->data == key) {
//                Node* newNode = new Node(val);
//                newNode->prev = temp->prev;
//                newNode->next = temp;
//                temp->prev->next = newNode;
//                temp->prev = newNode;
//                if (temp == head) {
//                    head = newNode;
//                }
//                return;
//            }
//            temp = temp->next;
//        } while (temp != head);
//        cout << "Node not found.\n";
//    }
//    void deleteByValue(int key) {
//        if (head == NULL) {
//            cout << "List is empty.\n";
//            return;
//        }
//        Node* temp = head;
//        do {
//            if (temp->data == key) {
//                temp->prev->next = temp->next;
//                temp->next->prev = temp->prev;
//                if (temp == head) {
//                    head = head->next;
//                    if (temp == head) {
//                        head = NULL;
//                    }
//                }
//                delete temp;
//                return;
//            }
//            temp = temp->next;
//        } while (temp != head);
//        cout << "Node not found.\n";
//    }
//    void display() {
//        if (head == NULL) {
//            cout << "List is empty.\n";
//            return;
//        }
//        Node* temp = head;
//        do {
//            cout << temp->data << " <> ";
//            temp = temp->next;
//        } while (temp != head);
//        cout << "(back to head)\n";
//    }
//    void insertAtEnd(int val) {
//        Node* newNode = new Node(val);
//        if (head == NULL) {
//            head = newNode;
//            head->next = head;
//            head->prev = head;
//        }
//        else {
//            Node* tail = head->prev;
//            tail->next = newNode;
//            newNode->prev = tail;
//            newNode->next = head;
//            head->prev = newNode;
//        }
//    }
//};
//int main() {
//    CircularDoublyLinkedList list;
//    list.insertAtEnd(10);
//    list.insertAtEnd(20);
//    list.insertAtEnd(30);
//    list.display();
//    list.insertBeforeValue(20, 15);
//    list.display();
//    list.deleteByValue(20);
//    list.display();
//    return 0;
//}