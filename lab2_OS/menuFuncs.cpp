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
			std::cout << "¬ыбран несуществующий пункт меню, попробуйте снова" << std::endl;
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
			std::cout << "¬ыбран несуществующий пункт меню, попробуйте снова" << std::endl;
			system("pause");
			break;
		}
	} while (menu != '0');
}

void PrintMainMenu() {
	std::cout << "1. ѕолучение информации о вычислительной системе" << std::endl
		<< "2. ќпределение статуса виртуальной пам€ти" << std::endl
		<< "3. ќпределение состо€ни€ конкретного участка пам€ти по заданному с клавиатуры адресу" << std::endl
		<< "4. –езервирование региона" << std::endl
		<< "5. «апись данных в €чейки пам€ти по заданным с клавиатуры адресам" << std::endl
		<< "6. „тение данных из €чейки пам€ти по заданным с клавиатуры адресам" << std::endl
		<< "7. ”становка защиты доступа дл€ заданного (с клавиатуры) региона пам€ти и ее проверка" << std::endl
		<< "8. ¬озврат физической пам€ти и освобождение региона адресного пространства заданного (с клавиатуры) региона пам€ти" << std::endl
		<< "0. ¬ыход" << std::endl;
}

void PrintAllocMenu() {
	std::cout << "1. –езервирование региона в автоматическом режиме" << std::endl
		<< "2. –езервирование региона в режиме ввода адреса начала региона" << std::endl
		<< "3. –езервирование региона в автоматическом режиме и передача ему физической пам€ти" << std::endl
		<< "4. –езервирование региона в режиме ввода адреса начала региона и передача ему физической пам€ти" << std::endl
		<< "0. ¬ыход" << std::endl;
}