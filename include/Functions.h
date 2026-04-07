#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <queue>
#include <cmath>
#include <map>

using namespace std;

// Словарь приориоритета операторов
// inline - для избежания множественного определения при включении в несколько файлов
inline map<string, int> Prior = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}};

queue<string> ToPolsk(string);
double FromPolsk(queue<string>);
string DeleteSpase(string);
void QMerge(queue<string>*, queue<string>);

int IsNum(char);
int IsOp(char);

string DeleteLast(string);

#endif //FUNCTIONS_H