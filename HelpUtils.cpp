#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cmath>
#include <cstring>
#include <fstream>
#include <istream>
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "HelpUtils.h"
using namespace std;

//Вспомогательная функция для ввода числа в указанном интервале
double InputDoubleNumber(double min, double max, string message)
{
	double n;
	do
	{
		cout << message;
		while ((!(cin >> n)) || cin.get() != '\n')
		{
			cin.clear();  // восстанавливает поток если он в ошибочном сосотянии
			cin.sync();   // очищает поток от имеющихся символов
			cout << message;
			cin.ignore(100, '\n');
		}
	} while ((n < min) || (n > max));
	return n;
}

//Ввод текстовой информации
string InputInformation(string message)
{
	string a;
	cout << message;
	getline(cin, a);
	while (a == "")
	{
		cout << "Введите непустую строку!" << endl;
		getline(cin, a);
	}
	return a;
}

//Считывание строки из бинарного файла
string StrFromBin(fstream *f) {
	string result;
	_int32 len;
	if (!f->read(reinterpret_cast<char*>(&len), sizeof(len))) {
		return "";
	}
	char *buf = new char[len];
	if (!f->read(buf, len)) {
		return "";
	}
	result = buf;
	delete[] buf;
	return result;
}

//Запись строки в бинарный файл
void StrToBin(fstream *f, string str) {
	_int32 len = str.length() + 1;
	f->write(reinterpret_cast<char*>(&len), sizeof(len));
	f->write(str.c_str(), len);
}

//to_str(s)
/*string toString(_int32 val)
{
	ostringstream oss;
	oss << val;
	return oss.str();
}*/

//Вывод шапки таблицы компьютеров
void PrintHeadComputers()
{
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(1) << left << "|" << setw(6) << left << "Запись" << "|" << setw(6) << left << "ID" << "|" << setw(12) << left << "Наименование" << "|"
		<< setw(25) << left << "Тип процессора" << "|" << setw(13) << left << "Частота (ГГц)" << "|" << setw(8) << left << "ОЗУ (GB)" << "|"
		<< setw(16) << left << "Видеопамять (GB)" << "|" << setw(8) << left << "HDD (GB)" << "|"
		<< setw(16) << left << "Стоимость (руб.)" << "|" << setw(12) << left << "Кол-во (шт.)" << "|" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void PrintFullHeadComputers()
{
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(1) << left << "|" << setw(6) << left << "Запись" << "|" << setw(15) << left << "Фамилия" << "|" << setw(6) << left << "ID" << "|" << setw(12) << left << "Наименование" << "|"
		<< setw(25) << left << "Тип процессора" << "|" << setw(13) << left << "Частота (ГГц)" << "|" << setw(8) << left << "ОЗУ (GB)" << "|"
		<< setw(16) << left << "Видеопамять (GB)" << "|" << setw(8) << left << "HDD (GB)" << "|"
		<< setw(16) << left << "Стоимость (руб.)" << "|" << setw(12) << left << "Кол-во (шт.)" << "|" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

//Вывод шапки таблицы клиента
void PrintHeadClients()
{
	cout << "------------------------------------------------------" << endl;
	cout << setw(1) << left << "|" << setw(6) << left << "Запись" << "|" << setw(15) << left << "Имя" << "|" << setw(15) << left << "Фамилия" << "|" << setw(13) << left << "Баланс (руб.)" << "|" << endl;
	cout << "------------------------------------------------------" << endl;
}

//Проверка символа на корректность в имени файла
bool CorrectSymbol(char c)
{
	switch (c)
	{
	case '.':
	case '*':
	case '?':
	case '<':
	case '>':
	case ':':
	case '|':
	case '/':
		return false;
	default:
		return true;
	}
}

//Проверка имени файла на корректность
bool CorrectName(string name)
{
	_int32 i = 0;
	bool check = true;
	for (_int32 i = 0; (i < name.length() && check); i++)
	{
		check = CorrectSymbol(name[i]);
	}
	return check;
}

//Ввод имени файла
string InputFileName()
{
	string filename;
	do
	{
		cout << "Введите имя файла: ";
		cin >> filename;
		if (CorrectName(filename))
		{
			filename = filename + ".txt";
			break;
		}
		else
			cout << "Неверное имя файла\n";
	} while (true);
	return filename;
}