/**
*
* Solution to course project #09
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2025/2026
*
* @author Martin Hritsov
* @idnumber 4MI0600616
* @compiler GCC
*
* File which initializes all the necessary menu methods such as printing the menu to the console's output
*/


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
    std::cout << BHWHT << "1." << " Login as an existing user" << std::endl;
    std::cout << BHWHT << "2." << " Register a new user" << std::endl;
    std::cout << BHWHT << "3." << " Exit" << std::endl;
    std::cout << CRESET;
}