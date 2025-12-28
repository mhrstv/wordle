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
#include "headers/user.h"

#include <iostream>
#include <limits>

int main()
{
    char currentUsername[MAX_BUFFER_SIZE];
    printMenu();
    int userChoice = readUserInt(PROMPT_MENU_INPUT, MENU_MIN, MENU_MAX);
    if(userChoice == 1)
    {
        int loginResult = loginIntoAccount(currentUsername);
        if(loginResult == 1)
        {
            startGame(MAX_ATTEMPTS, currentUsername);
        }
        else if(loginResult == -1)  
        {
            adminMenu();
        }
    }
    else if(userChoice == 2)
    {
        if(registerAccount(currentUsername))
        {
            startGame(MAX_ATTEMPTS, currentUsername);
        }
    }
    return 0;
}   