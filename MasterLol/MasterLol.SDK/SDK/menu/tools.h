#pragma once

#include <Windows.h>
#include <string>

using namespace std;

class Tools
{
public:
	//bool IsReadyForHook(string* ModuleList, int NumModules);
	void* DetourFunction(PBYTE src, const PBYTE dst, const int len);
	void HideModule(HINSTANCE hModule);
	void EraseHeader(HINSTANCE hModule);
};

// quantidade de elementos em um array
#define GetSizeOf(a)			sizeof(a)/sizeof(*a)

extern Tools tools;
