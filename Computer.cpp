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

//����������� �� ���������
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

//��������� ��������� Computer
Computer Computer::ChangeComputer(Computer &result)
{
	_int32 num = InputNumber(0, 9, "��� ������ ��������?\n1 - ID ����������\n2 - �������� ����������\n3 - ��� ����������\n4 - ������� ����������\n5 - ����� ���\n6 - ����� �����������\n7 - ����� �������� �����\n8 - ��������� ����������\n9 - ���������� �� ������\n0 - ������\n");
	string res;

	switch (num)
	{
	case 1:
		result.setcomputerID(InputNumber(0, 999999, "������� ��� ���������� (0 - 999 999): "));
		break;
	case 2:
		result.setcomputerName(InputInformation("������� �������� ����������: "));
		break;
	case 3:
		result.setTypeOfCPU(InputInformation("������� ��� ����������: "));
		break;
	case 4:
		result.setCPUfrequency(InputDoubleNumber(0, 6, "������� ������� ���������� (0 - 6 ���): "));
		break;
	case 5:
		result.setcapacityRAM(InputNumber(0, 256, "������� ����� ��� (0 - 256 GB): "));
		break;
	case 6:
		result.setcapacityGPU(InputNumber(0, 16, "������� ����� ����������� (0 - 16 GB): "));
		break;
	case 7:
		result.setcapacityHDD(InputNumber(0, 8192, "������� ����� �������� ����� (0 - 8 192 GB): "));
		break;
	case 8:
		result.setcost(InputDoubleNumber(0, 1500000, "������� ��������� ���������� (0 - 1 500 000 ���.): "));
		break;
	case 9:
		result.setcount(InputNumber(0, 1000, "������� ���������� �� ������ (0 - 1 000 ��.): "));
		break;
	case 0:
		exit(0);
	default:
		break;
	}

	return result;
}

//��������������� ��������� ��������� ��� ��������� ������ ���������
bool Computer::operator== (Computer comp)
{
	return ((_computerID == comp.getcomputerID()) && (_computerName == comp.getcomputerName()) &&
		(_TypeOfCPU == comp.getTypeOfCPU()) && (_CPUfrequency == comp.getCPUfrequency()) && (_capacityRAM == comp.getcapacityRAM()) &&
		(_capacityGPU == comp.getcapacityGPU()) && (_capacityHDD == comp.getcapacityHDD()) && (_cost = comp.getcost()) && (_count == comp.getcount()));
}

//����� ��������� ��������� � ����
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

//���� ��������� ��������� � �������
Computer InputScreenComputer()
{
	Computer comp;

	comp.setcomputerID(InputNumber(0, 999999, "������� ��� ���������� (0 - 999 999): "));
	comp.setcomputerName(InputInformation("������� �������� ����������: "));
	comp.setTypeOfCPU(InputInformation("������� ��� ����������: "));
	comp.setCPUfrequency(InputDoubleNumber(0, 6, "������� ������� ���������� (0 - 6 ���): "));
	comp.setcapacityRAM(InputNumber(0, 256, "������� ����� ��� (0 - 256 GB): "));
	comp.setcapacityGPU(InputNumber(0, 16, "������� ����� ����������� (0 - 16 GB): "));
	comp.setcapacityHDD(InputNumber(0, 8192, "������� ����� �������� ����� (0 - 8 192 GB): "));
	comp.setcost(InputDoubleNumber(0, 1500000, "������� ��������� ���������� (0 - 1 500 000 ���.): "));
	comp.setcount(InputNumber(0, 1000, "������� ���������� �� ������ (0 - 1 000 ��.): "));

	return comp;
}

//����� ��������� ��������� �� �������
void OutputScreenComputer(Computer comp)
{
	cout << setw(1) << "|" << setw(6) << left << comp.getcomputerID() << "|" << setw(12) << left << comp.getcomputerName() << "|" << setw(25) << left << comp.getTypeOfCPU() << "|"
		<< setw(13) << left << comp.getCPUfrequency() << "|" << setw(8) << left << comp.getcapacityRAM() << "|" << setw(16) << left << comp.getcapacityGPU() << "|" << setw(8) << left << comp.getcapacityHDD() << "|"
		<< setw(16) << left << comp.getcost() << "|" << setw(12) << left << comp.getcount() << "|";
}

//����� ��������� ��������� � �������
void OutputFullScreenComputer(Computer comp)
{
	cout << setw(1) << "|" << setw(15) << left << comp.getowner() << "|" << setw(6) << left << comp.getcomputerID() << "|" << setw(12) << left << comp.getcomputerName() << "|" << setw(25) << left << comp.getTypeOfCPU() << "|"
		<< setw(13) << left << comp.getCPUfrequency() << "|" << setw(8) << left << comp.getcapacityRAM() << "|" << setw(16) << left << comp.getcapacityGPU() << "|" << setw(8) << left << comp.getcapacityHDD() << "|"
		<< setw(16) << left << comp.getcost() << "|" << setw(12) << left << comp.getcount() << "|";
}

//������� ��������� ��������� � ������
string ToString(Computer comp, _int32 i)
{
	string result = "������ - " + to_string(i - 1) + "\n" + "��� ����������: " + to_string(comp.getcomputerID()) + "\n" + "�������� ����������: " + comp.getcomputerName() + "\n" + "��� ����������: " + comp.getTypeOfCPU() + "\n" +
		"������� ����������: " + to_string(comp.getCPUfrequency()) + "\n" + "����� ���: " + to_string(comp.getcapacityRAM()) + "\n" + "����� �����������: " + to_string(comp.getcapacityGPU()) + "\n"
		+ "����� �������� �����: " + to_string(comp.getcapacityHDD()) + "\n" + "��������� ����������: " + to_string(comp.getcost()) + "\n" + "���������� �� ������: " + to_string(comp.getcount()) + "\n";
	return result;
}

bool IsEqual(Computer first, Computer second)
{
	return ((first.getcomputerID() == second.getcomputerID()) && (first.getcomputerName() == second.getcomputerName()) &&
		(first.getTypeOfCPU() == second.getTypeOfCPU()) && (first.getCPUfrequency() == second.getCPUfrequency()) && (first.getcapacityRAM() == second.getcapacityRAM()) &&
		(first.getcapacityGPU() == second.getcapacityGPU()) && (first.getcapacityHDD() == second.getcapacityHDD()) && (first.getcost() == second.getcost()) && (first.getcount() == second.getcount()));
}

//���������� ��������� ��������� �� ������
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
			string wrd = "��� ����������: ";
			result.setcomputerID(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "�������� ����������: ";
			result.setcomputerName(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "��� ����������: ";
			result.setTypeOfCPU(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "������� ����������: ";
			result.setCPUfrequency(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "����� ���: ";
			result.setcapacityRAM(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "����� �����������: ";
			result.setcapacityGPU(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "����� �������� �����: ";
			result.setcapacityHDD(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "��������� ����������: ";
			result.setcost(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "���������� �� ������: ";
			result.setcount(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
	}
	catch (...)
	{
		cout << "������!!!" << endl;
	}
	return result;
}

/*����� �������� �� ���������� ��������
1 - ��� ����������
2 - ����� ���
3 - ����� �����������
4 - ����� �������� �����*/
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

/*���� �������� ������ � ����������� �� ��������
1 - ��� ����������
2 - ����� ���
3 - ����� �����������
4 - ����� �������� �����*/
Computer InputChangeTypeSearchComputer(_int32 type_search)
{
	Computer result;
	switch (type_search)
	{
	case 1:
		result.setTypeOfCPU(InputInformation("������� ��� ����������: "));
		return result;
	case 2:
		result.setcapacityRAM(InputNumber(0, 256, "������� ����� ��� (0 - 256 GB): "));
		return result;
	case 3:
		result.setcapacityGPU(InputNumber(0, 16, "������� ����� ����������� (0 - 16 GB): "));
		return result;
	case 4:
		result.setcapacityHDD(InputNumber(0, 8192, "������� ����� �������� ����� (0 - 8 192 GB): "));
		return result;
	default:
		return result;
	}
}

/*��������� �������� �� ��������� ����
1 - ��� ����������
2 - ����� ���
3 - ����� �����������
4 - ����� �������� �����*/
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