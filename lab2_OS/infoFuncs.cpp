#include "infoFuncs.h"
#include <iostream>

std::string GetProcessorArchitecture(WORD processorArchitecture) {
	switch (processorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_AMD64: return "x64(AMD or Intel)";
	case PROCESSOR_ARCHITECTURE_ARM: return "ARM";
	case PROCESSOR_ARCHITECTURE_ARM64: return "ARM64";
	case PROCESSOR_ARCHITECTURE_IA64: return "Intel Itanium-based";
	case PROCESSOR_ARCHITECTURE_INTEL: return "x86";
	default: return "Unknown architecture";
	}
}

void PrintMask(DWORD_PTR mask, DWORD numberOfProcessors) {
	for (int i = numberOfProcessors - 1; i > 0; --i) {
		std::cout << (mask & ((uint64_t)1 << i) ? '1' : '0');
	}
}

void SystemInfo() {
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	std::cout << "Архитектура системы процессора: " << GetProcessorArchitecture(sysInfo.wProcessorArchitecture) << std::endl
		<< "Размер страницы и гранулярность страничной защиты и обязательства: " << sysInfo.dwPageSize << " байт" << std::endl
		<< "Указатель на младший адрес памяти, доступный приложениям и библиотекам динамической компоновки: 0x" << sysInfo.lpMinimumApplicationAddress << std::endl
		<< "Указатель на старший адрес памяти, доступный приложениям и библиотекам динамической компоновки: 0x" << sysInfo.lpMaximumApplicationAddress << std::endl
		<< "Маска, представляющая набор процессоров, сконфигурированных в системе: ";
	PrintMask(sysInfo.dwActiveProcessorMask, sysInfo.dwNumberOfProcessors);
	std::cout << std::endl
		<< "Количество процессоров в системе: " << sysInfo.dwNumberOfProcessors << std::endl
		<< "Гранулярность для начального адреса, в котором может быть выделена виртуальная память: " << sysInfo.dwAllocationGranularity << std::endl
		<< "Уровень архитектурно-зависимого процессора системы: " << sysInfo.wProcessorLevel << std::endl
		<< "Ревизия архитектурно-зависимого процессора: " << sysInfo.wProcessorRevision << std::endl;
}

void MemoryStatus() {
	MEMORYSTATUSEX memStat;
	memStat.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memStat);
	std::cout << "Использовано физической памяти: " << memStat.dwMemoryLoad << "%" << std::endl
		<< "Доступно физической памяти: " << (memStat.ullAvailPhys >> 20) << " из " << (memStat.ullTotalPhys >> 20) << " МБайт" << std::endl
		<< "Доступно памяти для фиксации: " << (memStat.ullAvailPageFile >> 20) << " из " << (memStat.ullTotalPageFile >> 20) << " МБайт" << std::endl
		<< "Доступно виртуальной памяти: " << (memStat.ullAvailVirtual >> 20) << " из " << (memStat.ullTotalVirtual >> 20) << " МБайт" << std::endl;
}