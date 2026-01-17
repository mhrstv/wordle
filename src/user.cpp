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
* This file contains all the implementations for user related functions such as starting the game
* plus additiional helper methods for the game loop, handling turns and printing results
*
*/

#include "../headers/user.h"
#include "../headers/input.h"
#include "../headers/fileHandler.h"
#include "../headers/ANSI_color_codes.h"
#include "../headers/menu.h"

#include <iostream>
#include <cstdlib>

bool compareGuessLength(const char* guess, size_t requiredLength)
{
    if(!guess) return false;
    if (strLen(guess) != requiredLength) {
        std::cout << RED << "Your guess must be " << requiredLength << " letters long." << std::endl;
        std::cout << CRESET;
        return false;
    }
    return true;
}

void printGuessResult(const char* guess, const char* target, size_t length)
{
    if(!guess || !target) return;
    std::cout << CURSOR_UP << ERASE_LINE << "\r"; 
    for (int i = 0; i < length; i++) {
        char current = guess[i];
        if (current == target[i]) {
            std::cout << GRN << current << CRESET;
        }
        else {
            bool found = false;
            for (int j = 0; j < length; j++) {
                if (target[j] == current) {
                    found = true;
                    break;
                }
            }

            if (found) std::cout << YEL << current << CRESET;
            else std::cout << WHT << current << CRESET;
        }
    }
    std::cout << std::endl;
}

// Handles a single player turn
bool playerTurn(const char* word, size_t len, bool& guessed)
{
    if(!word) return false;
    char* guess = readUserLine("");
    if (!guess) {
        std::cout << RED << "Error: Failed to read input." << CRESET << std::endl;
        return false;
    }
    if (!compareGuessLength(guess, len)) {
        delete[] guess;
        return false;
    }
    for (int i = 0; i < strLen(guess); i++) {
        if (!isLetter(guess[i])) {
            std::cout << RED << "Error: Word must contain only latin letters." << CRESET << std::endl;
            delete[] guess;
            return false;
        }
    }

    if (strEquals(guess, word)) {
        guessed = true;
        printGuessResult(guess, word, len);
        std::cout << "Congratulations! You win!" << std::endl;
    }
    else {
        printGuessResult(guess, word, len);
    }

    delete[] guess;
    return true;
}

void runGameLoop(const char* word, int maxAttempts, bool& guessed)
{
    if(!word) return;
    size_t len = strLen(word);
    int currentAttempts = 0;

    std::cout << GRN << "Game started!" << CRESET << " You have " << BLU << maxAttempts << CRESET << " attempts left." << std::endl;

    while (currentAttempts < maxAttempts && !guessed) {
        if (playerTurn(word, len, guessed)) {
            currentAttempts++;
        }
    }
}

void endGame(const char* word, bool guessed, const char* username)
{
    if(!word || !username) return;
    if (!guessed) {
        std::cout << RED << "You lose. No more attempts left." << CRESET << std::endl;
        std::cout << "The correct word was: " << word << std::endl;
    }

    updateLeaderboard(LEADERBOARD_FILE, username, guessed);
    std::cin.get();
}

void startGame(int attempts, const char* username)
{
    if(!username) return;
    char* word = getRandomWord(WORDS_FILE);

    if (!word) {
        std::cout << RED << "Error retrieving word." << CRESET << std::endl;
        return;
    }

    bool guessed = false;
    runGameLoop(word, attempts, guessed);

    endGame(word, guessed, username);
    delete[] word;
}