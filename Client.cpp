#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"
#include "Client.h"

using namespace std;

//Конструктор по умолчанию
Client::Client()
{
	string _name = "";
	string _lastname = "";
	double _money = 0;
}

//Изменение структуры Client
Client Client::ChangeClient(Client &result)
{
	_int32 num = InputNumber(0, 3, "Что хотите изменить?\n1 - Имя\n2 - Фамилия\n3 - Баланс\n0 - Отмена\n");
	string res;

	switch (num)
	{
	case 1:
		res = InputInformation("Введите имя клиента: ");
		result.setname(res);
		break;
	case 2:
		res = InputInformation("Введите фамилию клиента: ");
		result.setlastname(res);
		break;
	case 3:
		result.setmoney(InputDoubleNumber(0, 9999999, "Введите баланс клиента (0 - 9 999 999 руб.): "));
		break;
	case 0:
		exit(0);
	default:
		break;
	}

	return result;
}

//Перегруженный оператор присваивания для структуры Client
Client& Client::operator= (Client cl)
{
	_name = cl.getname();
	_lastname = cl.getlastname();
	_money = cl.getmoney();

	return (*this);
}

void Client::ClientToFile(fstream *file)
{
	StrToBin(file, this->_name);
	StrToBin(file, this->_lastname);
	file->write(reinterpret_cast<char*>(&(this->_money)), sizeof(this->_money));
}

Client ClientFromFile(fstream *file, bool &ok)
{
	Client cl;
	double temp;
	cl.setname(StrFromBin(file));
	cl.setlastname(StrFromBin(file));
	ok = (bool)file->read(reinterpret_cast<char*>(&(temp)), sizeof(temp));
	cl.setmoney(temp);

	return cl;
}

//Функция ввода структуры Client с консоли
Client InputScreenClient()
{
	Client cl;

	cl.setname(InputInformation("Введите имя клиента: "));
	cl.setlastname(InputInformation("Введите фамилию клиента: "));
	cl.setmoney(InputDoubleNumber(0, 9999999, "Введите баланс клиента (0 - 9 999 999 руб.): "));

	return cl;
}

//Функция вывода структуры Client на консоль
void OutputScreenClient(Client cl)
{
	cout << setw(1) << left << "|" << setw(15) << left << cl.getname() << "|" << setw(15) << left << cl.getlastname() << "|" << setw(12) << left << cl.getmoney() << "|";
}

//Перевод структуры Client в строку
string ToString(Client cl, _int32 i)
{
	string result = "Запись - " + to_string(i) + "\n" + "Имя клиента: " + cl.getname() + "\n" + "Фамилия клиента: " + cl.getlastname() + "\n" + "Баланс клиента: " + to_string(cl.getmoney()) + "\n";
	return result;
}

bool IsEqual(Client first, Client second)
{
	return ((first.getname() == second.getname()) &&
		(first.getlastname() == second.getlastname()) &&
		(first.getmoney() == second.getmoney()));
}

//считывание структуры Client из строки
Client ReadFromString(ifstream& input)
{
	Client result;
	string s;

	try
	{
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Имя клиента: ";
			result.setname(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Фамилия клиента: ";
			result.setlastname(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Баланс клиента: ";
			result.setmoney(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
	}
	catch (...)
	{
		cout << "Ошибка!!!" << endl;
	}

	return result;
}