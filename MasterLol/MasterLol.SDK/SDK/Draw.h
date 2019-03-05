#ifndef _DRAW_H_
#define _DRAW_H_
#pragma comment(lib, "d3dx9.lib")

#include "stdafx.h"

#include <d3d9.h>
#include <d3dx9.h>
#include "colors_define.h"
#include "math/Vector.hpp"

enum circle_type { full, half, quarter };
enum text_alignment { lefted, centered, righted };

#define MAX_FONTS 6

struct vertex
{
	FLOAT x, y, z, rhw;
	DWORD color;
};

class Render_struct
{
public:
	char pad_0000[24]; //0x0000
	int32_t screenResolutionX; //0x0018
	int32_t screenResolutionY; //0x001C
	char pad_0020[68]; //0x0020
	D3DMATRIX viewMatrix; //0x0064 Starts with 1.0000 and is before a position vector3
	D3DMATRIX projMatrix; //0x00A4
}; //Size=0x010C

class CDraw
{
public:
	CDraw()
	{
		g_pVB = NULL;
		g_pIB = NULL;
		int FontNr = 0;
	}

	struct sScreen
	{
		float Width;
		float Height;
		float x_center;
		float y_center;
	} Screen;

	ID3DXFont *pFont[MAX_FONTS];

	// GAME FUNCTION
	void RangeCircle( Vector3 position, float range, D3DCOLOR color, int a4, float a5, int a6, float alpha );
	void RangeCircle( Vector3 position, float range, D3DCOLOR color, float alpha );

	bool WorldToScreen( Vector3 world, Vector3* screen );

	void Sprite( LPDIRECT3DTEXTURE9 tex, float x, float y, float resolution, float scale, float rotation );

	//=============================================================================================
	void Line( float x1, float y1, float x2, float y2, float width, bool antialias, DWORD color );
	void Line( Vector3 source, Vector3 dest, float gameWidth, DWORD color );

	void Box( float x, float y, float w, float h, float linewidth, DWORD color );
	void BoxFilled( float x, float y, float w, float h, DWORD color );
	void BoxBordered( float x, float y, float w, float h, float border_width, DWORD color, DWORD color_border );
	void BoxRounded( float x, float y, float w, float h, float radius, bool smoothing, DWORD color, DWORD bcolor );

	void Circle( float x, float y, float radius, int rotate, int type, bool smoothing, int resolution, DWORD color );
	void Circle( Vector3 pos, float gameRadius, D3DCOLOR );
	void CircleFilled( float x, float y, float rad, float rotate, int type, int resolution, DWORD color );
	void CircleFilled( Vector3 pos, float gameRadius, D3DCOLOR );

	void Text( char *text, float x, float y, int orientation, int font, bool bordered, DWORD color, DWORD bcolor );
	void Message( char *text, float x, float y, int font, int orientation );
	void Message( int fontId, unsigned int x, unsigned int y, D3DCOLOR color, LPCSTR Message );
	//=============================================================================================

	//=============================================================================================
	bool Font();
	void AddFont( char* Caption, float size, bool bold, bool italic );
	void FontReset();
	void FontRelease();
	void OnLostDevice();
	//=============================================================================================

	void setDevice( LPDIRECT3DDEVICE9 pDev ) { pDevice = pDev; }
	LPDIRECT3DDEVICE9 getDevice() { return pDevice; }

	void Reset();
	int FontNr;
private:
	LPDIRECT3DDEVICE9 pDevice;
	LPDIRECT3DVERTEXBUFFER9 g_pVB;    // Buffer to hold vertices
	LPDIRECT3DINDEXBUFFER9  g_pIB;    // Buffer to hold indices


	LPD3DXSPRITE sSprite;
};

extern CDraw Draw;

#endif /* _DRAW_H_ */