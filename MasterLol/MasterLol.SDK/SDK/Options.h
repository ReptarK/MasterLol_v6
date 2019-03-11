#pragma once
#include <d3d9.h>

#define OPTION(type, var, val) type var = val

extern bool g_Unload;

class Config
{
public:
	// VISUALS
	OPTION(bool, show_AA_range, true);
	OPTION(bool, show_Q_range, false);
	OPTION(bool, show_W_range, false);
	OPTION(bool, show_E_range, false);
	OPTION(bool, show_R_range, false);

	OPTION(bool, show_turrets_AA_range, true);

	// SUMMONER SPELLS
	OPTION(bool, enable_auto_smite, false);
	OPTION(bool, smite_blue, false);
	OPTION(bool, smite_red, false);
	OPTION(bool, smite_dragon, false);
	OPTION(bool, smite_baron, false);


	// DEBUG
	OPTION(bool, enable_debug_collision, false);
	OPTION(bool, show_lasthit_targets, false);
};

extern Config g_Options;