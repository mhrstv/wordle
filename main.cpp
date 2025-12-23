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
* The main file, which the program runs from - includes all the header files and helper functions.
*/

#include "headers/menu.h"
#include "headers/input.h"
#include "headers/fileHandler.h"
#include "headers/account.h"
#include "headers/admin.h"

#include <iostream>
#include <limits>

int main()
{
    printMenu();
    int userChoice = readUserInt(PROMPT_MENU_INPUT, MENU_MIN, MENU_MAX);
    if(userChoice == 1)
    {
        int loginResult = loginIntoAccount();
        if(loginResult == 1)
        {

        }
        else if(loginResult == -1)
        {
            adminMenu();
        }
    }
    else if(userChoice == 2)
    {
        if(registerAccount())
        {

        }
    }

    return 0;
}   