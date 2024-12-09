#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <cctype>
#include <algorithm>
#include "parse.h"
#include "evaluate.h"

using namespace std;

void lower(string& str) { //converts the user input to lowercase to easily check if the input is "exit"
    transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return tolower(c); });
}

int main() {
    string user_input;

    while (true) {
        cout << "Enter \"Exit\" to quit" << endl;
        cout << "Enter an Expression: ";
        getline(cin, user_input);
        cout << endl;

        lower(user_input);
        if (user_input == "exit") break;

        try {
            vector<string> tokens = parseExpression(user_input); //parses the input into readable bits
            isValidExpression(tokens); //checks the input for common invalid syntax

            double result = evaluateExpression(tokens); //sends the parsed bits to be evaluated

            cout << "Result: " << result << endl;
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    cout << "Exiting program." << endl;
    return 0;
}
