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
* This file contains initializations for methods which handle files (reading, writing) + methods such as
* checking for string prefixes and checking whether a file contains a specific string
*
*/

#include "../headers/fileHandler.h"
#include "../headers/input.h"
#include "../headers/ANSI_color_codes.h"

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>

bool startsWith(const char* line, const char* str)
{
    while (*str != '\0')
    {
        if (*line == '\0' || *line != *str)
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
    if (!file.is_open())
    {
        return false;
    }

    char buffer[MAX_BUFFER_SIZE];
    while (file.getline(buffer, MAX_BUFFER_SIZE))
    {
        if (startsWith(buffer, username))
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
    if (!file.is_open())
    {
        std::cout << RED << "Error: Could not open source file." << std::endl;
        return -1;
    }

    char buffer[MAX_BUFFER_SIZE];
    while (true)
    {
        file.getline(buffer, MAX_BUFFER_SIZE);
        if (file.eof())
        {
            break;
        }
    }

    file.close();
    return 0;
}

bool appendLine(const char* fileName, const char* line)
{
    std::ofstream file(fileName, std::ios::out | std::ios::app);

    if (!file.is_open())
    {
        std::cout << RED << "Error: Could not open " << fileName << std::endl;
        return false;
    }

    file << line << std::endl;

    file.close();
    return true;
}

void transferContent(std::ifstream& src, std::ofstream& dest, const char* excludeLine)
{
    char buffer[MAX_BUFFER_SIZE];
    while (src.getline(buffer, MAX_BUFFER_SIZE))
    {
        if (!strEquals(buffer, excludeLine))
        {
            dest << buffer << std::endl;
        }
    }
}

bool removeLine(const char* fileName, const char* line)
{
    std::ifstream inputFile(fileName);
    if (!inputFile.is_open())
    {
        std::cout << RED << "Error: Could not open source file." << std::endl;
        return false;
    }

    std::ofstream tempFile("temp.txt");
    if (!tempFile.is_open())
    {
        std::cout << RED << "Error: Could not create temporary file." << std::endl;
        inputFile.close();
        return false;
    }

    transferContent(inputFile, tempFile, line);

    inputFile.close();
    tempFile.close();

    if (std::remove(fileName) != 0)
    {
        return false;
    }

    return std::rename("temp.txt", fileName) == 0;
}

bool containsLine(const char* fileName, const char* line)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        std::cout << RED << "Error: Could not open source file." << std::endl;
        return false;
    }

    char buffer[MAX_BUFFER_SIZE];
    while (true)
    {
        file.getline(buffer, MAX_BUFFER_SIZE);
        if (strEquals(buffer, line))
        {
            return true;
        }

        if (file.eof())
        {
            return false;
        }
    }

    file.close();
    return false;
}

bool checkCredentials(const char* line, const char* user, const char* pass, char* type, int typeSize)
{
    int i = 0;
    int j = 0;

    while (line[i] != ':' && line[i] != '\0' && user[j] == line[i])
    {
        i++;
        j++;
    }

    if (user[j] != '\0' || line[i] != ':')
    {
        return false;
    }
    i++;

    j = 0;
    while (line[i] != ':' && line[i] != '\0' && pass[j] == line[i])
    {
        i++;
        j++;
    }

    if (pass[j] != '\0' || line[i] != ':')
    {
        return false;
    }
    i++;

    if (type && typeSize > 0)
    {
        j = 0;
        while (line[i] != '\0' && j < typeSize - 1)
        {
            type[j++] = line[i++];
        }
        type[j] = '\0';
    }

    return true;
}

bool findAccount(const char* fileName, const char* username, const char* password, char* type, int typeSize)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        return false;
    }

    char buffer[MAX_BUFFER_SIZE];
    while (file.getline(buffer, MAX_BUFFER_SIZE))
    {
        if (checkCredentials(buffer, username, password, type, typeSize))
        {
            return true;
        }
    }

    return false;
}

int countFileLines(std::ifstream& file)
{
    char buffer[MAX_BUFFER_SIZE];
    int count = 0;
    while (file.getline(buffer, MAX_BUFFER_SIZE))
    {
        count++;
    }
    return count;
}

char* getRandomWord(const char* fileName)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        return nullptr;
    }

    int count = countFileLines(file);
    if (count == 0)
    {
        return nullptr;
    }

    file.clear();
    file.seekg(0);
    std::srand(std::time(0));

    int target = std::rand() % count;
    char buffer[MAX_BUFFER_SIZE];

    for (int i = 0; i <= target; i++)
    {
        file.getline(buffer, MAX_BUFFER_SIZE);
    }

    int len = 0;
    while (buffer[len])
    {
        len++;
    }

    char* word = new char[len + 1];
    for (int i = 0; i <= len; i++)
    {
        word[i] = buffer[i];
    }

    return word;
}

bool isUserMatch(const char* line, const char* username, int& colonIndex)
{
    int i = 0;
    while (username[i] != '\0')
    {
        if (line[i] != username[i])
        {
            return false;
        }
        i++;
    }

    if (line[i] == ':')
    {
        colonIndex = i;
        return true;
    }
    return false;
}

void updateStats(std::ofstream& out, const char* username, const char* dataStart, bool won)
{
    int i = 0;
    int played = 0;

    while (dataStart[i] >= '0' && dataStart[i] <= '9')
    {
        played = played * 10 + (dataStart[i] - '0');
        i++;
    }

    if (dataStart[i] == ':')
    {
        i++;
    }

    int wins = 0;
    while (dataStart[i] >= '0' && dataStart[i] <= '9')
    {
        wins = wins * 10 + (dataStart[i] - '0');
        i++;
    }

    out << username << ":" << (played + 1) << ":" << (wins + (won ? 1 : 0)) << "\n";
}

void copyFile(const char* srcFile, const char* destFile)
{
    std::ifstream src(srcFile);
    std::ofstream dst(destFile);
    char buffer[MAX_BUFFER_SIZE];

    if (src.is_open() && dst.is_open())
    {
        while (src.getline(buffer, MAX_BUFFER_SIZE))
        {
            dst << buffer << "\n";
        }
    }
}

void processLeaderboardUpdate(std::ifstream& infile, std::ofstream& outfile, const char* username, bool won, bool& found)
{
    char line[MAX_BUFFER_SIZE];
    while (infile.getline(line, MAX_BUFFER_SIZE))
    {
        int colonIndex = 0;
        if (isUserMatch(line, username, colonIndex))
        {
            updateStats(outfile, username, &line[colonIndex + 1], won);
            found = true;
        }
        else
        {
            outfile << line << "\n";
        }
    }
}

bool updateLeaderboard(const char* fileName, const char* username, bool won)
{
    std::ifstream infile(fileName);
    std::ofstream outfile("temp.txt");

    if (!outfile.is_open())
    {
        return false;
    }

    bool found = false;
    if (infile.is_open())
    {
        processLeaderboardUpdate(infile, outfile, username, won, found);
        infile.close();
    }

    if (!found)
    {
        outfile << username << ":1:" << (won ? 1 : 0) << "\n";
    }

    outfile.close();
    copyFile("temp.txt", fileName);
    std::remove("temp.txt");

    return true;
}

int parseStatInt(const char* line, int& i)
{
    int value = 0;
    while (line[i] >= '0' && line[i] <= '9')
    {
        value = value * 10 + (line[i] - '0');
        i++;
    }
    return value;
}

void parseStatLine(const char* line, UserStat& stat)
{
    int i = 0;
    int nameIndex = 0;

    while (line[i] != ':' && line[i] != '\0' && nameIndex < 49)
    {
        stat.username[nameIndex++] = line[i++];
    }
    stat.username[nameIndex] = '\0';

    if (line[i] == ':')
    {
        i++;
    }

    stat.played = parseStatInt(line, i);

    if (line[i] == ':')
    {
        i++;
    }

    stat.wins = parseStatInt(line, i);

    if (stat.played > 0)
    {
        stat.winRate = (double)stat.wins / stat.played;
    }
    else
    {
        stat.winRate = 0.0;
    }
}

int loadLeaderboardData(const char* fileName, UserStat* stats, int maxStats)
{
    std::ifstream file(fileName);
    if (!file.is_open())
    {
        return 0;
    }

    char line[MAX_BUFFER_SIZE];
    int count = 0;

    while (file.getline(line, MAX_BUFFER_SIZE) && count < maxStats)
    {
        parseStatLine(line, stats[count]);
        count++;
    }

    file.close();
    return count;
}