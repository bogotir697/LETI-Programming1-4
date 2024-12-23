#include "lab4func.h"

char randomSymbol() {
	int i = rand();
	switch (i % 4) {
	case 0:
		return 48 + i % 10;
	case 1:
		return 65 + i % 26;
	case 2:
		return 97 + i % 26;
	case 3:
		return 32;
	}
}

void createStr(char* s, int l) {
	for (int i = 0; i < l - 1; i++) {
		*(s + i) = randomSymbol();
	}
	*(s + l - 1) = '\0';
}

bool coutFile(char* fileName) {
	ifstream file;
	file.open(fileName);
	if (!file.is_open()) {
		cout << "File not found!" << endl;
		return 0;
	}
	char s[ML];
	while (!file.eof()) {
		file.getline(s, 100);
		cout << s << endl;
	}
	file.close();
	return 1;
}

void coutStr(char* s) {
	for (s; *s; s++) {
		cout << *s;
	}
	cout << endl;
}

void coutStr(char* s, int start, int end) {
	char c = s[end];
	s[end] = '\0';
	coutStr(s + start);
	s[end] = c;
}

int len(char* s) {
	int c = 0;
	for (s; *s; s++) {
		c++;
	}
	return c;
}

int len(int* arr) {
	int c = 0;
	for (arr; *arr >= 0; arr++) {
		c++;
	}
	return c;
}

void coutArr(int* arr, char c) {
	for (int* i = arr; *i >= 0; i++) {
		cout << *i << c;
	}
	cout << endl;
}

int linearSearch(char* s, char* subS, int start, int end) {
	int n = len(s);
	int m = len(subS);
	end = ((end < 0) ? n - m : end);
	int table[ML];
	int k = 0;
	for (int i = start; i <= end; i++) {
		if (*(s + i) == *subS) {
			table[k++] = i;
		}
	}
	table[k] = -1;
	for (int* index = table; *index >= 0; index++) {
		int i = 0;
		for (i; i < n - *index; i++) {
			if (s[i + *index] != subS[i]) {
				break;
			}
		}
		if (i == m) {
			return *index;
		}
	}
	return -1;
}

int* linearSearchAll(char* s, char* subS, int start, int end) {
	int n = len(s);
	int m = len(subS);
	end = ((end < 0) ? n - m : end);
	int table[ML];
	int k = 0;
	for (int i = start; i <= end; i++) {
		if (*(s + i) == *subS) {
			table[k++] = i;
		}
	}
	table[k] = -1;
	int indexes[ML];
	k = 0;
	for (int* index = table; *index >= 0; index++) {
		int i = 0;
		for (i; i < n - *index; i++) {
			if (s[i + *index] != subS[i]) {
				break;
			}
		}
		if (i == m) {
			indexes[k] = *index;
			k++;
		}
	}
	indexes[k] = -1;
	return indexes;
}

int* computeLsp(char* pattern) {
	int n = len(pattern);
	int lsp[ML] = { 0 };
	int j = 0, i = 1;
	while (i < n) {
		if (pattern[i] == pattern[j]) {
			j++;
			lsp[i] = j;
			i++;
		}
		else {
			if (j != 0) {
				j = lsp[j - 1];
			}
			else {
				lsp[i] = 0;
				i++;
			}
		}
	}
	lsp[n] = -1;
	return lsp;
}

int* kmp(char* s, char* pattern) {
	int* lsp = computeLsp(pattern);
	int occurrences[ML];
	int n = len(s), m = len(pattern);
	int i = 0, j = 0;
	int k = 0;
	while (i < n) {
		if (s[i] == pattern[j]) {
			i++;
			j++;
		}
		if (j == m) {
			occurrences[k] = i - j;
			k++;
		}
		else if (i < n && s[i] != pattern[j]) {
			if (j != 0) {
				j = lsp[j - 1];
			}
			else {
				i++;
			}
		}
	}
	occurrences[k] = -1;
	return occurrences;
}

int* boyerMoore(char* s, char* pattern) {
	int n = len(s), m = len(pattern);
	int occurrences[ML];
	int k = 0;
	
	int shift[256];
	for (int *i = shift, *end = shift + 256; i < end; i++) {
		*i = m;
	}
	for (int i = 0; i < m - 1; i++) {
		shift[pattern[i]] = m - i - 1;
	}

	int i = 0;
	while (i <= n - m) {
		int j = m - 1;
		while (j >= 0 && pattern[j] == s[i + j]) {
			--j;
		}
		if (j < 0) {
			occurrences[k] = i;
			k++;
			i += shift[s[i + m - 1]];
		}
		else {
			if (j == m - 1) {
				i += shift[s[i + j]];
			}
			else {
				i += shift[pattern[j]];
			}
		}
	}
	occurrences[k] = -1;
	return occurrences;
}


bool isIn(char* s, char* subS) {
	return (linearSearch(s, subS) >= 0);
}

void cinStr(char* s, int n) {
	cin.getline(s, n);
}

bool cinStrFile(char* s, char* path) {
	ifstream file;
	file.open(path);
	if (!file.is_open()) {
		cout << "Файл не найден!" << endl;
		return 0;
	}
	if (file.eof()) {
		return 0;
	}
	file.getline(s, ML * 3 / 4, '.');
	file.close();
	return 1;
}

void moveStr(char* s, int start, int move) {
	if (move == 0) {
		return;
	}
	int l = len(s);
	int i, end, sign = move / abs(move);
	if (sign > 0) {
		i = l;
		end = start;
	}
	else {
		i = start - move;
		end = l;
	}
	for (i; i * move >= end * move; i -= sign) {
		s[i + move] = s[i];
	}
}

void replace(char* s, char* oldSubS, char* newSubS, int max) {
	int index = linearSearch(s, oldSubS);
	int lenOldS = len(oldSubS);
	int lenNewS = len(newSubS);
	int move = lenNewS - lenOldS;
	while (max != 0 && index >= 0) {
		max--;
		moveStr(s, index, move);
		for (int i = 0; i < lenNewS; i++) {
			*(s + index + i) = *(newSubS + i);
		}
		index = linearSearch(s, oldSubS, index + lenNewS);
	}
}

void replaceWhileIn(char* s, char* oldSubS, char* newSubS) {
	while (linearSearch(s, oldSubS) >= 0) {
		replace(s, oldSubS, newSubS);
	}
}

void changeStr(char* s, char* newS) {
	for (int i = 0, end = len(newS) + 1; i < end; i++) {
		*(s + i) = *(newS + i);
	}
}

void lower(char* s) {
	for (s; *s; s++) {
		if ((*s >= 65) && (*s <= 90)) {
			*s += 97 - 65;
		}
	}
}

void formatPuncMarks(char* s) {
	char oldSubS[10] = "  ";
	char newSubS[10] = " ";
	char pMarks[10] = ",!?:'";
	for (char* mark = pMarks, *end = pMarks + len(pMarks); mark < end; mark++) {
		newSubS[0] = *mark;
		oldSubS[0] = *mark;
		oldSubS[1] = *mark;
		replaceWhileIn(s, oldSubS, newSubS);
		oldSubS[0] = ' ';
		replaceWhileIn(s, oldSubS, newSubS);
	}
	replace(s, (char*)",", (char*)", ");
	replace(s, (char*)"-", (char*)" - ");
	replace(s, (char*)"' ", (char*)"'");
	replaceWhileIn(s, (char*)"  ", (char*)" ");
}

void formatCase(char* s) {
	int upperIndexes[ML];
	int k = 0;

	for (char* i = s + len(s); i >= s; i--) {
		bool isUpperCase = (*i >= 65) && (*i <= 90),
			isFirst = i - 1 < s,
			isPrevSpace = *(i - 1) == ' ';
		if (isUpperCase && (isPrevSpace || isFirst)) {
			upperIndexes[k] = i - s;
			k++;
		}
	}
	upperIndexes[k] = -1;
	lower(s);
	for (int* i = upperIndexes; *i >= 0; i++) {
		s[*i] -= 97 - 65;
	}
}

void swapWords(char* s1, char* s2) {
	char temp[100];
	changeStr(temp, s2);
	temp[len(s2)] = ' ';
	changeStr(&temp[len(s2) + 1], s1);
	changeStr(s1, temp);
	s1[len(s2)] = 0;
}

void sort(char* s, int* spaces, int n) {
	for (int i = len(spaces) - 1; i > 0; i--) {
		for (int* wordI = spaces; *(wordI + 1) >= 0; wordI++) {
			int k = 0;
			char* word = s + *wordI;
			char* word1 = s + *(wordI + 1);
			while ((*(word + k) == *(word1 + k)) && *(word + k) && *(word1 + k)) {
				k++;
			}
			if (*(word + k) > *(word1 + k)) {
				*(wordI + 1) = *wordI + len(word1) + 1;
				swapWords(word, word1);
			}
		}
	}
	for (int* i = spaces; *i >= 0; i++) {
		s[*i - 1] = ' ';
	}
}

void coutWordsAlphabetically(char* s) {
	char newS[ML];
	changeStr(newS, s);
	moveStr(newS, 0, 1);
	newS[0] = ' ';
	char pMarks[10] = ",!?:'-.";
	for (char* mark = pMarks, *end = pMarks + len(pMarks); mark < end; mark++) {
		replaceWhileIn(newS, new char[2] {*mark, '\0'}, (char*)" ");
	}
	replaceWhileIn(newS, (char*)"  ", (char*)" ");

	int spaces[ML];
	int k = 0;
	for (char* c = newS; *c; c++) {
		if (*c == ' ') {
			spaces[k] = c - newS;
			k++;
		}
	}
	spaces[k] = -1;
	int n = len(newS);
	for (int* i = spaces; *i >= 0; i++) {
		newS[*i] = '\0';
		(*i)++;
	}
	sort(newS, spaces, n);
	coutStr(&newS[1]);
}