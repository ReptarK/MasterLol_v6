#pragma once
#include "stdafx.h"
#include "Utilities.h"

bool Utils::isProcessRunning(const wchar_t *processName)
{
	return true;
}

// PATTERN SCANNING
bool PatternScanning::bCompare(const BYTE * pData, const BYTE * bMask, const char * szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;

	return (*szMask) == NULL;
}

DWORD PatternScanning::FindPattern(DWORD dwAddress, DWORD dwLen, BYTE * bMask, const char * szMask)
{
	for (DWORD i = 0; i < dwLen; i++)
		if (bCompare((BYTE*)(dwAddress + i), bMask, szMask))
			return (DWORD)(dwAddress + i);

	return 0;
}
//////////////////
