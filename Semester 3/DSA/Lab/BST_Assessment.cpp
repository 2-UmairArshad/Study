#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
private:
    Node* root;

    int height(Node* node) {
        if (node == nullptr) 
            return 0;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        if (leftHeight > rightHeight) 
            return leftHeight;
        else 
            return rightHeight;
    }

public:
    BST() {
        root = nullptr;
    }

    void insertIterative(int value) {
        Node* newNode = new Node(value);
        if (root == nullptr) {
            root = newNode;
            return;
        }
        Node* current = root;
        Node* parent = nullptr;
        while (current != nullptr) {
            parent = current;
            if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (value < parent->data) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }
    }

    bool searchIterative(int value) {
        Node* current = root;
        while (current != nullptr) {
            if (value == current->data) {
                return true;
            } else if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    void deleteIterative(int value) {
        Node* parent = nullptr;
        Node* current = root;
        while (current != nullptr && current->data != value) {
            parent = current;
            if (value < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        if (current == nullptr) 
            return;

        if (current->left == nullptr && current->right == nullptr) {
            if (current == root) {
                root = nullptr;
            } else if (parent->left == current) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete current;
        }
        else if (current->left == nullptr) {
            if (current == root) {
                root = current->right;
            } else if (parent->left == current) {
                parent->left = current->right;
            } else {
                parent->right = current->right;
            }
            delete current;
        }
        else if (current->right == nullptr) {
            if (current == root) {
                root = current->left;
            } else if (parent->left == current) {
                parent->left = current->left;
            } else {
                parent->right = current->left;
            }
            delete current;
        }
        else {
            Node* successorParent = current;
            Node* successor = current->right;
            while (successor->left != nullptr) {
                successorParent = successor;
                successor = successor->left;
            }
            current->data = successor->data;
            if (successorParent->left == successor) {
                successorParent->left = successor->right;
            } else {
                successorParent->right = successor->right;
            }
            delete successor;
        }
    }

    int treeHeight() {
        return height(root);
    }

    void LevelofTree() {
        if (root == nullptr) {
            cout << "Tree is Empty\n";
        }

        else
            cout << "Levels of Tree are" << height(root) + 1;
    }

    int balanceFactor(Node* node) {
        if (node == nullptr) 
            return 0;
        return height(node->right) - height(node->left);
    }

    Node* getRoot() {
        return root;
    }

    void inorder(Node* node) {
        if (node == nullptr) 
            return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void displayInorder() {
        cout << "Inorder traversal: ";
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    int choice, value, count;

    while (true) {
        cout << "\nBinary Search Tree Operations Menu\n";
        cout << "1. Insert values\n";
        cout << "2. Delete a value\n";
        cout << "3. Search for a value\n";
        cout << "4. Display tree height\n";
        cout << "5. Display inorder traversal\n";
        cout << "6. Calculate balance factor of root\n";
        cout << "7. Display level of Tree\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "How many values do you want to insert: ";
                cin >> count;
                for (int i = 0; i < count; i++) {
                    cout << "Enter value " << i + 1 << ": ";
                    cin >> value;
                    tree.insertIterative(value);
                }
                cout << "All values inserted successfully.\n";
                break;
            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                tree.deleteIterative(value);
                cout << "Deletion performed (if value existed).\n";
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (tree.searchIterative(value)) {
                    cout << "Value found in the tree.\n";
                } else {
                    cout << "Value not found in the tree.\n";
                }
                break;
            case 4:
                cout << "Tree height: " << tree.treeHeight() << endl;
                break;
            case 5:
                tree.displayInorder();
                break;
            case 6:
                cout << "Balance factor of root: " << tree.balanceFactor(tree.getRoot()) << endl;
                break;
            case 7:
                tree.LevelofTree();
                break;
            case 8:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}