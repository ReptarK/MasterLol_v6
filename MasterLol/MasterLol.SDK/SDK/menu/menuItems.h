#pragma once
#include <string>
#include "../colors_define.h"
#include "../StaticEnums.h"

class Item
{
public:
	string _name;
	string* _arrDisplay;
	int _maxVal;
	int _value;

    Item(string name, string* arrDisplay, int maxVal, int value)
        :_name(name),
        _arrDisplay(arrDisplay),
		_maxVal(maxVal),
        _value(value){ }

	virtual D3DCOLOR getColor(D3DCOLOR ON_color, D3DCOLOR OFF_color) { return OFF_color; }

	virtual void left_click_event()
	{
		if (_value < _maxVal)
			_value++;
		else
			_value = 0;
	}

	virtual void right_click_event(){}
};

class Item_toggle : public Item
{
public:
    Item_toggle(string name, string* arrDisplay, int maxVal, int value, bool* pOption)
        :Item(name, arrDisplay, maxVal, value), _pOption(pOption){}

	virtual D3DCOLOR getColor(D3DCOLOR ON_color, D3DCOLOR OFF_color)
	{
		return *_pOption ? ON_color : OFF_color;
	}

    virtual void left_click_event()
    {
		Item::left_click_event();
        *_pOption = !(*_pOption);
    }

    bool* _pOption;
};

class Item_color : public Item
{
public:
	Item_color(string name, string* arrDisplay, int maxVal, int value, D3DCOLOR* pColor, D3DCOLOR* arrColors)
		:Item(name, arrDisplay, maxVal, value),_pColor(pColor), _arrColors(arrColors) {}

	virtual D3DCOLOR getColor(D3DCOLOR ON_color, D3DCOLOR OFF_color)
	{
		return _arrColors[_value];
	}

	virtual void left_click_event()
	{
		Item::left_click_event();
		*_pColor = _arrColors[_value];
	}

	D3DCOLOR* _pColor;
	D3DCOLOR* _arrColors;
};

class Item_priority : public Item
{
public:
	Item_priority(string name, string arrDisplay[], Priority::Priority* priority)
		:Item(name, arrDisplay, 0, (int)*priority), _priority(priority) {}

	virtual D3DCOLOR getColor(D3DCOLOR ON_color, D3DCOLOR OFF_color)
	{
		return WHITE(180);
	}

	virtual void left_click_event()
	{
		if (++_value >= Priority::COUNT)
			_value = Priority::Lowest;
		*_priority = (Priority::Priority)_value;
	}

	virtual void right_click_event()
	{
		if (--_value <= 0)
			_value = Priority::Highest;
		*_priority = (Priority::Priority)_value;
	}

	Priority::Priority* _priority;
};