#include "Functions.h"

int main()
{
    std::string str;

    std::cout << "Write your expression, to exit, write esc\n";
    std::cout << "Write hear ----> ";
    std::getline(std::cin, str);

    while (str != "esc")
    {
        //Сам алгоритм будет тут
        std::cout << FromPolsk(ToPolsk(str)) << "\n";

        std::cout << "Write hear ----> ";   //Ввод нового выражения
        std::getline(std::cin, str);
    }
}