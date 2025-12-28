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
* This file contains the declarations for the admin related functions such as viewing the leaderboard and adding/removing words
*
*/

#pragma once
void adminMenu();
bool addWord(const char* fileName);
bool removeWord(const char* fileName);
void viewLeaderboard(const char* fileName);