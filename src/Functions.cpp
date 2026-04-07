#include "../include/Functions.h"
using std::queue;
using std::string;
using std::stack;
using std::vector;


// Возвращает 1, если символ является цифрой ('0'–'9'), иначе 0
bool IsNum(char ch)
{
    if((ch >= '0') && (ch <= '9')) return true;

    return false;
}

// Возвращает 1, если строка является одним из операторов: + - * / ^
bool IsOp(char str)
{
    if(((str == '+') || (str == '-') || (str == '*')
            || (str == '/') || (str == '^'))) return true;

    return false;
}

// Возвращает 1, если строка ни оператор ни символ, а значит, возможно, функция
bool IsFun(char c) {    return (isalpha(c)); }

// Переводит инфиксное выражение (например "3+4*2") в обратную польскую нотацию.
// Возвращает очередь токенов (чисел и операторов) в порядке ОПН.
queue<string> ToPolsk(string str)
{
    queue<string> Ans;   // Очередь результата (ОПН)
    stack<string> OpSt;  // Стек операторов
    // bool BraFlag = 0;
    string Str1 = "";

    str = DeleteSpase(str);     // Убираем пробелы из входной строки
    str = HandleNegative(str);  // Превращаем все -a в 0-a

    for (int i = 0; i < str.length(); i++)
    {
        // Обработка начал функции
        if(IsFun(str[i]))
        {
            string name = "";
            // Прохожусь по имени пока не найду (
            while ((i < str.length() - 1) && (str[i] != '('))
            {
                name += str[i];
                i++;
            }

            OpSt.push(name);
        }

        // Обработка открывающей скобки: рекурсивно обрабатываем содержимое
        if(str[i] == '(')
        {
            stack<char> st; // Вспомогательный стек для отслеживания вложенных скобок
            st.push(str[i]);
            string NewStr = "";

            i++;

            // Собираем содержимое скобок, учитывая вложенность
            while((!st.empty()) && (i < str.length()))
            {
                NewStr += str[i];

                if(str[i] == '(') st.push(str[i]);
                if(str[i] == ')') st.pop();
                i++;
            }
            NewStr = DeleteLast(NewStr); // Удаляем закрывающую ')'

            // Рекурсивно переводим содержимое скобок и добавляем к результату
            QMerge(&Ans, ToPolsk(NewStr));
        }

        // Считываем число (целое или дробное) и помещаем его в очередь результата
        if (IsNum(str[i]))
        {
            Str1 = str[i];
            i++;

            // Продолжаем читать цифры и точку (для дробных чисел)
            while ((i < str.length()) && ((IsNum(str[i])) || (str[i] == '.')))
            {
                Str1 += str[i];
                i++;
            }

            Ans.push(Str1);
        }


        // Помещаем текущий символ в стек операторов
        // Реализован алгоритм сортировочной станции
        if (( i < str.length() ) && ( IsOp(str[i]) ))
        {
            string PreStr = "";
            PreStr += str[i];
            if(PreStr == "^")
            {
                while( (!OpSt.empty()) && (Prior[OpSt.top()] > Prior[PreStr]))
                {
                    Ans.push(OpSt.top());
                    OpSt.pop();
                }
            }
            else
            {
                while((!OpSt.empty()) && (Prior[OpSt.top()] >= Prior[PreStr]))
                {
                    Ans.push(OpSt.top());
                    OpSt.pop();
                }
            }

            OpSt.push(PreStr);
        }
    }

    // Выталкиваем оставшиеся операторы из стека в результат
    while (!OpSt.empty())
    {
        Ans.push(OpSt.top());
        OpSt.pop();
    }

    return Ans;
}

// Вычисляет выражение, записанное в обратной польской нотации.
// Возвращает результат вычисления как double.
double FromPolsk(queue<string> StAns)
{
    stack<double> Ans; // Стек операндов


    while(!StAns.empty())
    {
        string front = StAns.front();
        // Если токен — число, кладём его в стек
        if(IsNum(front[0]))
        {
            Ans.push(atof(front.c_str()));
            StAns.pop();
            continue;
        }

        // Число принимаемых аргументов
        int number = Arity[front];
        // Если токен — оператор, извлекаем нужное число операнда и применяем операцию
        vector<double> operands(number);

        for(int i = 0; i < number; i++)
        {
            operands[i] = Ans.top();
            Ans.pop();
        }

        if((front == "Cos")) Ans.push(cos(operands[0]));
        if((front == "Sin")) Ans.push(sin(operands[0]));
        if(front == "+") Ans.push(operands[0] + operands[1]);
        if(front == "-") Ans.push(operands[1] - operands[0]);
        if(front == "*") Ans.push(operands[0] * operands[1]);
        if(front == "/") Ans.push(operands[1] / operands[0]);
        if(front == "^") Ans.push(pow(operands[1], operands[0]));

        StAns.pop();
    }

    // Итоговый результат остаётся на вершине стека
    return Ans.top();
}

// Функция для вывод итоговой строки
string ShowPolsk(queue<string> Q)
{
    string line = "[";
    while(!Q.empty())
    {
        line += Q.front() + ",";
        Q.pop();
    }
    line = DeleteLast(line) +"]";
    return line;
}

// Удаляет все пробелы из строки
string DeleteSpase(string str)
{
    string Ans = "";

    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] != ' ') Ans += str[i];
    }

    return Ans;
}

// Добавляет все элементы очереди q2 в конец очереди q1
void QMerge(queue<string> *q1, queue<string> q2)
{
    while(!q2.empty())
    {
        q1->push(q2.front());
        q2.pop();
    }
}

// Возвращает строку без последнего символа
// Используется для удаления закрывающей ')' после извлечения содержимого скобок
string DeleteLast(string str)
{
    string S = "";

    

    for(int i = 0; i < str.length() - 1; i++)
    {
        S += str[i];
    }

    return S;
}

string HandleNegative(string str)
{
    if (str[0] == '-') str.insert(0, "0");

    for (int i = 1; i < str.length(); i++)
    {
        if ((str[i] == '-') && (str[i - 1] == '(')) str.insert(i, "0");
    }

    return str;
}

vector<string> parce(string line)
{
    line = DeleteSpase(line);
    vector<string> ans(2);
    if(line.find("Show") != string::npos)
    {
        ans[0] = "Show";
        ans[1] = line.substr(ans[0].length() + 1, line.length() - ans[0].length() - 2);
    }
    if(line.find("Calculate") != string::npos)
    {
        ans[0] = "Calculate";
        ans[1] = line.substr(ans[0].length() + 1, line.length() - ans[0].length() - 2);
    }

    return ans;
}