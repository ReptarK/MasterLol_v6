#pragma once
#include <d3d9.h>

#define OPTION(type, var, val) type var = val

extern bool g_Unload;

class Config
{
public:
	OPTION(bool, show_AA_range, true);
};

extern Config g_Options;