#include "../include/Functions.h"

int main()
{
    std::string str;
    std::vector<std::string> cmd(2);

    std::cout << "Write your expression, to exit, write esc\n";
    std::cout << "Enter the expression here ----> ";
    std::getline(std::cin, str); // Читаем первое выражение

    // Основной цикл: принимаем выражения до тех пор, пока пользователь не введёт "esc"
    while (str != "esc")
    {
        cmd = parce(str);
        // Переводим выражение в ОПН, затем вычисляем и выводим результат
        if(cmd[0] == "Calculate") std::cout << FromPolsk(ToPolsk(cmd[1])) << "\n";
        if(cmd[0] == "Show") std::cout << ShowPolsk(ToPolsk(cmd[1])) << "\n";

        std::cout << "Enter the expression here ----> ";
        std::getline(std::cin, str); // Читаем следующее выражение
    }
}
