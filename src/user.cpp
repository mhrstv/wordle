#include "../headers/user.h"
#include "../headers/input.h"
#include "../headers/fileHandler.h"
#include "../headers/ANSI_color_codes.h"
#include "../headers/menu.h"

#include <iostream>
#include <cstdlib>

bool compareGuessLength(const char* guess, size_t requiredLength)
{
    if(strLen(guess) != requiredLength)
    {
        std::cout << RED << "Your guess must be " << requiredLength << " letters long." << std::endl;
        std::cout << CRESET;
        return false;
    }
    return true;
}

void printGuessResult(const char* guess, const char* target, size_t length)
{
    std::cout << CURSOR_UP << ERASE_LINE << "\r"; 
    for(int i = 0; i < length; i++)
    {
        char current = guess[i];
        if(current == target[i])
        {
            std::cout << GRN << current << CRESET;
        }
        else
        {
            bool found = false;
            for(int j = 0; j < length; j++)
            {
                if(target[j] == current)
                {
                    found = true;
                    break;
                }
            }

            if(found) std::cout << YEL << current << CRESET;
            else std::cout << current;
        }
    }
    std::cout << std::endl;
}

void startGame(int attempts)
{
    const char* word = getRandomWord(WORDS_FILE);
    if(!word)
    {
        std::cout << RED << "Error retrieving word." << CRESET << std::endl;
        return;
    }

    size_t wordLength = strLen(word);
    int currentAttempts = 0;
    bool guessed = false;
    
    std::cout << "You have " << BLU << attempts << CRESET << " attempts left." << std::endl;

    while(currentAttempts < attempts && !guessed)
    {
        char* guess = readUserLine("");
        if(!compareGuessLength(guess, wordLength))
        {
            delete[] guess;
            continue; 
        }
        currentAttempts++;

        if(strEquals(guess, word))
        {
            guessed = true;
            printGuessResult(guess, word, wordLength);
            std::cout << "Congratulations! You win!" << std::endl;
        }
        else
        {
            printGuessResult(guess, word, wordLength);
        }
        delete[] guess;
    }
    if(!guessed)
    {
        std::cout << RED << "You lose. No more attempts left." << CRESET << std::endl;
        std::cout << "The correct word was: " << word << std::endl;
    }
}