#include "../headers/admin.h"
#include "../headers/fileHandler.h"
#include "../headers/ANSI_color_codes.h"
#include "../headers/input.h"

#include <iostream>

void printLogo()
{
    std::cout << RED << "__          __           _ _\n"
              << MAG << "\\ \\        / /          | | |\n"
              << CYN <<  " \\ \\  /\\  / /__  _ __ __| | | ___\n"
              << BLU << "  \\ \\/  \\/ / _ \\| '__/ _` | |/ _ \\\n"
              << GRN << "   \\  /\\  / (_) | | | (_| | |  __/\n"
              << YEL << "    \\/  \\/ \\___/|_|  \\__,_|_|\\___|\n"
              << BHWHT << "_____________________________________\n";
}
void adminMenu()
{
    printLogo();
    std::cout << BHWHT << "============= Admin Menu ============" << std::endl;
    std::cout << BHWHT << "1. Add a word" << std::endl;
    std::cout << BHWHT << "2. Remove a word" << std::endl;
    std::cout << BHWHT << "3. View leaderboard" << std::endl;
    std::cout << BHWHT << "4. Exit" << std::endl;
    while(true)
    {
        int choice = readUserInt(PROMPT_MENU_INPUT, MENU_MIN, ADMIN_MENU_MAX);
        switch(choice)
        {
            case 1:
                if(addWord(WORDS_FILE))
                {   
                    std::cout << GRN << "Word added successfully!" << CRESET << std::endl;
                }
                else
                {
                    std::cout << RED << "Failed to add word." << CRESET << std::endl;
                }
                break;
            case 2:
                if(removeWord(WORDS_FILE))
                {
                    std::cout << GRN << "Word removed successfully!" << CRESET << std::endl;
                }
                else
                {
                    std::cout << RED << "Failed to remove word." << CRESET << std::endl;
                }
                break;
            case 3:
            
                break;
            case 4:
                return;
        }
    }
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
    return !containsLine(fileName, word) && appendLine(fileName, word);
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