#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"

using namespace std;

class Computer
{
private:
	_int32 _computerID;
	string _computerName;
	string _TypeOfCPU;
	double _CPUfrequency;
	_int32 _capacityRAM;
	_int32 _capacityHDD;
	_int32 _capacityGPU;
	double _cost;
	_int32 _count;

	string _owner;
public:

	//Свойства доступа к полям
	_int32 getcomputerID()
	{
		return _computerID;
	}

	_int32 setcomputerID(_int32 value)
	{
		return _computerID = value;
	}

	string getcomputerName()
	{
		return _computerName;
	}

	string setcomputerName(string value)
	{
		return _computerName = value;
	}

	string getTypeOfCPU()
	{
		return _TypeOfCPU;
	}

	string setTypeOfCPU(string value)
	{
		return _TypeOfCPU = value;
	}

	double getCPUfrequency()
	{
		return _CPUfrequency;
	}

	double setCPUfrequency(double value)
	{
		return _CPUfrequency = value;
	}

	_int32 getcapacityRAM()
	{
		return _capacityRAM;
	}

	_int32 setcapacityRAM(_int32 value)
	{
		return _capacityRAM = value;
	}

	_int32 getcapacityGPU()
	{
		return _capacityGPU;
	}

	_int32 setcapacityGPU(_int32 value)
	{
		return _capacityGPU = value;
	}

	_int32 getcapacityHDD()
	{
		return _capacityHDD;
	}

	_int32 setcapacityHDD(_int32 value)
	{
		return _capacityHDD = value;
	}

	double getcost()
	{
		return _cost;
	}

	double setcost(double value)
	{
		return _cost = value;
	}

	_int32 getcount()
	{
		return _count;
	}

	_int32 setcount(_int32 value)
	{
		return _count = value;
	}

	string getowner()
	{
		return _owner;
	}

	string setowner(string value)
	{
		return _owner = value;
	}

	/*_int32 computerID;
	string computerName;
	string TypeOfCPU;
	double CPUfrequency;
	_int32 capacityRAM;
	_int32 capacityHDD;
	_int32 capacityGPU;
	double cost;
	_int32 count;

	string owner;*/

	//Конструктор по умолчанию
	Computer();

	//Изменение структуры Computer
	Computer ChangeComputer(Computer &result);

	//Переопределение оператора сравнение для структуры данных Компьютер
	bool operator== (Computer comp);

	//Вывод структуры Компьютер в файл
	void ComputerToFile(fstream *file);

	bool SetOwner(string lastname, _int32 money);
};

Computer ComputerFromFile(fstream *file, bool &ok);

//Ввод структуры Компьютер с консоли
Computer InputScreenComputer();

//Вывод структуры Компьютер с консоли
void OutputScreenComputer(Computer comp);

//Вывод структуры Компьютер с консоли
void OutputFullScreenComputer(Computer comp);

//Перевод структуры Компьютер в строку
string ToString(Computer comp, _int32 i);

bool IsEqual(Computer comp1, Computer comp2);

//Считывание структуры Компьютер из строки
Computer ReadFromStringComputer(ifstream& input);

/*Поиск элемента по выбранного критерию
1 - тип процессора
2 - объем ОЗУ
3 - объем видеопамяти
4 - объем жесткого диска*/
bool SearchElement(Computer first, Computer second, _int32 type_search);

/*Ввод критерия поиска в зависимости от критерия
1 - тип процессора
2 - объем ОЗУ
3 - объем видеопамяти
4 - объем жесткого диска*/
Computer InputChangeTypeSearchComputer(_int32 type_search);

/*Сравнение структур по заданному полю
1 - тип процессора
2 - объем ОЗУ
3 - объем видеопамяти
4 - объем жесткого диска*/
_int32 Sort(Computer first, Computer second, _int32 type_search);
