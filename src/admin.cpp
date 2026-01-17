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
* This file contains the implementations for all admin related functions such as viewing the leaderboard and adding/removing words
*
*/

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
    while (true)
    {
        int choice = readUserInt(PROMPT_MENU_INPUT, MENU_MIN, ADMIN_MENU_MAX);
        switch (choice)
        {
            case 1:
                if (addWord(WORDS_FILE))
                {   
                    std::cout << GRN << "Word added successfully!" << CRESET << std::endl;
                }
                else
                {
                    std::cout << RED << "Failed to add word." << CRESET << std::endl;
                }
                break;
            case 2:
                if (removeWord(WORDS_FILE))
                {
                    std::cout << GRN << "Word removed successfully!" << CRESET << std::endl;
                }
                else
                {
                    std::cout << RED << "Failed to remove word." << CRESET << std::endl;
                }
                break;
            case 3:
                viewLeaderboard(LEADERBOARD_FILE);
                break;
            case 4:
                return;
        }
    }
}

// Adds a word to the words file
bool addWord(const char* fileName)
{
    std::cout << "Enter word to add to words list: ";
    char word[MAX_WORD_LENGTH + 1];
    std::cin.getline(word, MAX_WORD_LENGTH + 1);
    for (int i = 0; i < strLen(word); i++)
    {
        if (!isLetter(word[i]))
        {
            std::cout << RED << "Error: Word must contain only latin letters." << CRESET << std::endl;
            return false;
        }
    }
    if (strLen(word) != MAX_WORD_LENGTH)
    {
        std::cout << "Error: Word must be exactly " << MAX_WORD_LENGTH << " letters long." << std::endl;
        return false;
    }
    return !containsLine(fileName, word) && appendLine(fileName, word);
}

// Removes a word from the words file
bool removeWord(const char* fileName)
{
    std::cout << "Enter word to remove from words list: ";
    char word[MAX_WORD_LENGTH + 1];
    std::cin.getline(word, MAX_WORD_LENGTH + 1);
    if (strLen(word) != MAX_WORD_LENGTH)
    {
        std::cout << "Error: Word must be exactly " << MAX_WORD_LENGTH << " letters long." << std::endl;
        return false;
    }
    return containsLine(fileName, word) && removeLine(fileName, word);
}

void printSortMenu()
{
    std::cout << BHWHT << "Select sorting method:\n";
    std::cout << "1. By Games Played (Descending)\n";
    std::cout << "2. By Win Rate (Descending)\n" << CRESET;
}

// This function returns true if 'firstStat' should be swapped with 'secondStat' based on the chosen sorting criteria
bool shouldSwap(const UserStat& firstStat, const UserStat& secondStat, int choice)
{
    if (choice == 1)
    {
        return firstStat.played < secondStat.played;
    }
    return firstStat.winRate < secondStat.winRate;
}

void sortLeaderboard(UserStat* stats, int count, int choice)
{
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = 0; j < count - i - 1; j++)
        {
            if (shouldSwap(stats[j], stats[j + 1], choice))
            {
                UserStat temp = stats[j];
                stats[j] = stats[j + 1];
                stats[j + 1] = temp;
            }
        }
    }
}

void printLeaderboardRow(const UserStat& stat)
{
    std::cout << YEL << stat.username << CRESET;
    int len = 0;
    while (stat.username[len])
    {
        len++;
    }

    if (len < 8)
    {
        std::cout << "\t\t";
    }
    else
    {
        std::cout << "\t";
    }

    std::cout << stat.played << "\t" << stat.wins << "\t";
    int percent = (int)(stat.winRate * 100);
    std::cout << percent << "%" << std::endl;
}

void printLeaderboard(UserStat* stats, int count)
{
    std::cout << "\n" << BHWHT << "====== LEADERBOARD ======" << CRESET << std::endl;
    std::cout << UCYN << "Username" << "\t\t" << "Played" << "\t" << "Wins" << "\t" << "Win Rate" << CRESET << std::endl;

    for (int i = 0; i < count; i++)
    {
        printLeaderboardRow(stats[i]);
    }
    std::cout << BHWHT << "=========================\n" << CRESET << std::endl;
}

void viewLeaderboard(const char* fileName)
{
    UserStat stats[MAX_STATS];
    int count = loadLeaderboardData(fileName, stats, MAX_STATS);

    if (count == 0)
    {
        std::cout << RED << "No leaderboard data found/file is empty." << CRESET << std::endl;
        return;
    }

    printSortMenu();
    int choice = readUserInt("Enter choice: ", 1, 2);

    sortLeaderboard(stats, count, choice);
    printLeaderboard(stats, count);

    std::cout << "Press Enter to return to the admin menu...";
    std::cin.get();
}