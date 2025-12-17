#include "../headers/menu.h"
#include "../headers/ANSI_color_codes.h"

#include <iostream>

void printMenu()
{
    std::cout << RED << "__          __           _ _\n"
              << MAG << "\\ \\        / /          | | |\n"
              << CYN <<  " \\ \\  /\\  / /__  _ __ __| | | ___\n"
              << BLU << "  \\ \\/  \\/ / _ \\| '__/ _` | |/ _ \\\n"
              << GRN << "   \\  /\\  / (_) | | | (_| | |  __/\n"
              << YEL << "    \\/  \\/ \\___/|_|  \\__,_|_|\\___|\n"
              << BHWHT << "_____________________________________\n\n";
    std::cout << BHWHT << "1." << WHT << " Login as an existing user" << std::endl;
    std::cout << BHWHT << "2." << WHT << " Register a new user" << std::endl;
    std::cout << BHWHT << "3." << WHT << " Exit" << std::endl;
    std::cout << CRESET;
}