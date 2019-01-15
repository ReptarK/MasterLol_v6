#include "stdafx.h"
#include "Patchables.h"
#include "Utilities.h"

void Patchables::InitializePointers()
{
	LolBase = (DWORD)GetModuleHandle(NULL);
}

bool Patchables::Initialize()
{
	InitializePointers();
	return LolBase;
}

unsigned long Patchables::LolBase;
