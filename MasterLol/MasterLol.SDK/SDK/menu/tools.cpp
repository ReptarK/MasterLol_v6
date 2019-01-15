#include "stdafx.h"
#include "tools.h"

Tools tools;

//bool Tools::IsReadyForHook(string* moduleList, int numModules)
//{
//	for (int moduleIndex = 0; moduleIndex < numModules; moduleIndex++)
//	{
//		if (GetModuleHandle(moduleList[moduleIndex].c_str()) != NULL)
//		{
//			if (moduleIndex == numModules - 1)
//				return true;
//		}
//		else
//			return false;
//	}
//
//	return false;
//}

void* Tools::DetourFunction(PBYTE src, const PBYTE dst, const int len)
{
	BYTE* jmp = (BYTE*)malloc(len + 5);
	DWORD dwBack;
	VirtualProtect(src, len, PAGE_EXECUTE_READWRITE, &dwBack);
	memcpy(jmp, src, len);	
	jmp += len;
	jmp[0] = 0xE9;
	*(DWORD*)(jmp + 1) = (DWORD)(src + len - jmp) - 5;
	memset(src, 0x90, len);
	src[0] = 0xE9;
	*(DWORD*)(src + 1) = (DWORD)(dst - src) - 5;
	for (int i = 5; i < len; i++)
		src[i] = 0x90;
	VirtualProtect(src, len, dwBack, &dwBack);
	FlushInstructionCache(GetCurrentProcess, src, len);	//
	return (jmp - len);
}

void Tools::HideModule(HINSTANCE hModule)
{
	DWORD dwPEB_LDR_DATA = 0;
	_asm
	{
		pushad;
		pushfd;
		mov eax, fs:[30h];
		mov eax, [eax+0Ch];
		mov dwPEB_LDR_DATA, eax;
		mov esi, [eax+0Ch];
		mov edx, [eax+10h];
LoopInLoadOrderModuleList:
		lodsd;
		mov esi, eax;
		mov ecx, [eax+18h];
		cmp ecx, hModule;
		jne SkipA
			mov ebx, [eax]
		mov ecx, [eax+4]
		mov [ecx], ebx
			mov [ebx+4], ecx
			jmp InMemoryOrderModuleList
SkipA:
		cmp edx, esi
			jne LoopInLoadOrderModuleList
InMemoryOrderModuleList:
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax+14h]
		mov edx, [eax+18h]
LoopInMemoryOrderModuleList:
		lodsd
			mov esi, eax
			mov ecx, [eax+10h]
		cmp ecx, hModule
			jne SkipB
			mov ebx, [eax]
		mov ecx, [eax+4]
		mov [ecx], ebx
			mov [ebx+4], ecx
			jmp InInitializationOrderModuleList
SkipB:
		cmp edx, esi
			jne LoopInMemoryOrderModuleList
InInitializationOrderModuleList:
		mov eax, dwPEB_LDR_DATA
			mov esi, [eax+1Ch]
		mov edx, [eax+20h]
LoopInInitializationOrderModuleList:
		lodsd
			mov esi, eax      
			mov ecx, [eax+08h]
		cmp ecx, hModule      
			jne SkipC
			mov ebx, [eax]
		mov ecx, [eax+4]
		mov [ecx], ebx
			mov [ebx+4], ecx
			jmp Finished
SkipC:
		cmp edx, esi
			jne LoopInInitializationOrderModuleList
Finished:
		popfd;
		popad;
	}
}

void Tools::EraseHeader(HINSTANCE hModule)
{
	if (!hModule)
		return;

	DWORD size, protect;
	PIMAGE_DOS_HEADER pDoH = (PIMAGE_DOS_HEADER)(hModule);
	PIMAGE_NT_HEADERS pNtH = (PIMAGE_NT_HEADERS)((LONG)hModule + ((PIMAGE_DOS_HEADER)hModule)->e_lfanew);

	size = sizeof(IMAGE_DOS_HEADER);
	if (VirtualProtect(pDoH, size, PAGE_READWRITE, &protect))
		for (DWORD i = 0; i < size; i++)
			*(BYTE*)((BYTE*)pDoH + i) = 0;

	size = sizeof(IMAGE_NT_HEADERS);
	if (pNtH && VirtualProtect(pNtH, size, PAGE_READWRITE, &protect))
		for (DWORD i = 0; i < size; i++)
			*(BYTE*)((BYTE*)pNtH + i) = 0;

	return;
}