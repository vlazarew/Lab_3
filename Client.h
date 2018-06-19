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

	//�������� �������
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

	//����������� �� ���������
	Client();

	//��������� ��������� Client
	Client ChangeClient(Client &result);

	//������������� �������� ������������ ��� ��������� Client
	Client& operator = (Client c);

	void ClientToFile(fstream *file);
};

Client ClientFromFile(fstream *file, bool &ok);

//������� ����� ��������� Client � �������
Client InputScreenClient();

//������� ������ ��������� Client �� �������
void OutputScreenClient(Client st);

//������� ��������� Client � ������
string ToString(Client st, _int32 i);

bool IsEqual(Client first, Client second);

//���������� ��������� Client �� ������
Client ReadFromString(ifstream& input);