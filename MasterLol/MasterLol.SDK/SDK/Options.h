#pragma once
#include <d3d9.h>

#define OPTION(type, var, val) type var = val

extern bool g_Unload;

class Config
{
public:
	// VISUALS
	OPTION( bool, show_AA_range, true );
	OPTION( bool, show_Q_range, false );
	OPTION( bool, show_W_range, false );
	OPTION( bool, show_E_range, false );
	OPTION( bool, show_R_range, false );
};

extern Config g_Options;