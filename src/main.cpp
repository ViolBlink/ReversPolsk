#include "../include/Functions.h"

int main()
{
    std::string str;

    std::cout << "Write your expression, to exit, write esc\n";
    std::cout << "Enter the expression here ----> ";
    std::getline(std::cin, str); // Читаем первое выражение

    // Основной цикл: принимаем выражения до тех пор, пока пользователь не введёт "esc"
    while (str != "esc")
    {
        // Переводим выражение в ОПН, затем вычисляем и выводим результат
        std::cout << FromPolsk(ToPolsk(str)) << "\n";

        std::cout << "Enter the expression here ----> ";
        std::getline(std::cin, str); // Читаем следующее выражение
    }
}
