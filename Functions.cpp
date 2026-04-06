#include "Functions.h"


// Возвращает 1, если символ является цифрой ('0'–'9'), иначе 0
int IsNum(char ch)
{
    if((ch >= '0') && (ch <= '9')) return 1;

    return 0;
}

// Возвращает 1, если строка является одним из операторов: + - * / ^
int IsOp(std::string str)
{
    if(((str == "+") || (str == "-") || (str == "*")
            || (str == "/") || (str == "^"))) return 1;

    return 0;
}

// Переводит инфиксное выражение (например "3+4*2") в обратную польскую нотацию.
// Возвращает очередь токенов (чисел и операторов) в порядке ОПН.
std::queue<std::string> ToPolsk(std::string str)
{
    std::queue<std::string> Ans;   // Очередь результата (ОПН)
    std::stack<std::string> OpSt;  // Стек операторов
    bool OpFlag = 0;               // Флаг: нужно ли вытолкнуть оператор из стека
    bool BraFlag = 0;
    std::string Str1 = "";

    str = DeleteSpase(str); // Убираем пробелы из входной строки

    for (int i = 0; i < str.length(); i++)
    {
        // Обработка открывающей скобки: рекурсивно обрабатываем содержимое
        if(str[i] == '(')
        {
            std::stack<char> st; // Вспомогательный стек для отслеживания вложенных скобок
            st.push(str[i]);
            std::string NewStr = "";

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

        // Если на предыдущей итерации был выставлен флаг — выталкиваем оператор в результат
        if (OpFlag)
        {
            Ans.push(OpSt.top());
            OpSt.pop();

            OpFlag = 0;
        }

        // Помещаем текущий символ в стек операторов
        if ((i < str.length()) && (IsOp(str[i])))
        {
            std::string PreStr = "";
            PreStr += str[i];
            OpSt.push(PreStr);
        }

        // Для операторов высокого приоритета (* / ^) выставляем флаг выталкивания
        if ((str[i] == '*') || (str[i] == '/') || (str[i] == '^') && !OpFlag) OpFlag = 1;
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
double FromPolsk(std::queue<std::string> StAns)
{
    std::stack<double> Ans; // Стек операндов

    while(!StAns.empty())
    {
        // Если токен — число, кладём его в стек
        if(!IsOp(StAns.front()))
        {
            Ans.push(atof(StAns.front().c_str()));
            StAns.pop();
            continue;
        }

        // Если токен — оператор, извлекаем два операнда и применяем операцию
        double x1;
        double x2;

        x2 = Ans.top(); // Второй операнд (верхний)
        Ans.pop();

        x1 = Ans.top(); // Первый операнд
        Ans.pop();

        if(StAns.front() == "+") Ans.push(x1 + x2);
        if(StAns.front() == "-") Ans.push(x1 - x2);
        if(StAns.front() == "*") Ans.push(x1 * x2);
        if(StAns.front() == "/") Ans.push(x1 / x2);
        if(StAns.front() == "^") Ans.push(pow(x1, x2));

        StAns.pop();
    }

    // Итоговый результат остаётся на вершине стека
    return Ans.top();
}

// Удаляет все пробелы из строки
std::string DeleteSpase(std::string str)
{
    std::string Ans = "";

    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] != ' ') Ans += str[i];
    }

    return Ans;
}

// Добавляет все элементы очереди q2 в конец очереди q1
void QMerge(std::queue<std::string> *q1, std::queue<std::string> q2)
{
    while(!q2.empty())
    {
        q1->push(q2.front());
        q2.pop();
    }
}

// Возвращает строку без последнего символа
// Используется для удаления закрывающей ')' после извлечения содержимого скобок
std::string DeleteLast(std::string str)
{
    std::string S = "";

    for(int i = 0; i < str.length() - 1; i++)
    {
        S += str[i];
    }

    return S;
}
