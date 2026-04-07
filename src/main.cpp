#include "../include/Functions.h"

int main()
{
    std::string str;
    std::vector<std::string> cmd;

    std::cout << "Write your expression, to exit, write esc\n";
    std::cout << "Enter the expression here ----> ";
    std::getline(std::cin, str); // Читаем первое выражение

    // Основной цикл: принимаем выражения до тех пор, пока пользователь не введёт "esc"
    while (str != "esc")
    {
        try
        {
            cmd = parce(str);
            // Переводим выражение в ОПН, затем вычисляем и выводим результат
            if(cmd[0] == "Calculate") std::cout << FromPolsk(ToPolsk(cmd[1])) << "\n";
            if(cmd[0] == "Show") std::cout << ShowPolsk(ToPolsk(cmd[1])) << "\n";
            if(cmd[0] == "Set") SetVar({cmd[1], cmd[2]});
        }
        catch(const char *e)
        {
            std::cout << "Error: " << e << "\n";
        }

        std::cout << "Enter the expression here ----> ";
        std::getline(std::cin, str); // Читаем следующее выражение
    }
}
