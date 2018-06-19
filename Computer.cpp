#pragma once
#include <cstdio>
#include <sstream>
#include <cmath>
#include <string>
#include <iostream>
#include <string>
#include "HelpUtils.h"
#include "VectorOperations.h"
#include "Client.h"
#include "Computer.h"

//Конструктор по умолчанию
Computer::Computer()
{
	_int32 _computerID = 0;
	string _computerName = "";
	string _TypeOfCPU = "";
	double _CPUfrequency = 0;
	_int32 _capacityRAM = 0;
	_int32 _capacityGPU = 0;
	_int32 _capacityHDD = 0;
	double _cost = 0;
	_int32 _count = 0;
}

//Изменение структуры Computer
Computer Computer::ChangeComputer(Computer &result)
{
	_int32 num = InputNumber(0, 9, "Что хотите изменить?\n1 - ID компьютера\n2 - Название компьютера\n3 - Тип процессора\n4 - Частоту процессора\n5 - Объем ОЗУ\n6 - Объем видеопамяти\n7 - Объем жесткого диска\n8 - Стоимость компьютера\n9 - Количество на складе\n0 - Отмена\n");
	string res;

	switch (num)
	{
	case 1:
		result.setcomputerID(InputNumber(0, 999999, "Введите код компьютера (0 - 999 999): "));
		break;
	case 2:
		result.setcomputerName(InputInformation("Введите название компьютера: "));
		break;
	case 3:
		result.setTypeOfCPU(InputInformation("Введите тип процессора: "));
		break;
	case 4:
		result.setCPUfrequency(InputDoubleNumber(0, 6, "Введите частоту процессора (0 - 6 ГГц): "));
		break;
	case 5:
		result.setcapacityRAM(InputNumber(0, 256, "Введите объем ОЗУ (0 - 256 GB): "));
		break;
	case 6:
		result.setcapacityGPU(InputNumber(0, 16, "Введите объем видеопамяти (0 - 16 GB): "));
		break;
	case 7:
		result.setcapacityHDD(InputNumber(0, 8192, "Введите объем жесткого диска (0 - 8 192 GB): "));
		break;
	case 8:
		result.setcost(InputDoubleNumber(0, 1500000, "Введите стоимость компьютера (0 - 1 500 000 руб.): "));
		break;
	case 9:
		result.setcount(InputNumber(0, 1000, "Введите количество на складе (0 - 1 000 шт.): "));
		break;
	case 0:
		exit(0);
	default:
		break;
	}

	return result;
}

//Переопределение оператора сравнение для структуры данных Компьютер
bool Computer::operator== (Computer comp)
{
	return ((_computerID == comp.getcomputerID()) && (_computerName == comp.getcomputerName()) &&
		(_TypeOfCPU == comp.getTypeOfCPU()) && (_CPUfrequency == comp.getCPUfrequency()) && (_capacityRAM == comp.getcapacityRAM()) &&
		(_capacityGPU == comp.getcapacityGPU()) && (_capacityHDD == comp.getcapacityHDD()) && (_cost = comp.getcost()) && (_count == comp.getcount()));
}

//Вывод структуры Компьютер в файл
void Computer::ComputerToFile(fstream *file)
{
	StrToBin(file, this->_owner);
	file->write(reinterpret_cast<char*>(&(this->_computerID)), sizeof(this->_computerID));
	StrToBin(file, this->_computerName);
	StrToBin(file, this->_TypeOfCPU);
	file->write(reinterpret_cast<char*>(&(this->_CPUfrequency)), sizeof(this->_CPUfrequency));
	file->write(reinterpret_cast<char*>(&(this->_capacityRAM)), sizeof(this->_capacityRAM));
	file->write(reinterpret_cast<char*>(&(this->_capacityGPU)), sizeof(this->_capacityGPU));
	file->write(reinterpret_cast<char*>(&(this->_capacityHDD)), sizeof(this->_capacityHDD));
	file->write(reinterpret_cast<char*>(&(this->_cost)), sizeof(this->_cost));
	file->write(reinterpret_cast<char*>(&(this->_count)), sizeof(this->_count));
}

bool Computer::SetOwner(string lastname, _int32 money)
{
	if (money >= (*this)._cost)
	{
		_owner = lastname;
		return true;
	}
	else
	{
		return false;
	}
}

Computer ComputerFromFile(fstream *file, bool &ok)
{
	Computer comp;
	comp.setowner(StrFromBin(file));
	_int32 temp;
	double tmp;
	ok = (bool)file->read(reinterpret_cast<char*>(&(temp)), sizeof(temp));
	if (ok)
	{
		comp.setcomputerID(temp);
		comp.setcomputerName(StrFromBin(file));
		comp.setTypeOfCPU(StrFromBin(file));
		ok = (bool)file->read(reinterpret_cast<char*>(&(tmp)), sizeof(tmp));
		comp.setCPUfrequency(tmp);
		ok = (bool)file->read(reinterpret_cast<char*>(&(temp)), sizeof(temp));
		comp.setcapacityRAM(temp);
		ok = (bool)file->read(reinterpret_cast<char*>(&(temp)), sizeof(temp));
		comp.setcapacityGPU(temp);
		ok = (bool)file->read(reinterpret_cast<char*>(&(temp)), sizeof(temp));
		comp.setcapacityHDD(temp);
		ok = (bool)file->read(reinterpret_cast<char*>(&(tmp)), sizeof(tmp));
		comp.setcost(tmp);
		ok = (bool)file->read(reinterpret_cast<char*>(&(temp)), sizeof(temp));
		comp.setcount(temp);
	}

	return comp;
}

//Ввод структуры Компьютер с консоли
Computer InputScreenComputer()
{
	Computer comp;

	comp.setcomputerID(InputNumber(0, 999999, "Введите код компьютера (0 - 999 999): "));
	comp.setcomputerName(InputInformation("Введите название компьютера: "));
	comp.setTypeOfCPU(InputInformation("Введите тип процессора: "));
	comp.setCPUfrequency(InputDoubleNumber(0, 6, "Введите частоту процессора (0 - 6 ГГц): "));
	comp.setcapacityRAM(InputNumber(0, 256, "Введите объем ОЗУ (0 - 256 GB): "));
	comp.setcapacityGPU(InputNumber(0, 16, "Введите объем видеопамяти (0 - 16 GB): "));
	comp.setcapacityHDD(InputNumber(0, 8192, "Введите объем жесткого диска (0 - 8 192 GB): "));
	comp.setcost(InputDoubleNumber(0, 1500000, "Введите стоимость компьютера (0 - 1 500 000 руб.): "));
	comp.setcount(InputNumber(0, 1000, "Введите количество на складе (0 - 1 000 шт.): "));

	return comp;
}

//Вывод структуры Компьютер на консоль
void OutputScreenComputer(Computer comp)
{
	cout << setw(1) << "|" << setw(6) << left << comp.getcomputerID() << "|" << setw(12) << left << comp.getcomputerName() << "|" << setw(25) << left << comp.getTypeOfCPU() << "|"
		<< setw(13) << left << comp.getCPUfrequency() << "|" << setw(8) << left << comp.getcapacityRAM() << "|" << setw(16) << left << comp.getcapacityGPU() << "|" << setw(8) << left << comp.getcapacityHDD() << "|"
		<< setw(16) << left << comp.getcost() << "|" << setw(12) << left << comp.getcount() << "|";
}

//Вывод структуры Компьютер с консоли
void OutputFullScreenComputer(Computer comp)
{
	cout << setw(1) << "|" << setw(15) << left << comp.getowner() << "|" << setw(6) << left << comp.getcomputerID() << "|" << setw(12) << left << comp.getcomputerName() << "|" << setw(25) << left << comp.getTypeOfCPU() << "|"
		<< setw(13) << left << comp.getCPUfrequency() << "|" << setw(8) << left << comp.getcapacityRAM() << "|" << setw(16) << left << comp.getcapacityGPU() << "|" << setw(8) << left << comp.getcapacityHDD() << "|"
		<< setw(16) << left << comp.getcost() << "|" << setw(12) << left << comp.getcount() << "|";
}

//Перевод структуры Компьютер в строку
string ToString(Computer comp, _int32 i)
{
	string result = "Запись - " + to_string(i - 1) + "\n" + "Код компьютера: " + to_string(comp.getcomputerID()) + "\n" + "Название компьютера: " + comp.getcomputerName() + "\n" + "Тип процессора: " + comp.getTypeOfCPU() + "\n" +
		"Частота процессора: " + to_string(comp.getCPUfrequency()) + "\n" + "Объем ОЗУ: " + to_string(comp.getcapacityRAM()) + "\n" + "Объем видеопамяти: " + to_string(comp.getcapacityGPU()) + "\n"
		+ "Объем жесткого диска: " + to_string(comp.getcapacityHDD()) + "\n" + "Стоимость компьютера: " + to_string(comp.getcost()) + "\n" + "Количество на складе: " + to_string(comp.getcount()) + "\n";
	return result;
}

bool IsEqual(Computer first, Computer second)
{
	return ((first.getcomputerID() == second.getcomputerID()) && (first.getcomputerName() == second.getcomputerName()) &&
		(first.getTypeOfCPU() == second.getTypeOfCPU()) && (first.getCPUfrequency() == second.getCPUfrequency()) && (first.getcapacityRAM() == second.getcapacityRAM()) &&
		(first.getcapacityGPU() == second.getcapacityGPU()) && (first.getcapacityHDD() == second.getcapacityHDD()) && (first.getcost() == second.getcost()) && (first.getcount() == second.getcount()));
}

//Считывание структуры Компьютер из строки
Computer ReadFromStringComputer(ifstream& input)
{
	Computer result;
	string s;
	try
	{
		if (!input.eof())
		{
			getline(input, s);
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Код компьютера: ";
			result.setcomputerID(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Название компьютера: ";
			result.setcomputerName(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Тип процессора: ";
			result.setTypeOfCPU(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Частота процессора: ";
			result.setCPUfrequency(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Объем ОЗУ: ";
			result.setcapacityRAM(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Объем видеопамяти: ";
			result.setcapacityGPU(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Объем жесткого диска: ";
			result.setcapacityHDD(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Стоимость компьютера: ";
			result.setcost(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "Количество на складе: ";
			result.setcount(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
	}
	catch (...)
	{
		cout << "Ошибка!!!" << endl;
	}
	return result;
}

/*Поиск элемента по выбранного критерию
1 - тип процессора
2 - объем ОЗУ
3 - объем видеопамяти
4 - объем жесткого диска*/
bool SearchElement(Computer first, Computer second, _int32 type_search)
{
	switch (type_search)
	{
	case 1:
		return (first.getTypeOfCPU() == second.getTypeOfCPU());
	case 2:
		return (first.getcapacityRAM() == second.getcapacityRAM());
	case 3:
		return (first.getcapacityGPU() == second.getcapacityGPU());
	case 4:
		return (first.getcapacityHDD() == second.getcapacityHDD());
	default:
		break;
	}
}

/*Ввод критерия поиска в зависимости от критерия
1 - тип процессора
2 - объем ОЗУ
3 - объем видеопамяти
4 - объем жесткого диска*/
Computer InputChangeTypeSearchComputer(_int32 type_search)
{
	Computer result;
	switch (type_search)
	{
	case 1:
		result.setTypeOfCPU(InputInformation("Введите тип процессора: "));
		return result;
	case 2:
		result.setcapacityRAM(InputNumber(0, 256, "Введите объем ОЗУ (0 - 256 GB): "));
		return result;
	case 3:
		result.setcapacityGPU(InputNumber(0, 16, "Введите объем видеопамяти (0 - 16 GB): "));
		return result;
	case 4:
		result.setcapacityHDD(InputNumber(0, 8192, "Введите объем жесткого диска (0 - 8 192 GB): "));
		return result;
	default:
		return result;
	}
}

/*Сравнение структур по заданному полю
1 - тип процессора
2 - объем ОЗУ
3 - объем видеопамяти
4 - объем жесткого диска*/
_int32 Sort(Computer first, Computer second, _int32 type_search)
{
	switch (type_search)
	{
	case 1:
		if (first.getTypeOfCPU() > second.getTypeOfCPU()) return 1;
		else if (first.getTypeOfCPU() < second.getTypeOfCPU()) return -1;
		else return 0;
	case 2:
		if (first.getcapacityRAM() > second.getcapacityRAM()) return 1;
		else if (first.getcapacityRAM() < second.getcapacityRAM()) return -1;
		else return 0;
	case 3:
		if (first.getcapacityGPU() > second.getcapacityGPU()) return 1;
		else if (first.getcapacityGPU() < second.getcapacityGPU()) return -1;
		else return 0;
	case 4:
		if (first.getcapacityHDD() > second.getcapacityHDD()) return 1;
		else if (first.getcapacityHDD() < second.getcapacityHDD()) return -1;
		else return 0;
	default:
		return -2;
	}
}