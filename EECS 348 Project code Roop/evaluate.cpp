#include <vector>
#include <string>
#include <stdexcept>
#include <cmath>
#include "evaluate.h"
#include "parse.h"

using namespace std;

double applyOperation(double a, double b, const string& op) {
    if (op == "+") return a + b;
    if (op == "-") return a - b;
    if (op == "*") return a * b;
    if (op == "/") {
        if (b == 0) throw invalid_argument("Division by zero");
        return a / b;
    }
    if (op == "%") return fmod(a, b);
    if (op == "**") return pow(a, b);

    throw invalid_argument("Unknown operator");
}

double evaluateTokens(vector<string>& tokens, int start, int end) {
    if (start == end) return stod(tokens[start]);

    int parenBalance = 0;
    int lastOperator = -1;
    int precedence = -1;

    for (int i = start; i <= end; i++) {
        if (tokens[i] == "(") parenBalance++;
        if (tokens[i] == ")") parenBalance--;

        if (parenBalance == 0 &&
            (tokens[i] == "+" || tokens[i] == "-" || tokens[i] == "*" || tokens[i] == "/" ||
                tokens[i] == "**" || tokens[i] == "%")) {

            int currentPrecedence =
                (tokens[i] == "+" || tokens[i] == "-") ? 1 :
                (tokens[i] == "*" || tokens[i] == "/" || tokens[i] == "%") ? 2 : 3;

            if (currentPrecedence >= precedence) {
                precedence = currentPrecedence;
                lastOperator = i;
            }
        }
    }

    if (lastOperator == -1) {
        if (tokens[start] == "(" && tokens[end] == ")") {
            return evaluateTokens(tokens, start + 1, end - 1);
        }
        throw invalid_argument("Invalid expression");
    }

    double left = evaluateTokens(tokens, start, lastOperator - 1);
    double right = evaluateTokens(tokens, lastOperator + 1, end);

    return applyOperation(left, right, tokens[lastOperator]);
}

double evaluateExpression(vector<string>& tokens) {
    return evaluateTokens(tokens, 0, tokens.size() - 1);
}
