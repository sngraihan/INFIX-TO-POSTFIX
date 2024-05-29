#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

bool isOperator(char ch) {
    vector<char> operators = {'+', '-', '*', '/', '%'};
    return find(operators.begin(), operators.end(), ch) != operators.end();
}

int oprank(string op) {
    if (op == "-" || op == "+") {
        return 1;
    } else if (op == "*" || op == "/" || op == "%") {
        return 2;
    }
    return 0;
}

double Operasi(double a, double b, string op){
    double total = 0;
     if(op == "+"){
         total = b + a;
     }else if(op == "-"){
         total = b - a;
     }else if(op == "*"){
         total = b * a;
     }else if(op == "/"){
         total = b / a;
     }else if(op == "%"){
         total = (int) b % (int) a;
     }
     return total;
 }

vector<string> strToInfix(string str) {
    vector<string> infix;
    string angka;
    int ssize = str.size();

    for (size_t i = 0; i < ssize; i++) {
        if (isspace(str[i])) {
            continue;
        } else if (isdigit(str[i])) {
            angka += str[i];
        } else if (str[i] == '-' && (i == 0 || isOperator(str[i-1]) || str[i-1] == '(')) {
            if (i + 2 < ssize && str[i-1] == '(' && str[i+2] == ')') {
                angka += str[i];
            } else if (isOperator(str[i-1]) || str[i+1] == '(' || str[i+1] == ')' || str[i-1] == '(') {
                infix.push_back("-1");
                infix.push_back("*");
            } else if ((isdigit(str[i+1]) && str[i-1] == '(') || i == 0) {
                angka += str[i];
            } else {
                infix.push_back("-");
            }
        } else {
            if (!angka.empty()) {
                infix.push_back(angka);
                angka.clear();
            }
            infix.push_back(string(1, str[i]));
        }
    }

    if (!angka.empty()) {
        infix.push_back(angka);
    }

    return infix;
}

vector<string> infixToPostfix(vector<string>& infix) {
    vector<string> postfix;
    vector<string> op;
    for (auto itr = infix.begin(); itr != infix.end(); itr++) {
        string str = *itr;
        if (isdigit(str[0]) || (str[0] == '-' && str.size() > 1 && isdigit(str[1]))) {
            postfix.push_back(str);
        } else if (str == "(") {
            op.push_back(str); 
        } else if (str == ")") {
            while (!op.empty() && op.back() != "(") {
                postfix.push_back(op.back());
                op.pop_back();
            }
            if (!op.empty()) {
                op.pop_back();
            }
        } else {
            while (!op.empty() && op.back() != "(" && oprank(str) <= oprank(op.back())) {
                postfix.push_back(op.back());
                op.pop_back();
            }
            op.push_back(str);
        }
    }
    while (!op.empty()) {
        postfix.push_back(op.back());
        op.pop_back();
    }
    return postfix;
}

 double evaluate(vector<string> postfix){
     vector<string> op = {"+" , "-", "*", "/", "%"};
     stack<double> total;

     double a,b,c;
     string temp;
     for(auto itr = postfix.begin(); itr != postfix.end(); itr++){
         string str = *itr;
         if(isOperator(str[0]) && str.size() == 1){
             a = total.top();
             total.pop();
             b = total.top();
             total.pop();
             temp = str;
             c = Operasi(a, b, temp);
             total.push(c);
         }
         else{
             total.push(strtod((str).c_str(), NULL));
         }
     }
     return total.top();
 }



void printfunc(const vector<string>& txt) {
    for (const auto& s : txt) {
        cout << s << " ";
    }
    cout << endl;
}

int main() {
    string input;
    getline(cin, input);
    vector<string> infix = strToInfix(input);
    vector<string> postfix = infixToPostfix(infix);
    printfunc(infix);
    printfunc(postfix);
	cout << evaluate(postfix);

    return 0;

}
