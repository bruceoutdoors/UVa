#include <iostream>
#include <string>
#include <stack>

using namespace std;

int main ()
{
    int count;
    cin >> count;
    cin.get();
    
    while (count-- > 0) {
        stack<char> operatorStack;
        bool isValid = true;
        string parens;
        getline (cin, parens);
        
        for (char &c : parens) {
            if (c == '(') {
                operatorStack.push(c);
            } else if (c == '[') {
                operatorStack.push(c);
            } else if (c == ')') {
                if (operatorStack.empty() || operatorStack.top() != '(') {
                    isValid = false;
                    break;
                }
                operatorStack.pop();
            } else if (c == ']') {
                if (operatorStack.empty() || operatorStack.top() != '[') {
                    isValid = false;
                    break;
                }
                operatorStack.pop();
            }
            
        }
        
        if (!operatorStack.empty()) isValid = false;
            
        cout << (isValid ? "Yes" : "No") << endl;
        
    }
}
