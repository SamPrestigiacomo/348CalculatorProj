#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>

//4 * (3 + 2) % 7 - 1 (test case)

//#############Known exceptions (not handled)########################
//divide by zero
//no number in expression EXAMPLE: "((()))"
//raising a number to a float

//#############Need to do########################
//write a recursive algorithm that calculates the result
//write a funciton that does exponents including negative exponents

/*Code takes an input string from the user that is the expression that needs to be evaulated
the program takes the string and puts the 'bits' into a vector
while it does this it checks for syntactical errors (note that 4+(-4) is allowed but 4+-4 is not)
currently program only prints the parsed bits, it needs to be able to evaluate the expression*/

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
                if (currentNumber == ".") throw invalid_argument("Invalid Syntax: Illegal Use of Operators");
                is_decimal = false;
                tokens.push_back(currentNumber);
                currentNumber.clear();
            }
            tokens.push_back("**");
            i++;
        } else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' || ch == ')' || ch == '%') {
            // Push any collected number before adding the operator
            if (!currentNumber.empty()) {
                if (currentNumber == ".") throw invalid_argument("Invalid Syntax: Illegal Use of Operators");
                is_decimal = false;
                tokens.push_back(currentNumber);
                currentNumber.clear();
            }
            // Add the operator as a token
            tokens.push_back(string(1, ch));
        } else if (isspace(ch)) {
            // If we encounter a space, finalize the current number if there is one
            if (!currentNumber.empty()) {
                if (currentNumber == ".") throw invalid_argument("Invalid Syntax: Illegal Use of Operators");
                is_decimal = false;
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
        if (currentNumber == ".") throw invalid_argument("Invalid Syntax: Illegal Use of Operators");
        tokens.push_back(currentNumber);
    }

    return tokens;
}

void is_valid(vector<string> tokens) {
    if (tokens[0] == "*" || tokens[0] == "**" || tokens[0] == "/" || tokens[0] == "%" || tokens[0] == ")") {
        throw invalid_argument("Invalid Syntax");
    } else {
        int end = tokens.size() - 1;
        if (tokens[end] == "*" || tokens[end] == "**" || tokens[end] == "/" || tokens[end] == "%" || tokens[end] == "(") {
            throw invalid_argument("Invalid Syntax");
        }
        int counter = 0;
        for (const string& token : tokens) {
            if (token == "(") counter++;
            if (token == ")") counter--;
            if (counter < 0) throw invalid_argument("Invalid Syntax: Unmatched Parenthesis");
        }
        if (counter != 0) {
            throw invalid_argument("Invalid Syntax: Unmatched Parenthesis");
        }
        string previous = "0";
        for (string token : tokens) {
            if (previous == "-" && token == "-") throw invalid_argument("Invalid Syntax: Illegal Use of Operators");
            if (previous == "+" && token == "+") throw invalid_argument("Invalid Syntax: Illegal Use of Operators");
            previous = token;
        }
        previous = "0";
        for (string token : tokens) {
            if (token != "(" && token != ")") {
                if (token == previous) {
                    if (token == "*" || token == "/" || token == "**" || token == "%") throw invalid_argument("Invalid Syntax: Illegal Use of Operators");
                }
                previous = token;
            }
        }
    }
}

void lower(string& str) {
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c){return tolower(c);});
}

int main() {
    string user_input;
    while (1) {
        cout << "Enter \"Exit\" to quit" << endl;
        cout << "Enter an Expression: ";
        getline(cin, user_input);
        cout << endl;
        lower(user_input);
        if(user_input == "exit" || user_input == "\"exit\"") break;
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
    }
    cout << "Exiting program" << endl;

    return 0;
}