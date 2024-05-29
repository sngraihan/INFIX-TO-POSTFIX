#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool isOperator(char ch){
    vector<char> operators = {'+', '-', '/', '%'};
    return find(operators.begin(), operators.end(), ch) != operators.end();
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

void printfunc(vector<string> txt){
    for(auto itr = txt.begin(); itr != txt.end(); itr++){
        cout << *itr << " ";
    }
    cout << endl;
}


int main(){
    string input;
    getline(cin, input);
    vector<string> infix = strToInfix(input);
	printfunc(infix);


    return 0;



}
