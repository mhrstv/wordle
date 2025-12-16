#include "../headers/menu.h"

#include <iostream>

void printMenu()
{
    std::cout << "__          __           _ _\n"
              << "\\ \\        / /          | | |\n"
              << " \\ \\  /\\  / /__  _ __ __| | | ___\n"
              << "  \\ \\/  \\/ / _ \\| '__/ _` | |/ _ \\\n"
              << "   \\  /\\  / (_) | | | (_| | |  __/\n"
              << "    \\/  \\/ \\___/|_|  \\__,_|_|\\___|\n"
              << "_____________________________________\n\n";
    std::cout << "1. Login as an existing user" << std::endl;
    std::cout << "2. Register a new user" << std::endl;
    std::cout << "3. Exit" << std::endl;
}