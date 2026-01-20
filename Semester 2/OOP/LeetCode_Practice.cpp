#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    char data;
    Node* next;
    Node(char val) { data = val; next = NULL; }
};

class Stack {
    Node* top;
public:
    Stack() { top = NULL; }

    bool isEmpty() { return top == NULL; }

    void push(char val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (isEmpty()) {
            return '\0';
        }
        Node* temp = top;
        char val = top->data;
        top = top->next;
        delete temp;
        return val;
    }

    char peek() {
        if (!isEmpty()) return top->data;
        return '\0';
    }
};

bool isBalanced(string expr) {
    Stack s;
    for (int i = 0; i < expr.length(); i++) {
        char ch = expr[i];
        if (ch == '(' || ch == '[' || ch == '{') {
            s.push(ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}') {
            if (s.isEmpty()) return false;
            char topChar = s.pop();
            if ((ch == ')' && topChar != '(') ||
                (ch == ']' && topChar != '[') ||
                (ch == '}' && topChar != '{')) {
                return false;
            }
        }
    }
    return s.isEmpty();
}

int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

string infixToPostfix(string infix) {
    Stack s;
    string postfix = "";

    for (int i = 0; i < infix.length(); i++) {
        char ch = infix[i];

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            postfix += ch;
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix += s.pop();
            }
            s.pop();
        }
        else {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch)) {
                postfix += s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.isEmpty()) {
        postfix += s.pop();
    }

    return postfix;
}

string infixToPrefix(string infix) {
    Stack s;
    string prefix = "";

    for (int i = infix.length() - 1; i >= 0; i--) {
        char ch = infix[i];

        if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) {
            prefix += ch;
        }
        else if (ch == ')') {
            s.push(ch);
        }
        else if (ch == '(') {
            while (!s.isEmpty() && s.peek() != ')') {
                prefix += s.pop();
            }
            s.pop();
        }
        else {
            while (!s.isEmpty() && precedence(s.peek()) > precedence(ch)) {
                prefix += s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.isEmpty()) {
        prefix += s.pop();
    }

    string result = "";
    for (int i = prefix.length() - 1; i >= 0; i--) {
        result += prefix[i];
    }
    return result;
}

class IntNode {
public:
    int data;
    IntNode* next;
    IntNode(int val) { data = val; next = NULL; }
};

class IntStack {
    IntNode* top;
public:
    IntStack() { top = NULL; }

    bool isEmpty() { return top == NULL; }

    void push(int val) {
        IntNode* newNode = new IntNode(val);
        newNode->next = top;
        top = newNode;
    }

    int pop() {
        if (isEmpty()) {
            return -1;
        }
        IntNode* temp = top;
        int val = top->data;
        top = top->next;
        delete temp;
        return val;
    }

    int peek() {
        if (!isEmpty()) return top->data;
        return -1;
    }
};

int evaluatePostfix(string postfix) {
    IntStack s;

    for (int i = 0; i < postfix.length(); i++) {
        char ch = postfix[i];

        if (ch >= '0' && ch <= '9') {
            s.push(ch - '0');
        }
        else {
            int val2 = s.pop();
            int val1 = s.pop();

            switch (ch) {
            case '+': s.push(val1 + val2); break;
            case '-': s.push(val1 - val2); break;
            case '*': s.push(val1 * val2); break;
            case '/': s.push(val1 / val2); break;
            }
        }
    }
    return s.pop();
}

int main() {
    cout << "Balanced Parentheses Check:" << endl;
    string test1 = "{{({(){()}})}}";
    string test2 = "{({[)}]}";
    cout << test1 << " : " << (isBalanced(test1) ? "Balanced" : "Not Balanced") << endl;
    cout << test2 << " : " << (isBalanced(test2) ? "Balanced" : "Not Balanced") << endl;

    cout << "\nInfix to Postfix:" << endl;
    string infix1 = "(A+B+D)*C-A/B";
    cout << infix1 << " -> " << infixToPostfix(infix1) << endl;

    cout << "\nInfix to Prefix:" << endl;
    string infix2 = "(A+B)*(C+D)/(E-F)";
    cout << infix2 << " -> " << infixToPrefix(infix2) << endl;

    cout << "\nPostfix Evaluation:" << endl;
    string postfix = "23+5*";
    cout << postfix << " = " << evaluatePostfix(postfix) << endl;

    cout << "\nComplex Expression Conversion:" << endl;
    string complexInfix = "((A+B)*C-(D-E))^(F+G)";
    cout << complexInfix << " -> " << infixToPostfix(complexInfix) << endl;

    return 0;
}
