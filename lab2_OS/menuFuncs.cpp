#include "menuFuncs.h"

void MainMenu() {
	char menu;
	do {
		system("cls");
		PrintMainMenu();
		menu = _getch();
		system("cls");
		switch (menu)
		{
		case '1':
			SystemInfo();
			system("pause");
			break;
		case '2':
			MemoryStatus();
			system("pause");
			break;
		case '3':
			GetVirtualQuery();
			system("pause");
			break;
		case '4':
			AllocMenu();
			break;
		case '5':
			WriteDataInRegion();
			system("pause");
			break;
		case '6':
			ReadDataFromRegion();
			system("pause");
			break;
		case '7':
			SetVirtualProtect(ChooseProtect(), ChooseModProtect());
			system("pause");
			break;
		case '8':
			FreeAllocatedMemory();
			system("pause");
			break;
		case '0': break;
		default:
			std::cout << "������ �������������� ����� ����, ���������� �����" << std::endl;
			system("pause");
			break;
		}
	} while (menu != '0');
}

void AllocMenu() {
	char menu;
	do {
		system("cls");
		PrintAllocMenu();
		menu = _getch();
		system("cls");
		switch (menu)
		{
		case '1':
			AllocateMemory(1, 0);
			system("pause");
			break;
		case '2':
			AllocateMemory(0, 0);
			system("pause");
			break;
		case '3':
			AllocateMemory(1, 1);
			system("pause");
			break;
		case '4':
			AllocateMemory(0, 1);
			system("pause");
			break;
		case '0': break;
		default:
			std::cout << "������ �������������� ����� ����, ���������� �����" << std::endl;
			system("pause");
			break;
		}
	} while (menu != '0');
}

void PrintMainMenu() {
	std::cout << "1. ��������� ���������� � �������������� �������" << std::endl
		<< "2. ����������� ������� ����������� ������" << std::endl
		<< "3. ����������� ��������� ����������� ������� ������ �� ��������� � ���������� ������" << std::endl
		<< "4. �������������� �������" << std::endl
		<< "5. ������ ������ � ������ ������ �� �������� � ���������� �������" << std::endl
		<< "6. ������ ������ �� ������ ������ �� �������� � ���������� �������" << std::endl
		<< "7. ��������� ������ ������� ��� ��������� (� ����������) ������� ������ � �� ��������" << std::endl
		<< "8. ������� ���������� ������ � ������������ ������� ��������� ������������ ��������� (� ����������) ������� ������" << std::endl
		<< "0. �����" << std::endl;
}

void PrintAllocMenu() {
	std::cout << "1. �������������� ������� � �������������� ������" << std::endl
		<< "2. �������������� ������� � ������ ����� ������ ������ �������" << std::endl
		<< "3. �������������� ������� � �������������� ������ � �������� ��� ���������� ������" << std::endl
		<< "4. �������������� ������� � ������ ����� ������ ������ ������� � �������� ��� ���������� ������" << std::endl
		<< "0. �����" << std::endl;
}