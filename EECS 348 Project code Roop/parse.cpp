#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>
#include "parse.h"

using namespace std;

vector<string> parseExpression(const string& input) {
    vector<string> tokens;
    string currentNumber;
    bool is_decimal = false;

    for (size_t i = 0; i < input.length(); ++i) {
        char ch = input[i];

        if (isdigit(ch) || ch == '.') {
            if (is_decimal && ch == '.') throw invalid_argument("Invalid number entered");
            if (ch == '.') is_decimal = true;
            currentNumber += ch;
        }
        else if (ch == '*' && input[i + 1] == '*') {
            if (!currentNumber.empty()) {
                tokens.push_back(currentNumber);
                currentNumber.clear();
                is_decimal = false;
            }
            tokens.push_back("**");
            i++;
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '%') {
            if (!currentNumber.empty()) {
                tokens.push_back(currentNumber);
                currentNumber.clear();
                is_decimal = false;
            }
            tokens.push_back(string(1, ch));
        }
        else if (isspace(ch)) {
            if (!currentNumber.empty()) {
                tokens.push_back(currentNumber);
                currentNumber.clear();
                is_decimal = false;
            }
        }
        else {
            throw invalid_argument(string("Unknown operator: ") + ch);
        }
    }

    if (!currentNumber.empty()) {
        tokens.push_back(currentNumber);
    }

    return tokens;
}

void isValidExpression(const vector<string>& tokens) {
    int parenCount = 0;
    string previous = "";

    for (const auto& token : tokens) {
        if (token == "(") parenCount++;
        else if (token == ")") parenCount--;

        if (parenCount < 0) throw invalid_argument("Unmatched parenthesis");

        if (previous == "*" || previous == "/" || previous == "+" || previous == "-" ||
            previous == "**" || previous == "%" || previous == "(") {
            if (token == "*" || token == "/" || token == "+" || token == "-" ||
                token == "**" || token == "%" || token == ")") {
                throw invalid_argument("Invalid operator usage");
            }
        }

        previous = token;
    }

    if (parenCount != 0) throw invalid_argument("Unmatched parenthesis");
}
