#include <iostream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;

vector<string> slice(vector<string> tokens, int start, int end) {
    if (start < 0 || end > tokens.size() || start > end) {
        throw out_of_range("Invalid slice indices");
    }
    return vector<string>(tokens.begin() + start, tokens.begin() + end);
}

//recieves input <string> and outputs <vector>
vector<string> parseExpression(const string& input) {
    vector<string> tokens;
    string currentNumber;
    bool is_decimal = false;

    for (size_t i = 0; i < input.length(); ++i) {
        char ch = input[i];
        
        if (isdigit(ch) || ch == '.') {
            if (is_decimal && ch == '.') throw invalid_argument("Invalid number entered");
            if (ch == '.') is_decimal = true;
            // Build the number as a token
            currentNumber += ch;
        } else if (ch == '*' && input[i + 1] == '*') {
            if (!currentNumber.empty()) {
                tokens.push_back(currentNumber);
                currentNumber.clear();
            }
            tokens.push_back("**");
            i++;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '%') {
            // Push any collected number before adding the operator
            if (!currentNumber.empty()) {
                tokens.push_back(currentNumber);
                currentNumber.clear();
            }
            // Add the operator as a token
            tokens.push_back(string(1, ch));
        } else if (isspace(ch)) {
            // If we encounter a space, finalize the current number if there is one
            if (!currentNumber.empty()) {
                tokens.push_back(currentNumber);
                currentNumber.clear();
            }
        } else {
            string argument = "Unknown Operator: ";
            argument += ch;
            throw invalid_argument(argument);
        }
    }
    // If there's a number left at the end, add it to the tokens
    if (!currentNumber.empty()) {
        tokens.push_back(currentNumber);
    }

    return tokens;
}

void is_valid(vector<string> tokens) {
    if (tokens[0] == "*" || tokens[0] == "**" || tokens[0] == "/" || tokens[0] == "%" || tokens[0] == ")") {
        throw invalid_argument("Invalid Syntax");
    } else {
        int open_p = 0;
        int close_p = 0;
        for (const string& token : tokens) {
            if (token == "(") open_p++;
            if (token == ")") close_p++;
        }
        if (open_p != close_p) {
            throw invalid_argument("Invalid Syntax: Unmatched Paranthesis");
        }
    }
}

int main() {
    string user_input;
    cout << "Enter the formula: ";
    getline(cin, user_input);
    cout << endl;
    try {
        vector<string> tokens = parseExpression(user_input);
        is_valid(tokens);
        
        for (const string& token : tokens) {
            cout << token << ", ";
        }
        cout << endl;
    } catch (const invalid_argument& e) {
        cout << e.what() << endl;
    }

    return 0;
}