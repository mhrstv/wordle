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

int readUserInt(const char* prompt, int MIN, int MAX) {
    int input;
    while(true) {
        std::cout << prompt;
        if (std::cin >> input) {
            if(input >= MIN && input <= MAX) {
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                return input;
            }
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

char* readUserLine(const char* prompt) {
    std::cout << prompt;
    char* line = new char[MAX_BUFFER_SIZE]; 
    
    std::cin.getline(line, MAX_BUFFER_SIZE);
    
    return line;
}