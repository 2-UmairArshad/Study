#include <iostream>
using namespace std;

class node {
public:
    int data;
    node* left;
    node* right;

    node(int val) {
        data = val;
        left = right = NULL;
    }
};

class bst {
private:
    node* root;

public:
    bst() {
        root = NULL;
    }

    void replaceChild(node* parent, node* oldChild, node* newChild) {
        if (parent == NULL) {
            root = newChild;
            return;
        }
        if (parent->left == oldChild)
            parent->left = newChild;
        else
            parent->right = newChild;
    }

    // Task 1
    void insert(int val) {
        node* newnode = new node(val);
        if (root == NULL) {
            root = newnode;
            return;
        }
        node* current = root;
        node* parent = NULL;
        while (current != NULL) {
            parent = current;
            if (val < current->data)
                current = current->left;
            else if (val > current->data)
                current = current->right;
            else
                return;
        }
        if (val < parent->data)
            parent->left = newnode;
        else
            parent->right = newnode;
    }

    // Task 2
    bool search(int key) {
        node* current = root;
        while (current != NULL) {
            if (key == current->data) return true;
            if (key < current->data) current = current->left;
            else current = current->right;
        }
        return false;
    }

    // Task 3
    void deleteNode(int key) {
        node* current = root;
        node* parent = NULL;
        while (current != NULL && current->data != key) {
            parent = current;
            if (key < current->data)
                current = current->left;
            else
                current = current->right;
        }
        if (current == NULL) return;

        if (current->left == NULL && current->right == NULL) {
            replaceChild(parent, current, NULL);
            delete current;
        }
        else if (current->left == NULL || current->right == NULL) {
            node* child = (current->left != NULL) ? current->left : current->right;
            replaceChild(parent, current, child);
            delete current;
        }
        else {
            node* succParent = current;
            node* succ = current->right;
            while (succ->left != NULL) {
                succParent = succ;
                succ = succ->left;
            }
            current->data = succ->data;
            node* succChild = (succ->left != NULL) ? succ->left : succ->right;
            replaceChild(succParent, succ, succChild);
            delete succ;
        }
    }

    // Task 4
    int height(node* nd) {
        if (nd == NULL) return -1;

        node* stack[1000];
        int depth[1000];
        int top = -1;

        stack[++top] = nd;
        depth[top] = 0;
        int maxH = 0;

        while (top >= 0) {
            node* cur = stack[top];
            int d = depth[top--];
            if (cur != NULL) {
                maxH = max(maxH, d);
                if (cur->left != NULL) {
                    stack[++top] = cur->left;
                    depth[top] = d + 1;
                }
                if (cur->right != NULL) {
                    stack[++top] = cur->right;
                    depth[top] = d + 1;
                }
            }
        }
        return maxH;
    }

    int heightOfTree() {
        return height(root);
    }

    // Task 5
    int balanceFactor(node* nd) {
        if (nd == NULL) return 0;
        return height(nd->left) - height(nd->right);
    }

    node* getRoot() { return root; }
};

int main() {
    bst t;
    int choice, val;

    while (true) {
        cout << "\n===== MENU =====\n";
        cout << "1. Insert\n";
        cout << "2. Search\n";
        cout << "3. Delete\n";
        cout << "4. Height of Tree\n";
        cout << "5. Balance Factor of Root\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value: ";
            cin >> val;
            t.insert(val);
            break;
        case 2:
            cout << "Enter value: ";
            cin >> val;
            cout << (t.search(val) ? "Found\n" : "Not Found\n");
            break;
        case 3:
            cout << "Enter value to delete: ";
            cin >> val;
            t.deleteNode(val);
            break;
        case 4:
            cout << "Height = " << t.heightOfTree() << endl;
            break;
        case 5:
            cout << "Balance Factor (root) = "
                << t.balanceFactor(t.getRoot()) << endl;
            break;
        case 0:
            return 0;
        default:
            cout << "Invalid choice!\n";
        }
    }
}