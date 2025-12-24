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
* This file contains the initializations for account related functions such as registering an account or logging into one
*
*/

#include "../headers/account.h"
#include "../headers/input.h"
#include "../headers/std.hpp"

#include <iostream>

bool registerAccount() {
    char* username = readUserLine("Type desired username: ");
    char* password = readUserLine("Type desired password: ");
    char* user = new char[MAX_BUFFER_SIZE * 2]; 
    
    int i = 0;
    while(username[i]) { user[i] = username[i]; i++; }
    user[i++] = ':'; 

    int j = 0;
    while(password[j]) { user[i] = password[j]; i++; j++; }
    user[i++] = ':';
    
    const char* defaultType = "user";
    int t = 0;
    while(defaultType[t]) { user[i] = defaultType[t]; i++; t++; }
    user[i] = '\0'; 

    if(!usernameExists(USERS_FILE, username))
    {
        bool registeredAccount = appendLine(USERS_FILE, user);
        
        if(registeredAccount) 
        {
            std::cout << "Account registered successfully!" << std::endl;
        }
        else std::cout << "Error: Failed to register account." << std::endl;

        delete[] username;
        delete[] password;
        delete[] user;
        return registeredAccount;
    }
    else
    {
        std::cout << "Error: Account with that username already exists." << std::endl;
        delete[] username;
        delete[] password;
        delete[] user;
        return false;
    }
}

int loginIntoAccount()
{
    char* username = readUserLine("Enter your username: ");
    char* password = readUserLine("Enter your password: ");

    char type[32] = {0};
    bool accountFound = findAccount(USERS_FILE, username, password, type, sizeof(type));
    if(accountFound)
    {
        std::cout << "Login successful!" << std::endl;
        if(strEquals(type, "admin")) return -1;
        else return 1;
    }
    else
    {
        std::cout << "Error: Failed to login into account." << std::endl;
        return 0;
    }

    delete[] username;
    delete[] password;
}