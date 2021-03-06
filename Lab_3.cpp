/*
Реализовать виртуальный магазин ПК. Магазин должен иметь два режима работы — клиент и сотрудник (выбирается в меню).
Сотрудник имеет возможность управления магазином: добавление, редактирование, удаление моделей ПК.
Предусмотреть вывод списка моделей ПК с сортировкой и/или фильтрацией по выбранному полю.
Пользователь имеет возможность поиска ПК по заданному критерию (любое поле, для полей типа цены и объема памяти — предусмотреть ввод диапазона) и покупки выбранного ПК.
Предусмотреть хранение истории покупок и просмотр истории сотрудником.
*/

#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <Windows.h>
#include "HelpUtils.h"
#include "VectorOperations.h"
#include "Client.h"
#include "Computer.h"
using namespace std;

Task<Computer> computers;
Task<Client> clients;
Task<Computer> history;

Task<Computer> res;

//Сохранение компьютеров в файл
void SaveComputersToFile(string FileName, Task<Computer> computers)
{
	fstream file;
	file.open(FileName, ios::out | ios::binary);
	if (!file.is_open())
		throw("Файл не открыт!");
	_int32 i;
	for (i = 0; i < computers.size(); i++)
	{
		computers.getvect()[i].ComputerToFile(&file);
	}
	file.close();
}

//
void SaveClientsToFile(string FileName, Task<Client> clients)
{
	fstream file;
	file.open(FileName, ios::out | ios::binary);
	if (!file.is_open())
		throw("Файл не открыт!");
	_int32 i;
	for (_int32 i = 0; i < clients.size(); i++)
	{
		clients.getvect()[i].ClientToFile(&file);
	}
	file.close();
}

//
void LoadComputersFromFile(string FileName, Task<Computer> &computers)
{
	fstream file;
	file.open(FileName, ios::binary | ios::in);
	if (!file.is_open())
	{
		return;
	}
	bool ok;
	while (!file.eof())
	{
		Computer comp = ComputerFromFile(&file, ok);
		if (ok)
		{
			computers.Add(comp);
		}
	}
	file.close();
}

//
void LoadClientsFromFile(string FileName, Task<Client> &clients)
{
	fstream file;
	file.open(FileName, ios::binary | ios::in);
	if (!file.is_open())
	{
		return;
	}
	bool ok;
	while (!file.eof())
	{
		Client cl = ClientFromFile(&file, ok);
		if (ok)
		{
			clients.Add(cl);
		}
	}
	file.close();
}

_int32 MainMenu()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "            Компьютерный салон «Сани»" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Войти как:" << endl;
	cout << "1 - Клиент" << endl;
	cout << "2 - Администратор" << endl;
	cout << "0 - Отмена" << endl;
	cout << "--------------------------------------------------------" << endl;

	return InputNumber(0, 2, "Ваш выбор: ");
}

_int32 MenuClients()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "                         Клиент" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "Выберите номер:" << endl;
	PrintHeadClients();
	clients.OutputScreenCl(clients.getvect(), OutputScreenClient);
	cout << "0 - Назад" << endl;
	cout << "--------------------------------------------------------" << endl;

	return InputNumber(0, clients.size(), "Ваш выбор: ");
}

_int32 MenuClient(_int32 i)
{
	cout << "--------------------------------------------------------" << endl;
	PrintHeadClients();
	vector<Client> tmp;
	tmp.push_back(clients.getvect()[i]);
	clients.OutputScreenCl(tmp, OutputScreenClient);
	cout << "--------------------------------------------------------" << endl;
	cout << "1 - Поиск компьютера" << endl;
	cout << "2 - Взять компьютер" << endl;
	cout << "3 - Посмотреть каталог компьютеров" << endl;
	cout << "0 - Назад" << endl;
	cout << "--------------------------------------------------------" << endl;

	return InputNumber(0, 3, "Ваш выбор: ");
}

void MenuSearch()
{
	cout << endl;

	string a, result;
	vector<Computer> res;
	Computer elem, search_elem;
	_int32 num = InputNumber(1, 4, "Выберите тип поиска:\n1 - по типу процессора\n2 - по объему ОЗУ\n3 - по объему видеопамяти\n4 - по объему жесткого диска\n");
	search_elem = InputChangeTypeSearchComputer(num);
	res = computers.LineSearch(search_elem, SearchElement, num);
	if (res.size() != 0)
	{
		for (_int32 i = 0; i < res.size(); i++)
		{
			PrintHeadComputers();
			cout << "|" << setw(6) << left << to_string(i + 1);
			OutputScreenComputer(res[i]);
			cout << endl;
		}
	}
	else
	{
		cout << "Элементы не найдены" << endl;
	}
}

void TakeComputer(_int32 i)
{
	_int32 m;

	string a;
	vector<Computer> res;
	Computer result;
	result = InputChangeTypeSearchComputer(1);
	res = computers.LineSearch(result, SearchElement, 1);

	if (res.size() > 1)
	{
		result = InputChangeTypeSearchComputer(2);
		res = computers.LineSearch(result, SearchElement, 2);
		if (res.size() > 1)
		{
			result = InputChangeTypeSearchComputer(3);
			res = computers.LineSearch(result, SearchElement, 3);
			if (res.size() > 1)
			{
				result = InputChangeTypeSearchComputer(4);
				res = computers.LineSearch(result, SearchElement, 4);
			}
		}
	}

	if (res.size() == 0)
	{
		cout << "Такого компьютера нет." << endl;
		return;
	}
	if (res.size() == 1)
	{
		m = computers.SearchIndex(res[0]);
		if (computers.getvect()[m].SetOwner(clients.getvect()[i].getlastname(), clients.getvect()[i].getmoney()) && (computers.getvect()[m].getcount() > 0))
		{
			cout << "Компьютер приобретен" << endl;

			vector<Client> temp = clients.getvect();
			temp[i].setmoney(clients.getvect()[i].getmoney() - computers.getvect()[m].getcost());
			clients.setvect(temp)[i];

			vector<Computer> tmp = computers.getvect();
			_int32 tmpcount=tmp[m].getcount();
			tmpcount--;
			tmp[m].setcount(tmpcount);
			tmp[m].setowner(clients.getvect()[i].getlastname());
			computers.setvect(tmp)[m];

			history.Add(computers.getvect()[m]);
		}
		else
		{
			cout << "Покупка невозможна. Проверьте баланс или доступность компьютера." << endl;
			return;
		}
	}
}

_int32 MainAdmin()
{
	cout << "--------------------------------------------------------" << endl;
	cout << "                   Администрирование" << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "1 - Редактирование клиентов" << endl;
	cout << "2 - Редактирование компьютеров" << endl;
	cout << "3 - Просмотр истории продажи компьютеров" << endl;
	cout << "0 - Назад" << endl;
	cout << "--------------------------------------------------------" << endl;

	return InputNumber(0, 3, "Ваш выбор: ");
}

_int32 MenuEdit(string message)
{
	cout << "--------------------------------------------------------" << endl;
	cout << "                " << message << endl;
	cout << "--------------------------------------------------------" << endl;
	cout << "1 - Добавить" << endl;
	cout << "2 - Удалить" << endl;
	cout << "3 - Изменить" << endl;
	cout << "4 - Показать полный список" << endl;
	cout << "0 - Отмена" << endl;
	cout << "--------------------------------------------------------" << endl;

	return InputNumber(0, 4, "Ваш выбор: ");
}

void MenuEditClients()
{
	Client r;
	_int32 m;
	_int32 num = MenuEdit("Редактирование клиентов");
	char ch;
	cout << endl;

	if (num != 0)
	{
		if (num == 1)
		{
			Client temp;
			temp = InputScreenClient();
			clients.Add(temp);
		}
		else
		{
			switch (num)
			{
			case 2:
			{
				PrintHeadClients();
				clients.OutputScreenCl(clients.getvect(), OutputScreenClient);
				cout << endl;
				clients.Remove(InputNumber(1, clients.size(), "Введите номер клиента для удаления: "));
				cout << "Клиент удален." << endl;
				break;
			}
			case 3:
			{
				cout << "Введите новые данные: " << endl;
				PrintHeadClients();
				clients.OutputScreenCl(clients.getvect(), OutputScreenClient);
				cout << endl;
				_int32 num = InputNumber(1, clients.size(), "Введите номер клиента для изменения: ");
				Client elem;

				vector<Client> temp = clients.getvect();
				temp[num - 1] = elem.ChangeClient(clients.getvect()[num - 1]);
				clients.setvect(temp)[num - 1];

				cout << "Клиент изменен." << endl;
				break;
			}
			case 4:
				PrintHeadClients();
				clients.OutputScreenCl(clients.getvect(), OutputScreenClient);
				break;
			default:
				break;
			}
		}
	}
}

void MenuEditComputers()
{
	Computer b;
	_int32 m;
	_int32 num = MenuEdit("Редактирование компьютера");
	char ch;
	cout << endl;

	if (num != 0)
	{
		if (num == 1)
		{
			Computer temp;
			temp = InputScreenComputer();
			computers.Add(temp);
		}
		else
		{
			switch (num)
			{
			case 2:
			{
				PrintHeadComputers();
				computers.OutputScreenComp(computers.getvect(), OutputScreenComputer);
				computers.Remove(InputNumber(1, computers.size(), "Введите номер компьютера для удаления: "));
				cout << "Компьютер удален." << endl;
				break;
			}
			case 3:
			{
				cout << "Введите новые данные: " << endl;
				PrintHeadComputers();
				computers.OutputScreenComp(computers.getvect(), OutputScreenComputer);
				_int32 num = InputNumber(1, computers.size(), "Введите номер компьютера для изменения: ");
				Computer elem;

				vector<Computer> temp = computers.getvect();
				temp[num - 1] = elem.ChangeComputer(computers.getvect()[num - 1]);
				computers.setvect(temp)[num - 1];

				cout << "Компьютер изменен." << endl;
				break;
			}
			case 4:
				PrintHeadComputers();
				computers.OutputScreenComp(computers.getvect(), OutputScreenComputer);
				break;
			default:
				break;
			}
		}
	}
}

//
_int32 main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	LoadComputersFromFile("Computers.dat", computers);
	LoadClientsFromFile("Clients.dat", clients);
	LoadComputersFromFile("History.dat", history);

	_int32 i, it, mode;


	do
	{
		mode = MainMenu();
		switch (mode)
		{
		case 1:
		{
			cout << endl << "Вы вошли как покупатель." << endl << endl;
			do {
				i = MenuClients();
				cout << endl;
				if (i != 0)
				{
					do
					{
						/*PrintHeadComputers();
						computers.OutputScreenComp(computers.getvect(), OutputScreenComputer);*/
						it = MenuClient(i - 1);
						cout << endl;
						switch (it)
						{
						case 1:
						{
							cout << "Результат поиска:" << endl;
							MenuSearch();
							break;
						}
						break;
						case 2:
						{
							TakeComputer(i - 1);
							cout << endl;
							break;
						}
						case 3:
						{
							PrintHeadComputers();
							computers.OutputScreenComp(computers.getvect(), OutputScreenComputer);
							break;
						}
						default:
							break;
						}
						SaveComputersToFile("Computers.dat", computers);
						SaveClientsToFile("Clients.dat", clients);
						SaveComputersToFile("history.dat", history);
					} while (it != 0);
				}
			} while (i != 0);
		}
		break;
		case 2:
		{
			cout << endl << "Вы вошли как администратор." << endl << endl;
			do
			{
				it = MainAdmin();
				cout << endl;
				switch (it)
				{
				case 1:
				{
					MenuEditClients();
					cout << endl;
					break;
				}
				case 2:
				{
					MenuEditComputers();
					cout << endl;
					break;
				}
				case 3:
				{
					PrintFullHeadComputers();
					history.OutputFullScreenComp(history.getvect(), OutputFullScreenComputer);
					cout << endl;
				}
				break;
				default:
					break;
				}
				SaveComputersToFile("Computers.dat", computers);
				SaveClientsToFile("Clients.dat", clients);
				SaveComputersToFile("history.dat", history);
			} while (it != 0);
			break;
		}
		break;
		default:
		{
			SaveComputersToFile("Computers.dat", computers);
			SaveClientsToFile("Clients.dat", clients);
			SaveComputersToFile("history.dat", history);
			exit(0);
		}
		break;
		}
	} while (mode != 0);
	return 0;
}
