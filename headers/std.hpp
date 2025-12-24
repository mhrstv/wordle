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
* This file contains standard library helper functions
*
*/

#include <iostream>

#pragma once
inline int strLen(const char* str)
{
    int len = 0;
    if(!str) return 0;
    while(str[len] != '\0')
    {
        len++;
    } 
    return len;
}

inline bool strEquals(const char* str1, const char* str2)
{
    while(*str1 == *str2)
    {
        if(*str1 == '\0') return true;
        str1++;
        str2++;
    }
    return false;
}