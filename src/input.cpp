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
* File with initializaitons for helper methods for user input such as reading from the console
*
*/

#include "../headers/input.h"
#include "../headers/constants.h"

#include <iostream>
#include <limits>

// Reads an integer from the console input within the specified range
int readUserInt(const char* prompt, int MIN, int MAX) {
    if(!prompt) prompt = "";
    int input;
    while (true) {
        std::cout << prompt << "(" << MIN << "-" << MAX << "): ";
        if (std::cin >> input) {
            if (input >= MIN && input <= MAX) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return input;
            }
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

// Reads a string from the console input
char* readUserLine(const char* prompt) {
    if(!prompt) prompt = "";
    std::cout << prompt;
    char* line = new char[MAX_BUFFER_SIZE]; 
    std::cin.getline(line, MAX_BUFFER_SIZE);
    
    return line;
}