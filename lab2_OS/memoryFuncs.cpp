#include "memoryFuncs.h"

std::string GetType(DWORD type) {
	switch (type)
	{
	case MEM_IMAGE: return "���� �������� ����������� ������� ������������� ��� ����������� � ������� EXE- ��� DLL-�����";
	case MEM_MAPPED: return "���� �������� ����������� ������� ������������� ��� ����������� � ������ ������, ������������ � ������";
	case MEM_PRIVATE: return "���� �������� ����������� ������� ����������� �� ���������� ������";
	default: return "��� ������";
	}
}

std::string GetState(DWORD state) {
	switch (state)
	{
	case MEM_COMMIT: return "�������� ���������� ���������, ���� � ������, ���� � ����� �������� �� �����";
	case MEM_FREE: return "��������� ��������, ����������� ��� ����������� �������� � ��������� ��� ���������";
	case MEM_RESERVE: return "����������������� ��������, �� ������� �������������� �������� ������������ ��������� ������������ �������� ��� ��������� ������-���� ����������� ���������";
	}
}

std::string GetProtect(DWORD option) {
	switch (option)
	{
	case PAGE_EXECUTE: return "����������";
	case PAGE_EXECUTE_READ: return "���������� ��� ������ ��� ������";
	case PAGE_EXECUTE_READWRITE: return "����������, ������ ��� ������ ��� ��� ������ � ������";
	case PAGE_EXECUTE_WRITECOPY: return "����������, ������ ��� ������ ��� ��� ����������� ��� ������";
	case PAGE_NOACCESS: return "����������";
	case PAGE_READONLY: return "������ ��� ������";
	case PAGE_READWRITE: return "������ ��� ������ ��� ��� ������ � ������";
	case PAGE_WRITECOPY: return "������ ��� ������ ��� ��� ����������� ��� ������";
	case PAGE_TARGETS_INVALID: return "������������ ���� ��� ������������";
	}
}

std::string GetModProtect(DWORD option) {
	switch (option)
	{
	case PAGE_GUARD: return "��������";
	case PAGE_NOCACHE: return "����������";
	case PAGE_WRITECOMBINE: return "������������ ������";
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
				std::cout << "������ ������: " << GetProtect(pConst) << ' ' << GetModProtect(mPConst);
			}
		}
	}
}

void GetVirtualQuery() {
	LPVOID address;
	MEMORY_BASIC_INFORMATION info;
	std::cout << "������� ����� ��� ����������� ���������: 0x";
	std::cin >> address;
	if (!VirtualQuery(address, &info, sizeof(info))) {
		std::cout << "������ ��� ������� ��������� �������, ���: " << GetLastError();
	}
	else {
		std::cout << "������� �����: 0x" << info.BaseAddress << std::endl
			<< "���������� ������� �����: 0x" << info.AllocationBase << std::endl
			<< "������ �������: " << info.RegionSize << std::endl
			<< "���: " << GetType(info.Type) << std::endl
			<< "���������: " << GetState(info.State) << std::endl;
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
		std::cout << "������� ����� ������ �������: 0x";
		std::cin >> address;
	}
	if (physicalMem) {
		newAddress = VirtualAlloc(address, sysInfo.dwPageSize, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	}
	else {
		newAddress = VirtualAlloc(address, sysInfo.dwPageSize, MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	}
	if (!newAddress) {
		std::cout << "������ ��� ���������� ��������, ���: " << GetLastError();
	}
	else {
		std::cout << "�������� ���������, ������� �����: 0x" << newAddress << std::endl;
	}
}

void FreeAllocatedMemory() {
	LPVOID address;
	std::cout << "������� ����� ��� ������������ ���������� ������ � ��������� ������������: 0x";
	std::cin >> address;
	if (!VirtualFree(address, 0, MEM_RELEASE)) {
		std::cout << "������ ������������, ���: " << GetLastError();
	}
	else {
		std::cout << "������ ����������� �������" << std::endl;
	}
}

void WriteDataInRegion() {
	LPVOID address;
	std::string myData;
	std::cout << "������� ������: ";
	std::cin.clear();
	std::getline(std::cin, myData);
	std::cout << "������� ����� ������ �������: 0x";
	std::cin >> address;
	memcpy(address, myData.data(), myData.size());
	std::cout << "������ ������� �������" << std::endl;
}

void ReadDataFromRegion() {
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	LPVOID address;
	std::string myData;
	std::cout << "������� ����� ������ �������: 0x";
	std::cin >> address;
	myData.assign((char*)address, sysInfo.dwPageSize);
	std::cout << "������ ������� ���������: " << std::endl << myData << std::endl;
}

DWORD ChooseProtect() {
	char choice;
	std::string vars = "1234567";
	DWORD protectOptions[] = { PAGE_EXECUTE, PAGE_EXECUTE_READ, PAGE_EXECUTE_READWRITE, PAGE_NOACCESS, PAGE_READONLY, PAGE_READWRITE, PAGE_TARGETS_NO_UPDATE };
	do {
		std::cout << "�������� �������� ��������� ������ ������ ��:"
			<< std::endl << "1. ����������"
			<< std::endl << "2. ���������� ��� ������ ��� ������"
			<< std::endl << "3. ����������, ������ ��� ������ ��� ��� ����������� ��� ������" 
			<< std::endl << "4. ����������" 
			<< std::endl << "5. ������ ��� ������" 
			<< std::endl << "6. ������ ��� ������ ��� ��� ������ � ������" 
			<< std::endl << "7. ������������";
		choice = _getch();
		std::cout << std::endl << choice << std::endl;
		if (vars.find(choice) == -1) {
			std::cout << "������ �������������� ����� ����, ���������� �����" << std::endl;
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
		std::cout << "�������� �������������� ��������� ������ ������ ��:"
			<< std::endl << "1. ��������"
			<< std::endl << "2. ����������"
			<< std::endl << "3. ������������ ������"
			<< std::endl << "4. ��� ��� ���������";
		choice = _getch();
		std::cout << std::endl << choice << std::endl;
		if (vars.find(choice) == -1) {
			std::cout << "������ �������������� ����� ����, ���������� �����" << std::endl;
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
	std::cout << "������� ����� ������ �������: 0x";
	std::cin >> address;
	if (!VirtualProtect(address, sysInfo.dwPageSize, newProtOpt, &oldProtOpt)) {
		std::cout << "������ ��� ��������� ����������, ���: " << GetLastError() << std::endl;
	}
	else {
		std::cout << "��������� �������� �������" << std::endl << "������ ���������: ";
		PrintMemProtect(oldProtOpt);
		std::cout << std::endl << "����� ���������: ";
		PrintMemProtect(newProtOpt);
	}
}