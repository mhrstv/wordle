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
* This file contains initializations for methods which handle files (reading, writing) + standard library methods such as
* comparing strings, checking for string prefixes and checking whether a file contains a specific string
*
*/

#include "../headers/fileHandler.h"
#include "../headers/input.h"

#include <fstream>
#include <iostream>

bool strEquals(const char* str1, const char* str2)
{
    while(*str1 == *str2)
    {
        if(*str1 == '\0') return true;
        str1++;
        str2++;
    }
    return false;
}

bool startsWith(const char* line, const char* str)
{
    while(*str != '\0')
    {
        if(*line == '\0' || *line != *str) 
        {
            return false;
        }
        
        line++;
        str++;
    }

    char next = *line;
    return (next == ' ' || next == ':' || next == ',' || next == '\t' || next == '\0' || next == '\n' || next == '\r');
}

bool usernameExists(const char* fileName, const char* username)
{   
    std::ifstream file(fileName);
    if(!file.is_open())
    {
        return false; 
    }

    char buffer[MAX_BUFFER_SIZE];
    while(file.getline(buffer, MAX_BUFFER_SIZE))
    {
        if(startsWith(buffer, username)) 
        {
            file.close();
            return true; 
        }
    }
    
    file.close(); 
    return false; 
}

int loadLines(const char* fileName, int maxLines)
{
    std::ifstream file(fileName);
    char* line;

    if(!file.is_open())
    {
        std::cout << "Error: Could not open source file." << std::endl;
        return -1;
    }

    char buffer[MAX_BUFFER_SIZE];
    while(true)
    {
        file.getline(buffer, MAX_BUFFER_SIZE);   
        if(file.eof()) break;  
    }

    file.close(); 
    return 0;
}

bool appendLine(const char* fileName, const char* line) {
    std::ofstream file(fileName, std::ios::out | std::ios::app);

    if(!file.is_open()) {
        std::cout << "Error: Could not open " << fileName << std::endl;
        return false;
    }

    file << line << std::endl;
    
    file.close();
    return true;
}

bool removeLine(const char* fileName, const char* line)
{
    std::ifstream inputFile(fileName);
    if(!inputFile.is_open())
    {
        std::cout << "Error: Could not open source file." << std::endl;
        return false;
    }

    std::ofstream tempFile("temp.txt");
    if(!tempFile.is_open())
    {
        std::cout << "Error: Could not create temporary file." << std::endl;
        inputFile.close();
        return false;
    }

    char buffer[MAX_BUFFER_SIZE];
    while(inputFile.getline(buffer, MAX_BUFFER_SIZE))
    {
        if(!strEquals(buffer, line))
        {
            tempFile << buffer << std::endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if(std::remove(fileName) != 0)
    {
        std::cout << "Error: Could not delete original file." << std::endl;
        return false;
    }

    if(std::rename("temp.txt", fileName) != 0)
    {
        std::cout << "Error: Could not rename temporary file." << std::endl;
        return false;
    }

    return true;
}

bool containsLine(const char* fileName, const char* line)
{
    std::ifstream file(fileName);
    if(!file.is_open())
    {
        std::cout << "Error: Could not open source file." << std::endl;
        return false;
    }

    char buffer[MAX_BUFFER_SIZE];
    int current = 0;
    while(true)
    {
        file.getline(buffer, MAX_BUFFER_SIZE);  
        if(strEquals(buffer, line)) return true;
        if(file.eof()) return false;  
    }

    file.close(); 
    return false;
}

bool findAccount(const char* fileName, const char* username, const char* password, char* type, int typeSize)
{
    std::ifstream file(fileName);
    if (!file.is_open()) return false;

    char buffer[MAX_BUFFER_SIZE];
    while (file.getline(buffer, MAX_BUFFER_SIZE))
    {
        int i = 0, j = 0;
        while (buffer[i] != ':' && buffer[i] != '\0' && username[j] == buffer[i])
        { 
            i++; 
            j++; 
        }

        if (username[j] != '\0' || buffer[i] != ':') continue; 
        i++; 

        j = 0; 
        while (buffer[i] != ':' && buffer[i] != '\0' && password[j] == buffer[i]) 
        { 
            i++; 
            j++; 
        }

        if (password[j] != '\0' || buffer[i] != ':') continue;
        i++; 

        if (type && typeSize > 0)
        {
            j = 0;
            while (buffer[i] != '\0' && j < typeSize - 1)
            {
                type[j++] = buffer[i++];
            }
            type[j] = '\0';
        }
        return true;
    }
    return false;
}
