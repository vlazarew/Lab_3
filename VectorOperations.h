#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Computer.h"
#include "Client.h"
#include "HelpUtils.h"

using namespace std;

template <typename Type>
struct iterator {
	Type *ptr;
	iterator(Type* ptr_ = 0) : ptr(ptr_) {}
	Type& operator*() { return *ptr; }
	Type* operator->() { return ptr; }
	Type* operator++() { return ++ptr; }
	Type* operator--() { return --ptr; }
	bool operator==(const iterator& other) const { return ptr == other.ptr; }
	bool operator!=(const iterator& other) const { return !(*this == other); }
};

template <class Type>
class Task {
private:
	vector<Type> vect; //��� ���������

	//���������� �� ��������� ��������, Compare - �������, ������������ ��� ��������  
	void Sort(_int32 n, _int32 type_search, int(*Compare)(Type, Type, int))
	{
		_int32 i, j, step;
		Type tmp;
		for (step = n / 2; step > 0; step /= 2)
			for (i = step; i < n; i++)
			{
				tmp = vect[i];
				for (j = i; j >= step; j -= step)
				{
					if ((Compare(tmp, vect[j - step], type_search) == -1))
						vect[j] = vect[j - step];
					else
						break;
				}
				vect[j] = tmp;
			}

	}

	//�������� �����, Compare - �������, ������������ ��� �������� 
	_int32 BinarySearchElement(_int32 left, _int32 right, _int32 type_search, Type d, int(*Compare)(Type, Type, int))
	{
		_int32 mid = 0;
		while (1)
		{
			mid = (left + right) / 2;

			if (Compare(d, vect[mid], type_search) == -1)
				right = mid - 1;
			else if (Compare(d, vect[mid], type_search) == 1)
				left = mid + 1;
			else
				return mid;

			if (left > right)
				return -1;
		}
	}

public:

	vector<Type> getvect()
	{
		return vect;
	}

	vector<Type> setvect(vector<Type> value)
	{
		return vect = value;
	}

	//vector<Type> vect; //��� ���������

	//�������� ��������
	void Remove(_int32 num)
	{
		if (num != 0)
			vect.erase(vect.begin() + num - 1);
	}

	//���������� ��������
	void Add(Type &elem)
	{
		for (_int32 i = 0; i < vect.size(); i++)
		{
			if (IsEqual(elem, vect[i]))
			{
				if (InputNumber(0, 1, "\n�� ������ �������� ������(0 - ���, 1 - ��)\n��� �����: ") == 1)
				{
					vect[i] = elem;
					cout << "������ ��������";
					return;
				}
				else
				{
					cout << "������ �� ��������";
					return;
				}
			}
		}
		vect.push_back(elem);
	}

	//������ �������
	_int32 size()
	{
		return vect.size();
	}

	//�������� �� �������
	bool Is_empty()
	{
		return (vect.size() == 0);
	}

	//����� � ����, f - �������, ������������ ���� ��������� � ����  
	void OutputFileComp(vector<Computer> items, string(*f)(Computer, int))
	{
		string newfname = InputFileName();
		ofstream fout(newfname);
		if (fout)
		{
			vector<Computer>::const_iterator pos;
			_int32 count = 1;
			for (pos = items.begin(); pos != items.end(); ++pos)
			{
				fout << f(*pos, count) << ' ';
				count++;
			}
			cout << endl << "���� ��������" << endl;
			fout.close();
		}
		else
		{
			cout << "���� �� ��������" << endl;
		}
	}

	//����� �� �����, f - �������, ������� ������� ���� ��������� �� �����  
	void OutputScreenComp(vector<Computer> items, void(*f) (Computer))
	{
		vector<Computer>::const_iterator pos;
		_int32 count = 1;
		for (pos = items.begin(); pos != items.end(); ++pos)
		{
			cout << setw(1) << "|" << setw(6) << left << count;
			f(*pos);
			++count;
			cout << endl;
		}
		if (items.empty())
			cout << "������ ����" << endl;
	}

	//����� �� �����, f - �������, ������� ������� ���� ��������� �� �����  
	void OutputFullScreenComp(vector<Computer> items, void(*f) (Computer))
	{
		vector<Computer>::const_iterator pos;
		_int32 count = 1;
		for (pos = items.begin(); pos != items.end(); ++pos)
		{
			cout << setw(1) << "|" << setw(6) << left << count;
			f(*pos);
			++count;
			cout << endl;
		}
		if (items.empty())
			cout << "������ ����" << endl;
	}
	//����� � ����, f - �������, ������������ ���� ��������� � ����  
	void OutputFileCl(vector<Client> items, string(*f)(Client, int))
	{
		string newfname = InputFileName();
		ofstream fout(newfname);
		if (fout)
		{
			vector<Client>::const_iterator pos;
			_int32 count = 1;
			for (pos = items.begin(); pos != items.end(); ++pos)
			{
				fout << f(*pos, count) << ' ';
				count++;
			}
			cout << endl << "���� ��������" << endl;
			fout.close();
		}
		else
		{
			cout << "���� �� ��������" << endl;
		}
	}

	//����� �� �����, f - �������, ������� ������� ���� ��������� �� �����  
	void OutputScreenCl(vector<Client> items, void(*f) (Client))
	{
		vector<Client>::const_iterator pos;
		_int32 count = 1;
		for (pos = items.begin(); pos != items.end(); ++pos)
		{
			cout << setw(1) << "|" << setw(6) << left << count;
			f(*pos);
			++count;
			cout << endl;
		}
		if (items.empty())
			cout << "������ ����" << endl;
	}

	//���� �� �����, f - �������, ������� ��������� ���� ��������� �� ����� 
	bool ReadFromFile(Type(*f)(ifstream&))
	{
		string newfname = InputFileName();
		ifstream input;

		input.open(newfname);

		if (!input)
		{
			cout << "���������� ������� ����" << endl;
			return false;
		}
		else
		{
			while (!input.eof())
			{
				vect.push_back(f(input));
			}
			vect.erase(vect.begin() + vect.size() - 1);

			input.close();
			return true;
		}
	}

	//���� � ������, f - �������, ������� ������ ���� ��������� � �������
	void ReadFromScreen(Type(*f)())
	{
		_int32 n;
		Type elem;
		do
		{
			Add(f());
			n = InputNumber(0, 1, "\n������ �������� ��� �������? (0 - ���, 1 - ��)\n��� �����: ");
		} while (n != 0);
	}

	//�������� �����, Equal - �������, ����������� ��������� ��-�� � ������� �� type_search
	vector<Type> LineSearch(Type search_elem, bool(*Equal)(Type, Type, int), _int32 type_search)
	{
		vector<Type> NewVect;
		for (auto iter = vect.begin(); iter != vect.end(); iter++)
		{
			if (Equal(search_elem, *iter, type_search))
				NewVect.push_back(*iter);
		}

		return NewVect;
	}

	//�������� �����, Compare - �������, ������������ ��� �������� �� type_search, Equal - �������, ����������� ��������� �������� ��-�� � ������� �� type_search
	vector<Type> BinarySearch(_int32 type_search, Type find_element, int(*Compare)(Type, Type, int), bool(*Equal)(Type, Type, int))
	{
		vector<Type> NewVect;
		Sort(vect.size(), type_search, Compare);
		_int32 left = 0;
		_int32 right = vect.size();
		_int32 index;
		if ((index = BinarySearchElement(left, right - 1, type_search, find_element, Compare)) != -1)
		{
			NewVect.push_back(vect[index]);
			_int32 first_index = index;
			while ((++index < right) && Equal(vect[index], find_element, type_search))
				NewVect.push_back(vect[index]);
			while ((--first_index >= 0) && Equal(vect[first_index], find_element, type_search))
				NewVect.push_back(vect[first_index]);
		}
		return NewVect;
	}

	Type& operator[] (_int32 index)
	{
		if (index < size())
			return c[index];	// ���������� ������
	}

	//����� �������
	_int32 SearchIndex(Type el)
	{
		string cn1 = el.getcomputerName();
		string ct1 = el.getTypeOfCPU();
		if ((vect.size() <= 0))
		{
			return -1;
		}
		for (_int32 i = 0; i < vect.size(); i++)
		{
			string cn2 = vect[i].getcomputerName();
			string ct2 = vect[i].getTypeOfCPU();
			if ((vect[i].getcapacityRAM() == el.getcapacityRAM()) && (vect[i].getcapacityHDD() == el.getcapacityHDD()) && (vect[i].getcapacityGPU() == el.getcapacityGPU())
				&& (vect[i].getcost() == el.getcost()) && (cn2 == cn1) && (ct2 == ct1) && (vect[i].getCPUfrequency() == el.getCPUfrequency()))
			{
				return i;
			}
		}
		return -1;
	}
};