#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <cmath>
#include <map>

// Словарь приориоритета операторов
std::map<std::string, int> Prior = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}};

std::queue<std::string> ToPolsk(std::string);
double FromPolsk(std::queue<std::string>);
std::string DeleteSpase(std::string);
void QMerge(std::queue<std::string>*, std::queue<std::string>);

int IsNum(char);
int IsOp(char);

std::string DeleteLast(std::string);

#endif //FUNCTIONS_H