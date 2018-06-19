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

//��������������� ������� ��� ����� ����� � ��������� ���������
double InputDoubleNumber(double min, double max, string message)
{
	double n;
	do
	{
		cout << message;
		while ((!(cin >> n)) || cin.get() != '\n')
		{
			cin.clear();  // ��������������� ����� ���� �� � ��������� ���������
			cin.sync();   // ������� ����� �� ��������� ��������
			cout << message;
			cin.ignore(100, '\n');
		}
	} while ((n < min) || (n > max));
	return n;
}

//���� ��������� ����������
string InputInformation(string message)
{
	string a;
	cout << message;
	getline(cin, a);
	while (a == "")
	{
		cout << "������� �������� ������!" << endl;
		getline(cin, a);
	}
	return a;
}

//���������� ������ �� ��������� �����
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

//������ ������ � �������� ����
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

//����� ����� ������� �����������
void PrintHeadComputers()
{
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(1) << left << "|" << setw(6) << left << "������" << "|" << setw(6) << left << "ID" << "|" << setw(12) << left << "������������" << "|"
		<< setw(25) << left << "��� ����������" << "|" << setw(13) << left << "������� (���)" << "|" << setw(8) << left << "��� (GB)" << "|"
		<< setw(16) << left << "����������� (GB)" << "|" << setw(8) << left << "HDD (GB)" << "|"
		<< setw(16) << left << "��������� (���.)" << "|" << setw(12) << left << "���-�� (��.)" << "|" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

void PrintFullHeadComputers()
{
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << setw(1) << left << "|" << setw(6) << left << "������" << "|" << setw(15) << left << "�������" << "|" << setw(6) << left << "ID" << "|" << setw(12) << left << "������������" << "|"
		<< setw(25) << left << "��� ����������" << "|" << setw(13) << left << "������� (���)" << "|" << setw(8) << left << "��� (GB)" << "|"
		<< setw(16) << left << "����������� (GB)" << "|" << setw(8) << left << "HDD (GB)" << "|"
		<< setw(16) << left << "��������� (���.)" << "|" << setw(12) << left << "���-�� (��.)" << "|" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
}

//����� ����� ������� �������
void PrintHeadClients()
{
	cout << "------------------------------------------------------" << endl;
	cout << setw(1) << left << "|" << setw(6) << left << "������" << "|" << setw(15) << left << "���" << "|" << setw(15) << left << "�������" << "|" << setw(13) << left << "������ (���.)" << "|" << endl;
	cout << "------------------------------------------------------" << endl;
}

//�������� ������� �� ������������ � ����� �����
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

//�������� ����� ����� �� ������������
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

//���� ����� �����
string InputFileName()
{
	string filename;
	do
	{
		cout << "������� ��� �����: ";
		cin >> filename;
		if (CorrectName(filename))
		{
			filename = filename + ".txt";
			break;
		}
		else
			cout << "�������� ��� �����\n";
	} while (true);
	return filename;
}