#pragma once
#include "constants.h"

struct PlayerStatistics{
    char playerUsername[32];
    int playedGames;
    int wins;
};

bool usernameExists(const char* fileName, const char* username);
bool appendLine(const char* fileName, const char* line);
int loadLines(const char* fileName, int maxLines);
bool containsLine(const char* fileName, const char* line);

bool saveLeaderboard(const char* fileName, PlayerStatistics statistics[], int count);
bool loadLeaderboard(const char* fileName, PlayerStatistics statistics[], int max);