#pragma once
#include <iostream>
#include <Windows.h>
#include <String>
#include <conio.h>

void GetVirtualQuery();
std::string GetType(DWORD);
std::string GetState(DWORD);
std::string GetProtect(DWORD);
std::string GetModProtect(DWORD);
void PrintMemProtect(DWORD);
void AllocateMemory(bool, bool);
void FreeAllocatedMemory();
void WriteDataInRegion();
void ReadDataFromRegion();
void SetVirtualProtect(DWORD, DWORD);
DWORD ChooseProtect();
DWORD ChooseModProtect();