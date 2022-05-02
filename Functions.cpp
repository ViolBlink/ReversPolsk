#include "Functions.h"


int IsNum(char ch)
{
    if((ch >= '0') && (ch <= '9')) return 1;

    return 0;
}

int IsOp(std::string str)
{
    if(((str == "+") || (str == "-") || (str == "*")
            || (str == "/") || (str == "^"))) return 1;

    return 0;
}

std::queue<std::string> ToPolsk(std::string str)
{
    std::queue<std::string> Ans;
    std::stack<std::string> OpSt;
    bool OpFlag = 0;
    bool BraFlag = 0;
    std::string Str1 = "";

    str = DeleteSpase(str);

    for (int i = 0; i < str.length(); i++)
    {
        if(str[i] == '(')
        {
            std::stack<char> st;
            st.push(str[i]);
            std::string NewStr = "";

            i++;

            while((!st.empty()) && (i < str.length()))
            {
                NewStr += str[i];

                if(str[i] == '(') st.push(str[i]);
                if(str[i] == ')') st.pop();
                i++;
            }
            NewStr = DeleteLast(NewStr);

            QMerge(&Ans, ToPolsk(NewStr));
        }

        if (IsNum(str[i]))  //Вычленяет число из строки и загоняет его в стэк ответа
        {
            Str1 = str[i];
            i++;

            while ((i < str.length()) && ((IsNum(str[i])) || (str[i] == '.')))
            {
                Str1 += str[i];
                i++;
            }

            Ans.push(Str1);
        }

        if (OpFlag)
        {
            Ans.push(OpSt.top());
            OpSt.pop();

            OpFlag = 0;
        }

        if ((i < str.length()) && ((str[i] != '+') || (str[i] != '-') || (str[i] != '*')
            || (str[i] != '/') || (str[i] != '^')))
        {
            std::string PreStr = "";
            PreStr += str[i];
            OpSt.push(PreStr);
        }

        if ((str[i] == '*') || (str[i] == '/') || (str[i] == '^') && !OpFlag) OpFlag = 1;
    }

    while (!OpSt.empty())
    {
        Ans.push(OpSt.top());
        OpSt.pop();
    }

    return Ans;
}

double FromPolsk(std::queue<std::string> StAns)
{
    std::stack<double> Ans;

    while(!StAns.empty())
    {
        if(!IsOp(StAns.front()))
        {
            Ans.push(atof(StAns.front().c_str()));
            StAns.pop();
            continue;
        }

        double x1;
        double x2; 

        x2 = Ans.top();
        Ans.pop();

        x1 = Ans.top();
        Ans.pop();

        if(StAns.front() == "+") Ans.push(x1 + x2);
        if(StAns.front() == "-") Ans.push(x1 - x2);
        if(StAns.front() == "*") Ans.push(x1 * x2);
        if(StAns.front() == "/") Ans.push(x1 / x2);
        if(StAns.front() == "^") Ans.push(pow(x1, x2));
        
        StAns.pop();
    }

    return Ans.top();
}

std::string DeleteSpase(std::string str)
{
    std::string Ans = "";

    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] != ' ') Ans += str[i];
    }

    return Ans;
}

void QMerge(std::queue<std::string> *q1, std::queue<std::string> q2)
{
    while(!q2.empty())
    {
        q1->push(q2.front());
        q2.pop();
    }
}

std::string DeleteLast(std::string str)
{
    std::string S = "";

    for(int i = 0; i < str.length() - 1; i++)
    {
        S += str[i];
    }

    return S;
}