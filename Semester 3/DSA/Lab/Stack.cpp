#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

class Node
{
public:
    string data;
    Node *next;
    Node(const string &d) : data(d), next(nullptr) {}
};

class Stack
{
private:
    Node *topInt;
    Node *topChar;
    Node *topString;

public:
    Stack() : topInt(nullptr), topChar(nullptr), topString(nullptr) {}
    void pushInt(int value)
    {
        Node *n = new Node(to_string(value));
        n->next = topInt;
        topInt = n;
    }
    int popInt()
    {
        if (!topInt)
            return 0;
        string s = topInt->data;
        Node *tmp = topInt;
        topInt = topInt->next;
        delete tmp;
        return stoi(s);
    }
    int peekInt()
    {
        if (!topInt)
            return 0;
        return stoi(topInt->data);
    }
    bool isEmptyInt() { return topInt == nullptr; }
    void pushChar(char c)
    {
        string s(1, c);
        Node *n = new Node(s);
        n->next = topChar;
        topChar = n;
    }
    char popChar()
    {
        if (!topChar)
            return '\0';
        string s = topChar->data;
        Node *tmp = topChar;
        topChar = topChar->next;
        delete tmp;
        return s.empty() ? '\0' : s[0];
    }
    char peekChar()
    {
        if (!topChar)
            return '\0';
        return topChar->data.empty() ? '\0' : topChar->data[0];
    }
    bool isEmptyChar() { return topChar == nullptr; }
    void pushString(const string &str)
    {
        Node *n = new Node(str);
        n->next = topString;
        topString = n;
    }
    string popString()
    {
        if (!topString)
            return "";
        string s = topString->data;
        Node *tmp = topString;
        topString = topString->next;
        delete tmp;
        return s;
    }
    string peekString()
    {
        if (!topString)
            return "";
        return topString->data;
    }
    bool isEmptyString() { return topString == nullptr; }
    ~Stack()
    {
        while (topInt)
        {
            Node *t = topInt;
            topInt = topInt->next;
            delete t;
        }
        while (topChar)
        {
            Node *t = topChar;
            topChar = topChar->next;
            delete t;
        }
        while (topString)
        {
            Node *t = topString;
            topString = topString->next;
            delete t;
        }
    }
};

bool isMatchingPair(char openC, char closeC)
{
    return (openC == '(' && closeC == ')') ||
           (openC == '[' && closeC == ']') ||
           (openC == '{' && closeC == '}');
}

bool isBalanced(Stack &s, const string &expr)
{
    while (!s.isEmptyChar())
        s.popChar();
    for (char ch : expr)
    {
        if (ch == '(' || ch == '[' || ch == '{')
        {
            s.pushChar(ch);
        }
        else if (ch == ')' || ch == ']' || ch == '}')
        {
            if (s.isEmptyChar())
                return false;
            char topC = s.popChar();
            if (!isMatchingPair(topC, ch))
                return false;
        }
    }
    return s.isEmptyChar();
}

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    if (op == '^')
        return 3;
    return 0;
}

bool isOperator(char c)
{
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

vector<string> tokenizeInfix(const string &expr)
{
    vector<string> tokens;
    int n = expr.size();
    for (int i = 0; i < n;)
    {
        if (isspace(expr[i]))
        {
            ++i;
            continue;
        }
        if (isalnum(expr[i]))
        {
            string operand;
            while (i < n && isalnum(expr[i]))
            {
                operand.push_back(expr[i++]);
            }
            tokens.push_back(operand);
        }
        else
        {
            tokens.push_back(string(1, expr[i]));
            ++i;
        }
    }
    return tokens;
}

string infixToPostfix(Stack &s, const string &infix)
{
    while (!s.isEmptyChar())
        s.popChar();
    vector<string> tokens = tokenizeInfix(infix);
    vector<string> output;
    for (const string &tok : tokens)
    {
        if (tok.empty())
            continue;
        if (isalnum(tok[0]))
        {
            output.push_back(tok);
        }
        else
        {
            char c = tok[0];
            if (c == '(')
            {
                s.pushChar('(');
            }
            else if (c == ')')
            {
                while (!s.isEmptyChar() && s.peekChar() != '(')
                {
                    string op(1, s.popChar());
                    output.push_back(op);
                }
                if (!s.isEmptyChar() && s.peekChar() == '(')
                    s.popChar();
            }
            else if (isOperator(c))
            {
                while (!s.isEmptyChar())
                {
                    char topOp = s.peekChar();
                    if (topOp == '(')
                        break;
                    int pTop = precedence(topOp);
                    int pCurr = precedence(c);
                    if ((c == '^' && pTop > pCurr) || (c != '^' && pTop >= pCurr))
                    {
                        string op(1, s.popChar());
                        output.push_back(op);
                    }
                    else
                        break;
                }
                s.pushChar(c);
            }
        }
    }
    while (!s.isEmptyChar())
    {
        char top = s.popChar();
        if (top != '(' && top != ')')
            output.push_back(string(1, top));
    }
    string res;
    for (size_t i = 0; i < output.size(); ++i)
    {
        if (i)
            res += ' ';
        res += output[i];
    }
    return res;
}

string infixToPrefix(Stack &s, const string &infix)
{
    vector<string> tokens = tokenizeInfix(infix);
    vector<string> revTokens;
    for (int i = (int)tokens.size() - 1; i >= 0; --i)
    {
        string t = tokens[i];
        if (t == "(")
            t = ")";
        else if (t == ")")
            t = "(";
        revTokens.push_back(t);
    }
    string joined;
    for (size_t i = 0; i < revTokens.size(); ++i)
    {
        if (i)
            joined += ' ';
        joined += revTokens[i];
    }
    string postfixRev = infixToPostfix(s, joined);
    vector<string> postTokens;
    {
        string cur;
        for (char c : postfixRev)
        {
            if (c == ' ')
            {
                if (!cur.empty())
                {
                    postTokens.push_back(cur);
                    cur.clear();
                }
            }
            else
                cur.push_back(c);
        }
        if (!cur.empty())
            postTokens.push_back(cur);
    }
    string prefix;
    for (int i = (int)postTokens.size() - 1; i >= 0; --i)
    {
        if (!prefix.empty())
            prefix += ' ';
        prefix += postTokens[i];
    }
    return prefix;
}

int evaluatePostfix(Stack &s, const string &postfix)
{
    while (!s.isEmptyInt())
        s.popInt();
    vector<string> tokens;
    string cur;
    for (char c : postfix)
    {
        if (c == ' ')
        {
            if (!cur.empty())
            {
                tokens.push_back(cur);
                cur.clear();
            }
        }
        else
            cur.push_back(c);
    }
    if (!cur.empty())
        tokens.push_back(cur);
    for (const string &tok : tokens)
    {
        if (tok.empty())
            continue;
        if (isdigit(tok[0]) || (tok.size() > 1 && (tok[0] == '-' && isdigit(tok[1]))))
        {
            s.pushInt(stoi(tok));
        }
        else if (tok.size() == 1 && isOperator(tok[0]))
        {
            int b = s.popInt();
            int a = s.popInt();
            int res = 0;
            char op = tok[0];
            switch (op)
            {
            case '+':
                res = a + b;
                break;
            case '-':
                res = a - b;
                break;
            case '*':
                res = a * b;
                break;
            case '/':
                res = a / b;
                break;
            case '^':
            {
                int r = 1;
                for (int i = 0; i < b; ++i)
                    r *= a;
                res = r;
                break;
            }
            }
            s.pushInt(res);
        }
    }
    return s.peekInt();
}

string convertComplex(Stack &s, const string &expr)
{
    return infixToPostfix(s, expr);
}

int main()
{
    Stack s;
    string balInput = "{{{()}}}{}(()){}";
    bool bal = isBalanced(s, balInput);
    if (bal)
        cout << "Input: " << balInput << "\nOutput: Accepted: Sequence is right\n";
    else
        cout << "Input: " << balInput << "\nOutput: Rejected: Sequence is wrong\n";
    cout << "\n";
    string inf1 = "(A+B)*C";
    string post1 = infixToPostfix(s, inf1);
    cout << "Infix: " << inf1 << "\nPostfix: " << post1 << "\n\n";
    string inf2 = "(A+B)*(C+D)";
    string pref2 = infixToPrefix(s, inf2);
    cout << "Infix: " << inf2 << "\nPrefix: " << pref2 << "\n\n";
    string pfEval = "2 3 + 5 *";
    int result = evaluatePostfix(s, pfEval);
    cout << "Postfix: " << pfEval << "\nEvaluation result: " << result << "\n\n";
    string complexIn = "((A+B)*C-(D-E))^(F+G)";
    string complexPost = convertComplex(s, complexIn);
    cout << "Infix: " << complexIn << "\nPostfix: " << complexPost << "\n";
    return 0;
}
