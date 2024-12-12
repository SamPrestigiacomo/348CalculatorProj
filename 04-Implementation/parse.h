#ifndef PARSE_H
#define PARSE_H

#include <vector>
#include <string>

std::vector<std::string> parseExpression(const std::string& input);
void isValidExpression(const std::vector<std::string>& tokens);

#endif
