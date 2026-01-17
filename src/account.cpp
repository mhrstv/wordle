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
#include "../headers/ANSI_color_codes.h"

#include <iostream>

// Appends the source to the destination buffer at the selected index
void appendToBuffer(char* buffer, int& index, const char* src)
{
    int i = 0;
    while (src[i]) {
        buffer[index] = src[i];
        index++;
        i++;
    }
}

// Formats account data into one line
char* formatData(const char* username, const char* password)
{
    char* userLine = new char[MAX_BUFFER_SIZE * 2];
    int index = 0;

    appendToBuffer(userLine, index, username);
    userLine[index] = ':';
    index++;

    appendToBuffer(userLine, index, password);
    userLine[index] = ':';
    index++;

    appendToBuffer(userLine, index, "user");
    userLine[index] = '\0';
    return userLine;
}

bool attemptToRegister(const char* username, const char* userLine, char* outputUsername)
{
    if (usernameExists(USERS_FILE, username)) {
        std::cout << RED << "Error: Account with that username already exists." << std::endl;
        return false;
    }

    if (appendLine(USERS_FILE, userLine)) {
        std::cout << "Account registered successfully!" << std::endl;
        strCpy(outputUsername, username);
        return true;
    }

    std::cout << RED << "Error: Failed to register account." << std::endl;
    return false;
}

bool registerAccount(char* outputUsername)
{
    char* username = readUserLine("Type desired username: ");
    char* password = readUserLine("Type desired password: ");

    if (!username || !password) {
        return false;
    }

    char* userLine = formatData(username, password);
    bool result = attemptToRegister(username, userLine, outputUsername);

    delete[] username;
    delete[] password;
    delete[] userLine;

    return result;
}

int loginIntoAccount(char* outputUsername)
{
    char* username = readUserLine("Enter your username: ");
    char* password = readUserLine("Enter your password: ");

    char type[32] = {0};
    bool accountFound = findAccount(USERS_FILE, username, password, type, sizeof(type));
    if (accountFound) {
        std::cout << "Login successful!" << std::endl;
        strCpy(outputUsername, username); 

        delete[] username;
        delete[] password;
        if (strEquals(type, "admin")) { 
            return -1;
        }
        else {
            return 1;
        } 
    }
    else {
        std::cout << RED << "Error: Failed to login into account." << std::endl;
        std::cin.get();
        delete[] username;
        delete[] password;
        return 0;
    }
}