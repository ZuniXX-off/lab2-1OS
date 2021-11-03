#include "memoryFuncs.h"

std::string GetType(DWORD type) {
	switch (type)
	{
	case MEM_IMAGE: return "Этот диапазон виртуальных адресов первоначально был сопоставлен с образом EXE- или DLL-файла";
	case MEM_MAPPED: return "Этот диапазон виртуальных адресов первоначально был сопоставлен с файлом данных, проецируемым в память";
	case MEM_PRIVATE: return "Этот диапазон виртуальных адресов сопоставлен со страничным файлом";
	default: return "Нет данных";
	}
}

std::string GetState(DWORD state) {
	switch (state)
	{
	case MEM_COMMIT: return "Выделено физическое хранилище, либо в памяти, либо в файле подкачки на диске";
	case MEM_FREE: return "Свободные страницы, недоступные для вызывающего процесса и доступные для выделения";
	case MEM_RESERVE: return "Зарезервированные страницы, на которых зарезервирован диапазон виртуального адресного пространства процесса без выделения какого-либо физического хранилища";
	}
}

std::string GetProtect(DWORD option) {
	switch (option)
	{
	case PAGE_EXECUTE: return "Выполняемо";
	case PAGE_EXECUTE_READ: return "Выполняемо или только для чтения";
	case PAGE_EXECUTE_READWRITE: return "Выполняемо, только для чтения или для чтения и записи";
	case PAGE_EXECUTE_WRITECOPY: return "Выполняемо, только для чтения или для копирования при записи";
	case PAGE_NOACCESS: return "Недоступно";
	case PAGE_READONLY: return "Только для чтения";
	case PAGE_READWRITE: return "Только для чтения или для чтения и записи";
	case PAGE_WRITECOPY: return "Только для чтения или для копирования при записи";
	case PAGE_TARGETS_INVALID: return "Недопустимые цели или необновляемо";
	}
}

std::string GetModProtect(DWORD option) {
	switch (option)
	{
	case PAGE_GUARD: return "защищено";
	case PAGE_NOCACHE: return "недоступно";
	case PAGE_WRITECOMBINE: return "объединенная запись";
	default: return "";
	}
}

void PrintMemProtect(DWORD protect) {
	DWORD protectConsts[] = { PAGE_EXECUTE, PAGE_EXECUTE_READ, PAGE_EXECUTE_READWRITE, PAGE_EXECUTE_WRITECOPY, PAGE_NOACCESS, PAGE_READONLY, 
		PAGE_READWRITE, PAGE_WRITECOPY, PAGE_TARGETS_INVALID, PAGE_TARGETS_NO_UPDATE };
	DWORD modProtectConsts[] = { PAGE_GUARD, PAGE_NOCACHE, PAGE_WRITECOMBINE, 0x0 };
	for (DWORD pConst : protectConsts) {
		for (DWORD mPConst : modProtectConsts) {
			if ((pConst | mPConst) == protect) {
				std::cout << "Защита памяти: " << GetProtect(pConst) << ' ' << GetModProtect(mPConst);
			}
		}
	}
}

void GetVirtualQuery() {
	LPVOID address;
	MEMORY_BASIC_INFORMATION info;
	std::cout << "Введите адрес для определения состояния: 0x";
	std::cin >> address;
	if (!VirtualQuery(address, &info, sizeof(info))) {
		std::cout << "Ошибка при попытке получения доступа, код: " << GetLastError();
	}
	else {
		std::cout << "Базовый адрес: 0x" << info.BaseAddress << std::endl
			<< "Выделенный базовый адрес: 0x" << info.AllocationBase << std::endl
			<< "Размер региона: " << info.RegionSize << std::endl
			<< "Тип: " << GetType(info.Type) << std::endl
			<< "Состояние: " << GetState(info.State) << std::endl;
		if (info.Protect) {
			PrintMemProtect(info.Protect);
			std::cout << std::endl;
		}
	}
}

void AllocateMemory(bool autoAlloc, bool physicalMem) {
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	void* address = nullptr,* newAddress = nullptr;
	if (!autoAlloc) {
		std::cout << "Введите адрес начала региона: 0x";
		std::cin >> address;
	}
	if (physicalMem) {
		newAddress = VirtualAlloc(address, sysInfo.dwPageSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	}
	else {
		newAddress = VirtualAlloc(address, sysInfo.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	}
	if (!newAddress) {
		std::cout << "Ошибка при выполнении операции, код: " << GetLastError();
	}
	else {
		std::cout << "Операция выполнена, базовый адрес: 0x" << newAddress << std::endl;
	}
}

void FreeAllocatedMemory() {
	LPVOID address;
	std::cout << "Введите адрес для освобождения физической памяти и адресного пространства: 0x";
	std::cin >> address;
	if (!VirtualFree(address, 0, MEM_RELEASE)) {
		std::cout << "Ошибка освобождения, код: " << GetLastError();
	}
	else {
		std::cout << "Память освобождена успешно" << std::endl;
	}
}

void WriteDataInRegion() {
	LPVOID address;
	std::string myData;
	std::cout << "Введите данные: ";
	std::cin.clear();
	std::getline(std::cin, myData);
	std::cout << "Введите адрес начала региона: 0x";
	std::cin >> address;
	memcpy(address, myData.data(), myData.size());
	std::cout << "Данные успешно введены" << std::endl;
}

void ReadDataFromRegion() {
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	LPVOID address;
	std::string myData;
	std::cout << "Введите адрес начала региона: 0x";
	std::cin >> address;
	myData.assign((char*)address, sysInfo.dwPageSize);
	std::cout << "Данные успешно прочитаны: " << std::endl << myData << std::endl;
}

DWORD ChooseProtect() {
	char choice;
	std::string vars = "1234567";
	DWORD protectOptions[] = { PAGE_EXECUTE, PAGE_EXECUTE_READ, PAGE_EXECUTE_READWRITE, PAGE_NOACCESS, PAGE_READONLY, PAGE_READWRITE, PAGE_TARGETS_NO_UPDATE };
	do {
		std::cout << "Изменить основную константу защиты памяти на:"
			<< std::endl << "1. Выполняемо"
			<< std::endl << "2. Выполняемо или только для чтения"
			<< std::endl << "3. Выполняемо, только для чтения или для копирования при записи" 
			<< std::endl << "4. Недоступно" 
			<< std::endl << "5. Только для чтения" 
			<< std::endl << "6. Только для чтения или для чтения и записи" 
			<< std::endl << "7. Необновляемо";
		choice = _getch();
		std::cout << std::endl << choice << std::endl;
		if (vars.find(choice) == -1) {
			std::cout << "Выбран несуществующий пункт меню, попробуйте снова" << std::endl;
			system("pause");
		}
	} while (vars.find(choice) == -1);
	return protectOptions[choice - 49];
} 

DWORD ChooseModProtect() {
	char choice;
	std::string vars = "1234";
	DWORD protectOptions[] = { PAGE_GUARD, PAGE_NOCACHE, PAGE_WRITECOMBINE, 0x0};
	do {
		std::cout << "Изменить дополнительную константу защиты памяти на:"
			<< std::endl << "1. Защищено"
			<< std::endl << "2. Недоступно"
			<< std::endl << "3. Объединенная запись"
			<< std::endl << "4. Без доп константы";
		choice = _getch();
		std::cout << std::endl << choice << std::endl;
		if (vars.find(choice) == -1) {
			std::cout << "Выбран несуществующий пункт меню, попробуйте снова" << std::endl;
			system("pause");
		}
	} while (vars.find(choice) == -1);
	return protectOptions[choice - 49];
}

void SetVirtualProtect(DWORD protect, DWORD modProtect) {
	SYSTEM_INFO sysInfo;
	void* address;
	DWORD newProtOpt = protect | modProtect, oldProtOpt = 0;
	GetSystemInfo(&sysInfo);
	std::cout << "Введите адрес начала региона: 0x";
	std::cin >> address;
	if (!VirtualProtect(address, sysInfo.dwPageSize, newProtOpt, &oldProtOpt)) {
		std::cout << "Ошибка при изменении параметров, код: " << GetLastError() << std::endl;
	}
	else {
		std::cout << "Параметры изменены успешно" << std::endl << "Старые параметры: ";
		PrintMemProtect(oldProtOpt);
		std::cout << std::endl << "Новые параметры: ";
		PrintMemProtect(newProtOpt);
	}
}