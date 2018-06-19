#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"

using namespace std;

class Client
{
private:
	string _name;
	string _lastname;
	double _money;
public:

	//Свойства доступа
	string getname()
	{
		return _name;
	}

	string setname(string value)
	{
		return _name = value;
	}

	string getlastname()
	{
		return _lastname;
	}

	string setlastname(string value)
	{
		return _lastname = value;
	}

	double getmoney()
	{
		return _money;
	}

	double setmoney(double value)
	{
		return _money = value;
	}

	/*string name;
	string lastname;
	double money;*/

	//Конструктор по умолчанию
	Client();

	//Изменение структуры Client
	Client ChangeClient(Client &result);

	//Перегруженный оператор присваивания для структуры Client
	Client& operator = (Client c);

	void ClientToFile(fstream *file);
};

Client ClientFromFile(fstream *file, bool &ok);

//Функция ввода структуры Client с консоли
Client InputScreenClient();

//Функция вывода структуры Client на консоль
void OutputScreenClient(Client st);

//Перевод структуры Client в строку
string ToString(Client st, _int32 i);

bool IsEqual(Client first, Client second);

//считывание структуры Client из строки
Client ReadFromString(ifstream& input);