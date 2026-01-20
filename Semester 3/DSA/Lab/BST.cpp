#include <iostream>
using namespace std;
class bnode
{
public:
    int key;
    bnode* leftchild;
    bnode* rightchild;

    bnode(int data)
    {
        key = data;
        leftchild = NULL;
        rightchild = NULL;
    }
};

class BST
{
public:
    bnode* root;
    BST()
    {
        root = NULL;
    }
    void insertion(bnode* newnode)
    {
        if (root == NULL)
        {
            root = newnode;
        }

        else
        {
            bnode* rptr = root;
            bnode* bptr = NULL;
            while (rptr != NULL)
            {
                if (newnode->key < rptr->key)
                {
                    bptr = rptr;
                    rptr = rptr->leftchild;
                }
                else if (newnode->key > rptr->key)
                {
                    bptr = rptr;
                    rptr = rptr->rightchild;
                }
                else
                {
                    cout << "Duplicate value not allowed\n";
                    return;
                }
            }
            if (newnode->key < bptr->key)
            {
                bptr->leftchild = newnode;
            }
            else if (newnode->key > bptr->key)
            {
                bptr->rightchild = newnode;
            }
        }
    }

    void search(int data)
    {
        bnode* rptr = root;
        while (rptr != NULL)
        {
            if (rptr->key == data)
            {
                cout << "Yes,Data is present " << rptr->key << endl;
                return;
            }
            else if (data < rptr->key)
            {
                rptr = rptr->leftchild;
            }
            else if (data > rptr->key)
            {
                rptr = rptr->rightchild;
            }
        }
        cout << "Data is not found " << endl;
    }
    void findMin()
    {
        bnode* rptr = root;
        if (root == NULL)
        {
            cout << "Root their is no element inthe tree" << endl;
            return;
        }
        while (rptr->leftchild != NULL)
        {
            rptr = rptr->leftchild;
        }
        cout << "The last leaf node is " << rptr->key << endl;
    }

    void findMax()
    {
        bnode* bptr = NULL;
        bnode* rptr = root;
        if (root == NULL)
        {
            cout << "Root their is no element inthe tree" << endl;
            return;
        }
        while (rptr != NULL)
        {
            bptr = rptr;
            rptr = rptr->rightchild;
        }
        cout << "The last max leaf node is " << bptr->key << endl;
    }

    void deleteNode(int data)
    {
        if (root == NULL)
        {
            cout << "There is no element to delete " << endl;
            return;
        }
        bnode* rptr = root;
        bnode* bptr = NULL;
        bnode* child = NULL;
        while (rptr != NULL && rptr->key != data)
        {
            if (data < rptr->key)
            {
                bptr = rptr;

                rptr = rptr->leftchild;
            }

            else if (data > rptr->key)
            {
                bptr = rptr;
                rptr = rptr->rightchild;
            }
        }

        if (rptr == NULL)
        {
            cout << "Data not found!" << endl;
            return;
        }

        if (root->leftchild == NULL && root->rightchild == NULL && root == rptr)
        {

            delete root;
            root = NULL;
            return;
        }

        if (rptr->leftchild == NULL && rptr->rightchild == NULL)
        { 

            if (bptr->leftchild == rptr)
            { 
                bptr->leftchild = NULL;
                delete rptr;
                return;
            }
            else if (bptr->rightchild == rptr)
            { 
                bptr->rightchild = NULL;
                delete rptr;
                return;
            }
        }
        if (rptr->leftchild != NULL && rptr->rightchild == NULL)
        {
            child = rptr->leftchild;
            if (rptr == root)
            {
                delete root;
                root = child;
                return;
            }
            if (bptr->leftchild == rptr)
            {
                bptr->leftchild = child;
            }
            else
            {
                bptr->rightchild = child;
            }
            delete rptr;
        }
        else if (rptr->rightchild != NULL && rptr->leftchild == NULL)
        {
            child = rptr->rightchild;
            if (rptr == root)
            {
                delete root;
                root = child;
                return;
            }
            if (bptr->rightchild == rptr)
            {
                bptr->rightchild = child;
            }
            else
            {
                bptr->leftchild = child;
            }
            delete rptr;
        }
        if (rptr->leftchild != NULL && rptr->rightchild != NULL)
        {
            bnode* Parent = rptr;
            bnode* succ = rptr->rightchild;

            while (succ->leftchild != NULL)
            {
                Parent = succ;
                succ = succ->leftchild;
            }
            rptr->key = succ->key;

            if (Parent->leftchild == succ)
            {
                Parent->leftchild = succ->rightchild;
            }
            else
            {
                Parent->rightchild = succ->rightchild;
            }

            delete succ;
            return;
        }
    }
};
int main()
{
    BST tree;
    tree.insertion(new bnode(50));
    tree.insertion(new bnode(30));
    tree.insertion(new bnode(70));
    tree.insertion(new bnode(20));
    tree.insertion(new bnode(40));
    tree.insertion(new bnode(60));
    tree.insertion(new bnode(80));
    tree.insertion(new bnode(45));

    cout << "Search for 40: ";
    tree.search(40); 

    cout << "Search for 90: ";
    tree.search(90); 

    cout << "Minimum value: ";
    tree.findMin(); 

    cout << "Maximum value: ";
    tree.findMax(); 

    cout << "\nDeleting a leaf node (20)...\n";
    tree.deleteNode(20); 

    cout << "Deleting a node with one child (30)...\n";
    tree.deleteNode(30);

    cout << "Deleting a node with two children (50)...\n";
    tree.deleteNode(50);

    cout << "\nFinal tree checks:\n";
    cout << "Minimum value: ";
    tree.findMin();
    cout << "Maximum value: ";
    tree.findMax();

    return 0;
}