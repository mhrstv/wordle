#include "../headers/admin.h"
#include "../headers/fileHandler.h"
#include "../headers/ANSI_color_codes.h"

#include <iostream>

size_t strLen(const char* str)
{
    int len = 0;
    if(!str) return 0;
    while(str[len] != '\0')
    {
        len++;
    } 
    return len;
}

void adminMenu()
{
    std::cout << RED << "__          __           _ _\n"
              << MAG << "\\ \\        / /          | | |\n"
              << CYN <<  " \\ \\  /\\  / /__  _ __ __| | | ___\n"
              << BLU << "  \\ \\/  \\/ / _ \\| '__/ _` | |/ _ \\\n"
              << GRN << "   \\  /\\  / (_) | | | (_| | |  __/\n"
              << YEL << "    \\/  \\/ \\___/|_|  \\__,_|_|\\___|\n"
              << BHWHT << "_____________________________________\n";
    std::cout << BHWHT << "============= Admin Menu ============" << std::endl;
    std::cout << BHWHT << "1. Add a word" << std::endl;
    std::cout << BHWHT << "2. Remove a word" << std::endl;
    std::cout << BHWHT << "3. View leaderboard" << std::endl;
    std::cout << BHWHT << "4. Exit" << std::endl;
}

bool addWord(const char* fileName)
{
    std::cout << "Enter word to add to words list: ";
    char word[MAX_WORD_LENGTH + 1];
    std::cin.getline(word, MAX_WORD_LENGTH + 1);
    if(strLen(word) != MAX_WORD_LENGTH)
    {
        std::cout << "Error: Word must be exactly " << MAX_WORD_LENGTH << " letters long." << std::endl;
        return false;
    }
    return containsLine(fileName, word) && appendLine(fileName, word);
}

bool removeWord(const char* fileName)
{
    std::cout << "Enter word to remove from words list: ";
    char word[MAX_WORD_LENGTH + 1];
    std::cin.getline(word, MAX_WORD_LENGTH + 1);
    if(strLen(word) != MAX_WORD_LENGTH)
    {
        std::cout << "Error: Word must be exactly " << MAX_WORD_LENGTH << " letters long." << std::endl;
        return false;
    }
    return containsLine(fileName, word) && removeLine(fileName, word);
}