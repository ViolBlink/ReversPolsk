#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <cmath>

std::queue<std::string> ToPolsk(std::string);
double FromPolsk(std::queue<std::string>);
std::string DeleteSpase(std::string);
void QMerge(std::queue<std::string>*, std::queue<std::string>);

int IsNum(std::string);
int IsOp(std::string);

std::string DeleteLast(std::string);

#endif //FUNCTIONS_H