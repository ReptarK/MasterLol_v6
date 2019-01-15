#pragma once

#define DIRECTINPUT_VERSION	0x800

#include <d3d9.h>
#include <dinput.h>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Input
{
public:
	void Init();
	void Update();

	bool IsKeyUp(int key) { return !(MouseState.rgbButtons[key] & 0x80); }
	bool IsKeyDown(int key) { return (MouseState.rgbButtons[key] & 0x80); }
	bool IsScrollUp() { return MouseState.lZ > 0; }
	bool IsScrollDown() { return MouseState.lZ < 0; }

private:
	LPDIRECTINPUTDEVICE8	lpDIMouseDevice;
	LPDIRECTINPUT8			lpDIObject;

	DIMOUSESTATE2			MouseState;
};

extern Input input;

