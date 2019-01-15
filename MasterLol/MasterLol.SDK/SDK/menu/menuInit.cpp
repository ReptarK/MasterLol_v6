#include "menuInit.h"

#include <string>
#include "../configuration/Options.h"
#include "menu.h"
#include "../game/ListObjects.h"

string onOff[] = { "OFF", "ON" };
string colorsName[] = { "Yellow", "Turquoise", "Orange", "Green" , "Blue"};
D3DCOLOR arrColors[] = { D3DCOLOR_RGBA(150, 150, 0, 255), D3DCOLOR_RGBA(40, 165, 130, 255),
D3DCOLOR_RGBA(155, 75, 50, 255), D3DCOLOR_RGBA(100, 135, 85, 255), D3DCOLOR_RGBA(0, 0, 255, 255) };

MenuInit menuInit;
void MenuInit::init()
{
	menu.Header("MasterLol_v3");

	menu.AddTab("Hero");
	menu.AddItem("Show AA range", onOff, 2, &g_Options.show_AA_range);
	menu.AddItem("AA range Color", colorsName, GetSizeOf(colorsName), &g_Options.AA_range_color, arrColors);
	menu.AddItem("Show Q range", onOff, 2, &g_Options.show_Q_range);
	menu.AddItem("Q range Color", colorsName, GetSizeOf(colorsName), &g_Options.Q_Range_color, arrColors);
	menu.AddItem("Show W range", onOff, 2, &g_Options.show_W_range);
	menu.AddItem("E range Color", colorsName, GetSizeOf(colorsName), &g_Options.W_Range_color, arrColors);
	menu.AddItem("Show E range", onOff, 2, &g_Options.show_E_range);
	menu.AddItem("W range Color", colorsName, GetSizeOf(colorsName), &g_Options.E_Range_color, arrColors);
	menu.AddItem("Show R range", onOff, 2, &g_Options.show_R_range);
	menu.AddItem("R range Color", colorsName, GetSizeOf(colorsName), &g_Options.R_Range_color, arrColors);

	menu.AddTab("Spells");
	menu.AddItem("Auto Heal/Barrier Low Hp", onOff, 2, &g_Options.enable_auto_barrier_heal_low_hp);
	menu.AddItem("Auto Smite (Toggle Key M)", onOff, 2, &g_Options.enable_auto_smite);

	menu.AddTab("Misk");
	menu.AddItem("Show Turrets AA range", onOff, 2, &g_Options.show_Turret_AA_range);

	menu.AddTab("Tracker");
	menu.AddItem("Show Wards", onOff, 2, &g_Options.show_wards);
	menu.AddItem("Show Ennemies Spells", onOff, 2, &g_Options.show_spell_tracker);

	menu.AddTab("Debug");
	menu.AddItem("Show All Objects", onOff, 2, &g_Options.show_all_objects);
	menu.AddItem("Show Collision helper", onOff, 2, &g_Options.show_collision_helper);
	menu.AddItem("Show All Casted Spells", onOff, 2, &g_Options.show_all_spellCaster);
	menu.AddItem("Show Walls", onOff, 2, &g_Options.show_all_walls);


}

void MenuInit::initEvade()
{
	menu.AddTab("MasterEvade");
	menu.AddItem("Enable Evade", onOff, 2, &g_Options.enable_evade);

	//for (auto hero : g_listObjects.getAllAIHero())
	//{
	//	shared_ptr<Spell> listSpell[4] = { hero->getSpell(Slot::Q), hero->getSpell(Slot::W),
	//									   hero->getSpell(Slot::E), hero->getSpell(Slot::R) };
	//	for (auto spell : listSpell)
	//	{
	//		if (spell->getIsComplex())
	//			menu.AddItem(spell->getSpellData()->spellName, onOff, 2, &g_Options.enable_evade);
	//	}
	//}
}
