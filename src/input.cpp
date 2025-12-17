#include "../headers/input.h"

#include <iostream>
#include <limits>

int readUserInt(const char* prompt, int MIN, int MAX)
{
    int input;
    while(true)
    {
        std::cout << prompt << std::endl;
        std::cin >> input;
        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else if(input >= MIN && input <= MAX) break;
    }
    return input;
}