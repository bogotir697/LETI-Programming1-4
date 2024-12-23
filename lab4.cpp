#include <iostream>
#include <conio.h>
#include <windows.h>
#include <chrono>
#include "lab4func.h"

using namespace std;
using namespace chrono;

#define hConsole GetStdHandle(STD_OUTPUT_HANDLE)

char str[ML];

#define isStrExist (len(str) > 0)
#define checkStrExist(n) if (!isStrExist) { cout << " Строка не существует!"; for (int i = 0; i < n; i++) { cout << endl; } return; }


bool active = 1;
unsigned char state[2] = { 0, 0 };
unsigned char prevState[2] = { -1, -1 };
unsigned char length[8] = { 7, 2, 3, 1, 2, 1, 2, 7 };
unsigned char step[8] = { 1, 1, 0, 0, 0, 0, 0, 0 };
unsigned inputType = 0;


void gotoxy(int x, int y) {
	COORD coordinate;
	coordinate.X = x;
	coordinate.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);
}

COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		COORD invalid = { 0, 0 };
		return invalid;
	}
}


void mainMenu() {
	printf(" [ Тип ввода ]: ");
	string s = "";
	switch (inputType) {
	case 0:
		s = "консоль";
		break;
	case 1:
		s = "файл";
		break;
	}
	cout << s << endl;
	printf(" [ Ввод строки ]\n");
	printf(" [ Вывод строки ]\n");
	printf(" [ Форматирование строки ]\n");
	printf(" [ ИДЗ 2 ]\n");
	printf(" [ ИДЗ 3 ]\n");
	printf(" [ Поиск подстроки в строке ]\n");

}

void f1ChooseInput() {
	printf(" [ Ввод через консоль ]\n");
	printf(" [ Ввод через файл ]\n");
	gotoxy(24, inputType % 2 + 1);
	putchar('*');
	gotoxy(0, 3);
}

void f2InputString() {
	bool isInputed = 0;
	gotoxy(1, 1);
	switch (inputType) {
	case 0:
		cinStr(str);
		cout << endl;
		isInputed = isStrExist;
		break;
	case 1:
		char path[300];
		cin.getline(path, 300);
		gotoxy(2, 1);
		isInputed = cinStrFile(str, path);
		break;
	}
	if (!isInputed) {
		cout << " Строка не сохранена!" << endl;
		return;
	}
	cout << " Строка сохранена" << endl;
}

void f3OutputString() {
	checkStrExist(length[3]);
	gotoxy(1, 1);
	coutStr(str);
}

void f4FormatString() {
	checkStrExist(length[4]);
	formatPuncMarks(str);
	formatCase(str);
	cout << " Отформатированная строка:\n ";
	coutStr(str);
}

void f5IHT2() {
	checkStrExist(length[5]);
	gotoxy(1, 1);
	coutWordsAlphabetically(str);
}

void f6IHT3() {
	checkStrExist(length[6]);
	gotoxy(1, 1);
	char del[100];
	cinStr(del);
	replaceWhileIn(str, del, (char*)"");
	gotoxy(1, 2);
	coutStr(str);
}

void f7() {
	checkStrExist(length[7]);
	time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
	nanoseconds result;

	gotoxy(1, 1);
	char pattern[300];
	cinStr(pattern, 300);
	int* occurrences;

	start = steady_clock::now();
	occurrences = linearSearchAll(str, pattern);
	end = steady_clock::now();
	result = duration_cast<nanoseconds>(end - start);
	cout << " Линейный поиск: "; 
	cout << (float)result.count() / 1000 << " мс\n ";
	coutArr(occurrences);

	start = steady_clock::now();
	occurrences = kmp(str, pattern);
	end = steady_clock::now();
	result = duration_cast<nanoseconds>(end - start);
	cout << " КМП: ";
	cout << (float)result.count() / 1000 << " нс\n ";
	coutArr(occurrences);

	start = steady_clock::now();
	occurrences = boyerMoore(str, pattern);
	end = steady_clock::now();
	result = duration_cast<nanoseconds>(end - start);
	cout << " Алгоритм Бойера-Мура: ";
	cout << (float)result.count() / 1000 << " нс\n ";
	coutArr(occurrences);
}

void print() {
	int len = 0;
	cout << "\b";
	cout << " ";
	if (prevState[0] != state[0]) {
		system("cls");
		gotoxy(0, 1);
		switch (state[0]) {
		case 0:
			mainMenu();
			break;
		case 1:
			f1ChooseInput();
			break;
		case 2:
			f2InputString();
			break;
		case 3:
			f3OutputString();
			break;
		case 4:
			f4FormatString();
			break;
		case 5:
			f5IHT2();
			break;
		case 6:
			f6IHT3();
			break;
		case 7:
			f7();
			break;
		}
		printf(" exit");
	}
	prevState[0] = state[0];
	gotoxy(0, 0);
	printf(" Практическая работа No4");
	len = length[state[0]] + 1;
	state[1] = state[1] % len;
	gotoxy(0, state[1] + 1);
	printf("%c", 62);
}

void activateFunc() {
	if (state[1] == length[state[0]]) {
		switch (state[0]) {
		case 0:
			active = 0;
			break;
		case 8:
			state[0] = 2;
			break;
		case 9:
			state[0] = 3;
			break;
		case 10:
			state[0] = 6;
			break;
		default:
			state[0] = 0;
		}
		return;
	}
	switch (state[0]) {
	case 0:
		switch (state[1]) {
		default:
			state[0] = state[1] + 1;
		}
		break;
	case 1:
		inputType = state[1];
		state[0] = 0;
		break;
	case 2:
		state[0] = 8;
		break;
	case 3:
		state[0] = 9;
		break;
	case 4:
		break;
	case 6:
		break;
	}
}

int menu()
{
	print();
	char c = _getch();
	while (active) {
		c = _getch();
		switch (c) {
		case 72:
			state[1] += length[state[0]] + 1 - step[state[0]];
			state[1] = state[1] % (length[state[0]] + 1);
			break;
		case 80:
			state[1] += step[state[0]];
			state[1] = state[1] % (length[state[0]] + 1);
			break;
		case 13:
			activateFunc();
			state[1] = length[state[0]] + step[state[0]];
			state[1] = state[1] % (length[state[0]] + 1);
			break;
		}
		print();
	}

	gotoxy(0, 20);
	system("pause");
	return 0;
}


int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL));

	menu();

	SetConsoleTextAttribute(hConsole, 15);
	gotoxy(0, 20);

	return 0;
}