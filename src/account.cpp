#include "../headers/account.h"
#include "../headers/input.h"

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
    user[i] = '\0'; 

    if(!usernameExists(USERS_FILE, user))
    {
        if(appendLine(USERS_FILE, user)) {
            std::cout << "Account registered successfully!" << std::endl;
            return true;
        } 
        else 
        {
            std::cout << "Error: Failed to register account." << std::endl;
            return false;
        }
    }
    else{
        std::cout << "Error: Account with that username already exists." << std::endl;
        return false;
    }
    

    delete[] username;
    delete[] password;
    delete[] user;
}

bool loginIntoAccount()
{
    char* username = readUserLine("Enter your username: ");
    char* password = readUserLine("Enter your password: ");
    char* user = new char[MAX_BUFFER_SIZE * 2]; 
    
    int i = 0;
    while(username[i]) { user[i] = username[i]; i++; }
    user[i++] = ':'; 
    int j = 0;
    while(password[j]) { user[i] = password[j]; i++; j++; }
    user[i] = '\0'; 

    if(containsLine(USERS_FILE, user))
    {
        std::cout << "Login successful!" << std::endl;
        return true;
    }
    else
    {
        std::cout << "Error: Failed to login into account." << std::endl;
        return false;
    }

    delete[] username;
    delete[] password;
    delete[] user;    
}