#pragma once

#include <Windows.h>
#include <string>
#include <map>
#include <vector>
#include <mutex>
#include "menuDraw.h"
#include "input.h"
#include "menuItems.h"
#include "../StaticEnums.h"

namespace ItemArrays
{
	static string onOff[] = { "OFF", "ON" };
	static string colorsName[] = { "Yellow", "Turquoise", "Orange", "Green" , "Blue" };
	static string priorityName[] = { "Unknown", "Lowest", "Low", "Medium", "High" , "Highest" };
	static D3DCOLOR arrColors[] = { D3DCOLOR_RGBA(150, 150, 0, 255)/*Yellow*/, D3DCOLOR_RGBA(40, 165, 130, 255)/*Turquoise*/,
		D3DCOLOR_RGBA(155, 75, 50, 255)/*Orange*/, D3DCOLOR_RGBA(100, 135, 85, 255)/*Green*/, D3DCOLOR_RGBA(0, 0, 255, 255)/*Blue*/ };
}

class Menu
{
public:
	Menu();

	void AddTab(string name);
	void AddItem(string name, string* arrDisplay, int max = 2, bool* pOption = nullptr);
	void AddItem(string name, string* arrDisplay, int max = 2, D3DCOLOR* pColor = nullptr, D3DCOLOR* arrColors = nullptr, int value = 0);
	void AddItem(string name, Priority::Priority *);
	void Header(string title) { menuInfo.title = title; }
	void Render();
	bool IsShown() { return menuInfo.isShown; }

	struct MenuInfo { string title; int x; int y; int w; D3DCOLOR color; bool isDragging; bool isShown; bool isInitialized; } menuInfo;

	vector<std::shared_ptr<Item>> items;

	void Initialize();
private:
	void MouseSetup();
	void MouseNavigation(int itemIndex);
	void MouseScrollNavigation(float x, float y, float w, float h);
	//void KeyboardNavigation();

	void DrawSelection(int x, int y, int w);
	void DrawTabs(int x, int y, int w, int h);
	void DrawItems(int x, int y, int w);
	void DrawScrollBar(int x, int y, int h);
	void DrawColors(int x, int y, int w, int h);
	void DragMenu(int x, int y, int w, int h);

	struct CursorInfo { POINT pos; POINT offset; bool isLClicked; bool isRClicked; bool isHolding; } c;
	struct ItemInfo { int num; int index; } itemInfo, tabInfo, scrollInfo, colorInfo;

	struct MenuTab { string name; int pos; } tabs[8];

	// update item index and scroll
	void Update() { itemInfo.index = 0; scrollInfo.index = 0; }

	// items and tabs
	int FirstTabIndex() { return tabs[tabInfo.index].pos; }// first index of the tab
	int LastTabIndex() { if (tabInfo.num > tabInfo.index + 1) return tabs[tabInfo.index + 1].pos - 1; else return itemInfo.num - 1; }	// last tab index
	int NumTabItems() { int num = 0; for (int i = this->FirstTabIndex(); i <= this->LastTabIndex(); i++) num++; return num; }			// quantity of items on the tab

																																		// scroll
	bool HasScroll() { return (this->NumTabItems() > scrollInfo.num); } // current tab has scroll
	int NumScrollItems() { return (this->NumTabItems() - scrollInfo.num); }	// maximum number of items in a scroll
	int NumScrollHideItems() { return (this->HasScroll() ? (this->NumScrollItems() - scrollInfo.index) : 0); }	// quantity of items not visible
	int FirstScrollIndex() { return (this->FirstTabIndex() + scrollInfo.index); }// initial index as a base on the scroll index
	int LastScrollIndex() { return (this->LastTabIndex() - this->NumScrollHideItems()); }// final index based on non-visible items

																						 // cursor
	bool IsLClicked() { return this->c.isLClicked; }
	bool IsRClicked() { return this->c.isRClicked; }
	bool IsHolding() { return this->c.isHolding; }

	// check if the cursor is over the given region
	bool IsMouseOver(float x, float y, float w, float h)
	{
		return (c.pos.x > x && c.pos.x < x + w && c.pos.y > y && c.pos.y < y + h);
	}
};

extern Menu menu;



