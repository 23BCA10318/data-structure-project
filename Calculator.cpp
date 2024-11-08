#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cctype>
#include <map>
#include <vector>

using namespace std;


int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

double applyOperation(double a, double b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': 
            if (b == 0) {
                throw runtime_error("Division by zero");
            }
            return a / b;
    }
    return 0;
}

vector<string> infixToPostfix(const string& expression) {
    stack<char> operators;
    vector<string> output;
    istringstream tokens(expression);
    string token;

    while (tokens >> token) {
        if (isdigit(token[0])) {
            output.push_back(token);
        } else if (token[0] == '(') {
            operators.push('(');
        } else if (token[0] == ')') {
            while (!operators.empty() && operators.top() != '(') {
                output.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.pop(); 
        } else { 
            while (!operators.empty() && precedence(operators.top()) >= precedence(token[0])) {
                output.push_back(string(1, operators.top()));
                operators.pop();
            }
            operators.push(token[0]);
        }
    }
    
    while (!operators.empty()) {
        output.push_back(string(1, operators.top()));
        operators.pop();
    }

    return output;
}


double evaluatePostfix(const vector<string>& postfix) {
    stack<double> values;

    for (const string& token : postfix) {
        if (isdigit(token[0])) {
            values.push(stod(token));
        } else {
            double b = values.top(); values.pop();
            double a = values.top(); values.pop();
            double result = applyOperation(a, b, token[0]);
            values.push(result);
        }
    }
    return values.top();
}


double calculate(const string& expression) {
    vector<string> postfix = infixToPostfix(expression);
    return evaluatePostfix(postfix);
}

int main() {
    string expression;

    cout << "Enter an expression (use spaces between numbers and operators): ";
    getline(cin, expression);

    try {
        double result = calculate(expression);
        cout << "Result: " << result << endl;
    } catch (const runtime_error& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}