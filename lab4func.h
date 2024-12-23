#pragma once

#include <iostream>
#include <fstream>

using namespace std;

#define ML 10000

char randomSymbol();
void createStr(char* s, int l);
bool coutFile(char* fileName);
void coutStr(char* s);
void coutStr(char* s, int start, int end);
void coutArr(int* arr, char c = ' ');
int len(char* s);
int len(int* arr);
int linearSearch(char* s, char* subS, int start = 0, int end = -1);
int* linearSearchAll(char* s, char* subS, int start = 0, int end = -1);
int* computeLsp(char* pattern);
int* kmp(char* s, char* pattern);
int* boyerMoore(char* s, char* pattern);
bool isIn(char* s, char* subS);
void cinStr(char* s, int n = ML * 3 / 4);
bool cinStrFile(char* s, char* path);
void moveStr(char* s, int start, int move);
void replace(char* s, char* oldSubS, char* newSubS, int max = -1);
void replaceWhileIn(char* s, char* oldSubS, char* newSubS);
void changeStr(char* s, char* newS);
void lower(char* s);
void formatPuncMarks(char* s);
void formatCase(char* s);
void swapWords(char* s1, char* s2);
void sort(char* s, int* spaces, int n);
void coutWordsAlphabetically(char* s);
