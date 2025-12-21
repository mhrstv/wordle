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
* This file declares all the functions related to handling files such as opening and reading them + all additional methods
* for the leaderboard and account statistics
*
*/

#pragma once
#include "constants.h"

struct PlayerStatistics{
    char playerUsername[32];
    int playedGames;
    int wins;
};

bool strEquals(const char* str1, const char* str2);

bool usernameExists(const char* fileName, const char* username);
bool findAccount(const char* fileName, const char* username, const char* password, char* type, int typeSize);

bool appendLine(const char* fileName, const char* line);
int loadLines(const char* fileName, int maxLines);
bool containsLine(const char* fileName, const char* line);

bool saveLeaderboard(const char* fileName, PlayerStatistics statistics[], int count);
bool loadLeaderboard(const char* fileName, PlayerStatistics statistics[], int max);