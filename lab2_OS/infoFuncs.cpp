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
	std::cout << "����������� ������� ����������: " << GetProcessorArchitecture(sysInfo.wProcessorArchitecture) << std::endl
		<< "������ �������� � ������������� ���������� ������ � �������������: " << sysInfo.dwPageSize << " ����" << std::endl
		<< "��������� �� ������� ����� ������, ��������� ����������� � ����������� ������������ ����������: 0x" << sysInfo.lpMinimumApplicationAddress << std::endl
		<< "��������� �� ������� ����� ������, ��������� ����������� � ����������� ������������ ����������: 0x" << sysInfo.lpMaximumApplicationAddress << std::endl
		<< "�����, �������������� ����� �����������, ������������������ � �������: ";
	PrintMask(sysInfo.dwActiveProcessorMask, sysInfo.dwNumberOfProcessors);
	std::cout << std::endl
		<< "���������� ����������� � �������: " << sysInfo.dwNumberOfProcessors << std::endl
		<< "������������� ��� ���������� ������, � ������� ����� ���� �������� ����������� ������: " << sysInfo.dwAllocationGranularity << std::endl
		<< "������� ������������-���������� ���������� �������: " << sysInfo.wProcessorLevel << std::endl
		<< "������� ������������-���������� ����������: " << sysInfo.wProcessorRevision << std::endl;
}

void MemoryStatus() {
	MEMORYSTATUSEX memStat;
	memStat.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memStat);
	std::cout << "������������ ���������� ������: " << memStat.dwMemoryLoad << "%" << std::endl
		<< "�������� ���������� ������: " << (memStat.ullAvailPhys >> 20) << " �� " << (memStat.ullTotalPhys >> 20) << " �����" << std::endl
		<< "�������� ������ ��� ��������: " << (memStat.ullAvailPageFile >> 20) << " �� " << (memStat.ullTotalPageFile >> 20) << " �����" << std::endl
		<< "�������� ����������� ������: " << (memStat.ullAvailVirtual >> 20) << " �� " << (memStat.ullTotalVirtual >> 20) << " �����" << std::endl;
}