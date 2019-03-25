#pragma once
#include <d3d9.h>
#include <SDK/singleton.hpp>
#include <SDK/Draw.h>

#define OPTION(type, var, val) type var = val

class Option : public Singleton<Option>
{
	friend class Singleton<Option>;

	Option() {}
	~Option() {}

public:
	// VISUALS
	OPTION(bool, show_AA_range, true);
	OPTION(bool, show_Q_range, false);
	OPTION(bool, show_W_range, false);
	OPTION(bool, show_E_range, false);
	OPTION(bool, show_R_range, false);

	OPTION(bool, show_turrets_AA_range, true);

	OPTION(bool, enable_cooldown_tracker, false);

	// SUMMONER SPELLS
	OPTION(bool, enable_auto_smite, false);
	OPTION(ImColor, smite_range_color, ImColor(90, 190, 60));
	OPTION(bool, smite_blue, false);
	OPTION(bool, smite_red, false);
	OPTION(bool, smite_dragon, false);
	OPTION(bool, smite_baron, false);


	// DEBUG
	OPTION(bool, enable_debug_collision, false);
	OPTION(bool, enable_debug_navigation, true);
	OPTION(bool, enable_debug_prediction, false);
	OPTION(bool, log_process_spell_hero, false);
	OPTION(bool, log_missile, false);
	OPTION(bool, show_lasthit_targets, false);
	OPTION(bool, show_debug_missile, false);
	OPTION(bool, show_process_spell, false);
};
