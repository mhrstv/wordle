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
    if(!str) return 0;
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
    if(!str1 || !str2) return false;
    while(*str1 == *str2)
    {
        if(*str1 == '\0') return true;
        str1++;
        str2++;
    }
    return false;
}

inline char* subStr(const char* src, size_t start, size_t length) {
    if(src == nullptr) return nullptr;
    size_t src_len = strLen(src);
    
    if (start >= src_len) {
        char* empty = new char[1];
        empty[0] = '\0';
        return empty;
    }

    if (start + length > src_len) {
        length = src_len - start;
    }

    char* dest = new char[length + 1];

    for (size_t i = 0; i < length; ++i) {
        dest[i] = src[start + i];
    }
    
    dest[length] = '\0';
    return dest;
}

inline void strCpy(char* dest, const char* src)
{
    if (dest == nullptr || src == nullptr) return;
    int i = 0;
    while(src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}