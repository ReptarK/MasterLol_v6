#pragma once

class Utils
{
public:
	static bool isProcessRunning(const wchar_t *processName);
};

class PatternScanning
{
public:
	static bool bCompare(const BYTE* pData, const BYTE* bMask, const char* szMask);
	static DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE *bMask, const char * szMask);
};
