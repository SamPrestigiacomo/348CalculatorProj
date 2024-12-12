#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>
#include "parse.h"

using namespace std;

vector<string> parseExpression(const string& input) { // function that parses the input into bits
    vector<string> tokens;
    string currentNumber;
    bool is_decimal = false; //keeps track of whether or not a decimal is encountered

    for (size_t i = 0; i < input.length(); ++i) {
        char ch = input[i];

        if (isdigit(ch) || ch == '.') {
            if (is_decimal && ch == '.') throw invalid_argument("Invalid number entered"); //checks if a number has multiple decimal points
            if (ch == '.') is_decimal = true;
            currentNumber += ch; //adds a digit to the current number until an operator is encountered
        }
        else if (ch == '*' && input[i + 1] == '*') { //checks for an exponent
            if (!currentNumber.empty()) { //adds the built number
                tokens.push_back(currentNumber);
                currentNumber.clear();
                is_decimal = false;
            }
            tokens.push_back("**");
            i++;
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '%') { //checks for operators
            if (!currentNumber.empty()) {
                tokens.push_back(currentNumber);
                currentNumber.clear();
                is_decimal = false;
            }
            tokens.push_back(string(1, ch));
        }
        else if (isspace(ch)) { //checks for spaces in the input
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

    if (!currentNumber.empty()) { //adds the last number in an input if the input does not end in ")"
        tokens.push_back(currentNumber);
    }

    return tokens;
}

void isValidExpression(const vector<string>& tokens) { //checks for common syntax errors
    int parenCount = 0;
    string previous = "";

    for (const auto& token : tokens) {
        if (token == "(") parenCount++;
        else if (token == ")") parenCount--;

        if (parenCount < 0) throw invalid_argument("Unmatched parenthesis"); //checks if a ")" appears before a matching "("

        //if statement checks if there are multiple operators in a row, unless permitted
        if (previous == "*" || previous == "/" || previous == "+" || previous == "-" ||
            previous == "**" || previous == "%" || previous == "(") {
            if (token == "*" || token == "/" || token == "+" || token == "-" ||
                token == "**" || token == "%" || token == ")") {
                if (previous != "(" && (previous != "+" || previous != "-")) {    
                    throw invalid_argument("Invalid operator usage");
                }
            }
        }

        previous = token;
    }

    if (parenCount != 0) throw invalid_argument("Unmatched parenthesis"); //checks if a ")" is missing
}
