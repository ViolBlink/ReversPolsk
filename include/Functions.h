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
// inline - для избежания множественного определения при включении в несколько файлов
// Prior - приоритет каждой операции для работы сортировки
inline std::map<std::string, int> Prior = {{"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3}, {"Sin", 4}, {"Cos", 4}};
// Operations - какие команды поддерживает
// TODO: Реализовать несколько
inline std::map<std::string, int> Operations = {{"Calculate", 0}, {"Show", 1}};
//Arity - кол-во принимаемых операторов
inline std::map<std::string, int> Arity = {{"+", 2}, {"-", 2}, {"*", 2}, {"/", 2}, {"^", 2}, {"Sin", 1}, {"Cos", 1}};
// Variables - словарь переменных
inline std::map<std::string, double> Variables = {};

std::queue<std::string> ToPolsk(std::string);
double FromPolsk(std::queue<std::string>);
std::string ShowPolsk(std::queue<std::string>);
std::string DeleteSpase(std::string);
std::string HandleNegative(std::string);
void QMerge(std::queue<std::string>*, std::queue<std::string>);
std::vector<std::string> parce(std::string);
void SetVar(std::vector<std::string>);

bool IsNum(char);
bool IsOp(char);
bool IsFun(char);

std::string DeleteLast(std::string);

#endif //FUNCTIONS_H;