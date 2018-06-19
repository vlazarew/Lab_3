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

//����������� �� ���������
Client::Client()
{
	string _name = "";
	string _lastname = "";
	double _money = 0;
}

//��������� ��������� Client
Client Client::ChangeClient(Client &result)
{
	_int32 num = InputNumber(0, 3, "��� ������ ��������?\n1 - ���\n2 - �������\n3 - ������\n0 - ������\n");
	string res;

	switch (num)
	{
	case 1:
		res = InputInformation("������� ��� �������: ");
		result.setname(res);
		break;
	case 2:
		res = InputInformation("������� ������� �������: ");
		result.setlastname(res);
		break;
	case 3:
		result.setmoney(InputDoubleNumber(0, 9999999, "������� ������ ������� (0 - 9 999 999 ���.): "));
		break;
	case 0:
		exit(0);
	default:
		break;
	}

	return result;
}

//������������� �������� ������������ ��� ��������� Client
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

//������� ����� ��������� Client � �������
Client InputScreenClient()
{
	Client cl;

	cl.setname(InputInformation("������� ��� �������: "));
	cl.setlastname(InputInformation("������� ������� �������: "));
	cl.setmoney(InputDoubleNumber(0, 9999999, "������� ������ ������� (0 - 9 999 999 ���.): "));

	return cl;
}

//������� ������ ��������� Client �� �������
void OutputScreenClient(Client cl)
{
	cout << setw(1) << left << "|" << setw(15) << left << cl.getname() << "|" << setw(15) << left << cl.getlastname() << "|" << setw(12) << left << cl.getmoney() << "|";
}

//������� ��������� Client � ������
string ToString(Client cl, _int32 i)
{
	string result = "������ - " + to_string(i) + "\n" + "��� �������: " + cl.getname() + "\n" + "������� �������: " + cl.getlastname() + "\n" + "������ �������: " + to_string(cl.getmoney()) + "\n";
	return result;
}

bool IsEqual(Client first, Client second)
{
	return ((first.getname() == second.getname()) &&
		(first.getlastname() == second.getlastname()) &&
		(first.getmoney() == second.getmoney()));
}

//���������� ��������� Client �� ������
Client ReadFromString(ifstream& input)
{
	Client result;
	string s;

	try
	{
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "��� �������: ";
			result.setname(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "������� �������: ";
			result.setlastname(s.substr(wrd.length(), s.length()));
		}
		if (!input.eof())
		{
			getline(input, s, '\n');
			string wrd = "������ �������: ";
			result.setmoney(atoi(s.substr(wrd.length(), s.length()).c_str()));
		}
	}
	catch (...)
	{
		cout << "������!!!" << endl;
	}

	return result;
}