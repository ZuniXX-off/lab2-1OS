#pragma once
#include <string>
#include <Windows.h>

void SystemInfo();
std::string GetProcessorArchitecture(WORD);
void PrintMask(DWORD_PTR, DWORD);
void MemoryStatus();