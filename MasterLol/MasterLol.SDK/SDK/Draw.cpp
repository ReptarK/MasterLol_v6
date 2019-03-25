#include "stdafx.h"
#include "Draw.h"

CDraw Draw;

void CDraw::Reset()
{
	D3DVIEWPORT9 screen;
	pDevice->GetViewport(&screen);

	Screen.Width = (float)screen.Width;
	Screen.Height = (float)screen.Height;
	Screen.x_center = Screen.Width / 2;
	Screen.y_center = Screen.Height / 2;
}

typedef void(__cdecl* _fnDrawCircle)(Vector3 * position, float range, int * color, int a4, float a5, int a6, float alpha);
void CDraw::RangeCircle(Vector3 position, float range, D3DCOLOR color, int a4, float a5, int a6, float alpha)
{
	_fnDrawCircle originalDrawCircle = (_fnDrawCircle)(Patchables::LolBase + fnDrawCircle);
	return originalDrawCircle(&position, range, (int*)&color, a4, a5, a6, alpha);
}

void CDraw::RangeCircle(Vector3 position, float range, D3DCOLOR color, float alpha)
{
	return RangeCircle(position, range, color, 0, 0, 0, alpha);
}

void CDraw::RangeCircle(Vector3 position, float range, ImColor color, float alpha)
{
	D3DCOLOR d3dColor = D3DCOLOR_RGBA(
		(UINT8)(color.Value.x * 255),
		(UINT8)(color.Value.y * 255),
		(UINT8)(color.Value.z * 255),
		255);

	Draw.RangeCircle(position, range, d3dColor, alpha);
}

//int __cdecl sub_AA3E20(int a1, int a2)
bool CDraw::WorldToScreen(Vector3 world, Vector3 * screen)
{
	typedef int(__cdecl* _fnWorldToScreen)(Vector3* world, Vector3* screen);
	static _fnWorldToScreen oWorldToScreen = (_fnWorldToScreen)(Patchables::LolBase + fnWorldToScreen);
	return oWorldToScreen(&world, screen);

	//screen->x = 0; screen->y = 0; screen->z = 0;
	//DWORD pRender = 0;
	//pRender = *(DWORD*)(Patchables::LolBase + oRenderer);
	//Render_struct* render = (Render_struct*)(pRender);

	//D3DXMATRIX viewMatrix = render->viewMatrix;
	//D3DXMATRIX projectionMatrix = render->projMatrix;
	//D3DXMATRIX viewProjectionMatrix = D3DXMATRIX();
	//D3DXMatrixMultiply(&viewProjectionMatrix, &viewMatrix, &projectionMatrix);

	//D3DXVECTOR3 pScreen = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//D3DXVECTOR3 pOrigin(world.x, world.y, world.z);
	//int width = render->screenResolutionX;
	//int heigth = render->screenResolutionY;

	//D3DXVec3TransformCoord(&pScreen, &pOrigin, &viewProjectionMatrix);
	//*screen = Vector3(float((1 + pScreen.x) * 0.5 * width), float((1 - pScreen.y) * 0.5 * heigth), 0);

	//return screen->x < width && screen->x > 0 && screen->y < heigth && screen->y > 0;
}

void CDraw::Line(float x1, float y1, float x2, float y2, float width, bool antialias, DWORD color)
{
	ID3DXLine *m_Line;

	D3DXCreateLine(pDevice, &m_Line);
	D3DXVECTOR2 line[] = { D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2) };
	m_Line->SetWidth(width);
	if (antialias) m_Line->SetAntialias(1);
	m_Line->Begin();
	m_Line->Draw(line, 2, color);
	m_Line->End();
	m_Line->Release();
}

void CDraw::Line(Vector3 source, Vector3 dest, float gameWidth, DWORD color)
{
	Vector3 sourceScreen, destScreen;
	bool cond1 = WorldToScreen(source, &sourceScreen);
	bool cond2 = WorldToScreen(dest, &destScreen);
	if (cond1 || cond2)
		Draw.Line(sourceScreen.x, sourceScreen.y, destScreen.x, destScreen.y, gameWidth, true, color);
}


void CDraw::Circle(float x, float y, float radius, int rotate, float circumferenceRatio, bool smoothing, int resolution, DWORD color)
{
	std::vector<vertex> circle(resolution + 2);
	float angle = rotate * D3DX_PI / 180;
	float pi = D3DX_PI * circumferenceRatio;

	for (int i = 0; i < resolution + 2; i++)
	{
		circle[i].x = (float)(x - radius * cos(i*(2 * pi / resolution)));
		circle[i].y = (float)(y - radius * sin(i*(2 * pi / resolution)));
		circle[i].z = 0;
		circle[i].rhw = 1;
		circle[i].color = color;
	}

	// Rotate matrix
	int _res = resolution + 2;
	for (int i = 0; i < _res; i++)
	{
		circle[i].x = x + cos(angle)*(circle[i].x - x) - sin(angle)*(circle[i].y - y);
		circle[i].y = y + sin(angle)*(circle[i].x - x) + cos(angle)*(circle[i].y - y);
	}

	pDevice->CreateVertexBuffer((resolution + 2) * sizeof(vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL);

	VOID* pVertices;
	g_pVB->Lock(0, (resolution + 2) * sizeof(vertex), (void**)&pVertices, 0);
	memcpy(pVertices, &circle[0], (resolution + 2) * sizeof(vertex));
	g_pVB->Unlock();


	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(NULL);
	if (smoothing)
	{
		pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
		pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
	}
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetStreamSource(0, g_pVB, 0, sizeof(vertex));
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, resolution);
	if (g_pVB != NULL) g_pVB->Release();
}

void CDraw::Circle(float x, float y, float radius, int rotate, int type, bool smoothing, int resolution, DWORD color)
{
	float circumferenceRatio;
	if (type == full) circumferenceRatio = 1.0f;			// Full circle
	if (type == half) circumferenceRatio = 1 / 2.0f;		// 1/2 circle
	if (type == quarter) circumferenceRatio = 1 / 4.0f;		// 1/4 circle

	this->Circle(x, y, radius, rotate, circumferenceRatio, smoothing, resolution, color);
}

void CDraw::Circle(Vector3 pos, float gameRadius, D3DCOLOR color)
{
	Vector3 u, v;
	bool cond1 = WorldToScreen(pos, &u);
	bool cond2 = WorldToScreen(pos + Vector3(0, 0, gameRadius), &v);
	float screenRadius = u.DistTo(v);
	if (cond1 || cond2)
		Circle(u.x, u.y, screenRadius, 0, full, 1, 32, color);
}

void CDraw::CircleFilled(float x, float y, float rad, float rotate, float circumferenceRatio, int resolution, DWORD color)
{
	std::vector<vertex> circle(resolution + 2);
	float angle = rotate * D3DX_PI / 180;
	float pi = D3DX_PI * circumferenceRatio;

	circle[0].x = x;
	circle[0].y = y;
	circle[0].z = 0;
	circle[0].rhw = 1;
	circle[0].color = color;

	for (int i = 1; i < resolution + 2; i++)
	{
		circle[i].x = (float)(x - rad * cos(pi*((i - 1) / (resolution / 2.0f))));
		circle[i].y = (float)(y - rad * sin(pi*((i - 1) / (resolution / 2.0f))));
		circle[i].z = 0;
		circle[i].rhw = 1;
		circle[i].color = color;
	}

	// Rotate matrix
	int _res = resolution + 2;
	for (int i = 0; i < _res; i++)
	{
		circle[i].x = x + cos(angle)*(circle[i].x - x) - sin(angle)*(circle[i].y - y);
		circle[i].y = y + sin(angle)*(circle[i].x - x) + cos(angle)*(circle[i].y - y);
	}

	pDevice->CreateVertexBuffer((resolution + 2) * sizeof(vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL);

	VOID* pVertices;
	g_pVB->Lock(0, (resolution + 2) * sizeof(vertex), (void**)&pVertices, 0);
	memcpy(pVertices, &circle[0], (resolution + 2) * sizeof(vertex));
	g_pVB->Unlock();

	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(NULL);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetStreamSource(0, g_pVB, 0, sizeof(vertex));
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->DrawPrimitive(D3DPT_TRIANGLEFAN, 0, resolution);
	if (g_pVB != NULL) g_pVB->Release();
}

void CDraw::CircleFilled(float x, float y, float rad, float rotate, int type, int resolution, DWORD color)
{
	float circumferenceRatio;
	if (type == full) circumferenceRatio = 1.0f;			// Full circle
	if (type == half) circumferenceRatio = 1 / 2.0f;		// 1/2 circle
	if (type == quarter) circumferenceRatio = 1 / 4.0f;		// 1/4 circle

	this->CircleFilled(x, y, rad, rotate, circumferenceRatio, resolution, color);
}

void CDraw::CircleFilled(Vector3 pos, float gameRadius, D3DCOLOR color)
{
	Vector3 u, v;
	bool cond1 = WorldToScreen(pos, &u);
	bool cond2 = WorldToScreen(pos + Vector3(0, 0, gameRadius), &v);
	float screenRadius = u.DistTo(v);
	if (cond1 || cond2)
		CircleFilled(u.x, u.y, screenRadius, 0, full, 20, color);
}

void CDraw::Box(float x, float y, float w, float h, float linewidth, DWORD color)
{
	if (linewidth == 0 || linewidth == 1)
	{
		BoxFilled(x, y, w, 1, color);             // Top
		BoxFilled(x, y + h - 1, w, 1, color);         // Bottom
		BoxFilled(x, y + 1, 1, h - 2 * 1, color);       // Left
		BoxFilled(x + w - 1, y + 1, 1, h - 2 * 1, color);   // Right
	}
	else
	{
		BoxFilled(x, y, w, linewidth, color);                                     // Top
		BoxFilled(x, y + h - linewidth, w, linewidth, color);                         // Bottom
		BoxFilled(x, y + linewidth, linewidth, h - 2 * linewidth, color);               // Left
		BoxFilled(x + w - linewidth, y + linewidth, linewidth, h - 2 * linewidth, color);   // Right
	}
}

void CDraw::BoxBordered(float x, float y, float w, float h, float border_width, DWORD color, DWORD color_border)
{
	BoxFilled(x, y, w, h, color);
	Box(x - border_width, y - border_width, w + 2 * border_width, h + border_width, border_width, color_border);
}

void CDraw::BoxFilled(float x, float y, float w, float h, DWORD color)
{
	vertex V[4];

	V[0].color = V[1].color = V[2].color = V[3].color = color;

	V[0].z = V[1].z = V[2].z = V[3].z = 0;
	V[0].rhw = V[1].rhw = V[2].rhw = V[3].rhw = 0;

	V[0].x = x;
	V[0].y = y;
	V[1].x = x + w;
	V[1].y = y;
	V[2].x = x + w;
	V[2].y = y + h;
	V[3].x = x;
	V[3].y = y + h;

	unsigned short indexes[] = { 0, 1, 3, 1, 2, 3 };

	pDevice->CreateVertexBuffer(4 * sizeof(vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL);
	pDevice->CreateIndexBuffer(2 * sizeof(short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB, NULL);

	VOID* pVertices;
	g_pVB->Lock(0, sizeof(V), (void**)&pVertices, 0);
	memcpy(pVertices, V, sizeof(V));
	g_pVB->Unlock();

	VOID* pIndex;
	g_pIB->Lock(0, sizeof(indexes), (void**)&pIndex, 0);
	memcpy(pIndex, indexes, sizeof(indexes));
	g_pIB->Unlock();

	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(NULL);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetStreamSource(0, g_pVB, 0, sizeof(vertex));
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetIndices(g_pIB);

	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	g_pVB->Release();
	g_pIB->Release();
}

void CDraw::BoxRounded(float x, float y, float w, float h, float radius, bool smoothing, DWORD color, DWORD bcolor)
{
	BoxFilled(x + radius, y + radius, w - 2 * radius - 1, h - 2 * radius - 1, color);   // Center rect.
	BoxFilled(x + radius, y + 1, w - 2 * radius - 1, radius - 1, color);            // Top rect.
	BoxFilled(x + radius, y + h - radius - 1, w - 2 * radius - 1, radius, color);     // Bottom rect.
	BoxFilled(x + 1, y + radius, radius - 1, h - 2 * radius - 1, color);            // Left rect.
	BoxFilled(x + w - radius - 1, y + radius, radius, h - 2 * radius - 1, color);     // Right rect.

																					  // Smoothing method
	if (smoothing)
	{
		CircleFilled(x + radius, y + radius, radius - 1, 0, quarter, 16, color);             // Top-left corner
		CircleFilled(x + w - radius - 1, y + radius, radius - 1, 90, quarter, 16, color);        // Top-right corner
		CircleFilled(x + w - radius - 1, y + h - radius - 1, radius - 1, 180, quarter, 16, color);   // Bottom-right corner
		CircleFilled(x + radius, y + h - radius - 1, radius - 1, 270, quarter, 16, color);       // Bottom-left corner

		Circle(x + radius + 1, y + radius + 1, radius, 0, quarter, true, 16, bcolor);          // Top-left corner
		Circle(x + w - radius - 2, y + radius + 1, radius, 90, quarter, true, 16, bcolor);       // Top-right corner
		Circle(x + w - radius - 2, y + h - radius - 2, radius, 180, quarter, true, 16, bcolor);    // Bottom-right corner
		Circle(x + radius + 1, y + h - radius - 2, radius, 270, quarter, true, 16, bcolor);      // Bottom-left corner

		Line(x + radius, y + 1, x + w - radius - 1, y + 1, 1, false, bcolor);       // Top line
		Line(x + radius, y + h - 2, x + w - radius - 1, y + h - 2, 1, false, bcolor);   // Bottom line
		Line(x + 1, y + radius, x + 1, y + h - radius - 1, 1, false, bcolor);       // Left line
		Line(x + w - 2, y + radius, x + w - 2, y + h - radius - 1, 1, false, bcolor);   // Right line
	}
	else
	{
		CircleFilled(x + radius, y + radius, radius, 0, quarter, 16, color);             // Top-left corner
		CircleFilled(x + w - radius - 1, y + radius, radius, 90, quarter, 16, color);        // Top-right corner
		CircleFilled(x + w - radius - 1, y + h - radius - 1, radius, 180, quarter, 16, color);   // Bottom-right corner
		CircleFilled(x + radius, y + h - radius - 1, radius, 270, quarter, 16, color);       // Bottom-left corner
	}
}

void CDraw::Text(const char *text, float x, float y, text_alignment alignment, int font, bool bordered, DWORD color, DWORD bcolor)
{
	if (!Draw.mFontSize) {
		this->AddFont("Arial Black", 16, true, false);
	}
	RECT rect;

	switch (alignment)
	{
	case lefted:
		if (bordered)
		{
			SetRect(&rect, x - 1, y, x - 1, y);
			pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, bcolor);
			SetRect(&rect, x + 1, y, x + 1, y);
			pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, bcolor);
			SetRect(&rect, x, y - 1, x, y - 1);
			pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, bcolor);
			SetRect(&rect, x, y + 1, x, y + 1);
			pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, bcolor);
		}
		SetRect(&rect, x, y, x, y);
		pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, color);
		break;
	case centered:
		if (bordered)
		{
			SetRect(&rect, x - 1, y, x - 1, y);
			pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, bcolor);
			SetRect(&rect, x + 1, y, x + 1, y);
			pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, bcolor);
			SetRect(&rect, x, y - 1, x, y - 1);
			pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, bcolor);
			SetRect(&rect, x, y + 1, x, y + 1);
			pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, bcolor);
		}
		SetRect(&rect, x, y, x, y);
		pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, color);
		break;
	case righted:
		if (bordered)
		{
			SetRect(&rect, x - 1, y, x - 1, y);
			pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, bcolor);
			SetRect(&rect, x + 1, y, x + 1, y);
			pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, bcolor);
			SetRect(&rect, x, y - 1, x, y - 1);
			pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, bcolor);
			SetRect(&rect, x, y + 1, x, y + 1);
			pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, bcolor);
		}
		SetRect(&rect, x, y, x, y);
		pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, color);
		break;
	}
}

void CDraw::Text(const char * text, Vector3 worldPosition, text_alignment alignment, int font, bool bordered, DWORD color, DWORD bcolor)
{
	Vector3 screenPos;
	if (this->WorldToScreen(worldPosition, &screenPos))
		Draw.Text(text, screenPos.x, screenPos.y, alignment, font, bordered, color, bcolor);
}

//void CDraw::Message(char *text, float x, float y, int font, int orientation)
//{
//	RECT rect = { x, y, x, y };
//	switch (orientation)
//	{
//	case lefted:
//		pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_CALCRECT | DT_LEFT, BLACK_A(255));
//
//		BoxRounded(x - 5, rect.top - 5, rect.right - x + 10, rect.bottom - rect.top + 10, 5, true, DARKGRAY_A(150), SKYBLUE_A(255));
//
//		SetRect(&rect, x, y, x, y);
//		pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_LEFT | DT_NOCLIP, ORANGE_A(255));
//		break;
//	case centered:
//		pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_CALCRECT | DT_CENTER, BLACK_A(255));
//
//		BoxRounded(rect.left - 5, rect.top - 5, rect.right - rect.left + 10, rect.bottom - rect.top + 10, 5, true, DARKGRAY_A(150), SKYBLUE_A(255));
//
//		SetRect(&rect, x, y, x, y);
//		pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_CENTER | DT_NOCLIP, ORANGE_A(255));
//		break;
//	case righted:
//		pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_CALCRECT | DT_RIGHT, BLACK_A(255));
//
//		BoxRounded(rect.left - 5, rect.top - 5, rect.right - rect.left + 10, rect.bottom - rect.top + 10, 5, true, DARKGRAY_A(150), SKYBLUE_A(255));
//
//		SetRect(&rect, x, y, x, y);
//		pFont[font]->DrawTextA(NULL, text, -1, &rect, DT_RIGHT | DT_NOCLIP, ORANGE_A(255));
//		break;
//	}
//}
//
//void CDraw::Message(int fontId, unsigned int x, unsigned int y, D3DCOLOR color, LPCSTR Message)
//{	// Create a colour for the text
//	D3DCOLOR fontColor = color;
//	RECT rct; //Font
//	rct.left = x;
//	rct.right = 1680;
//	rct.top = y;
//	rct.bottom = rct.top + 200;
//	pFont[fontId]->DrawTextA(NULL, Message, -1, &rct, 0, fontColor);
//}

void CDraw::Sprite(LPDIRECT3DTEXTURE9 tex, float x, float y, float resolution, float scale, float rotation)
{
	float screen_pos_x = x;
	float screen_pos_y = y;

	// Texture being used is 64x64:
	D3DXVECTOR2 spriteCentre = D3DXVECTOR2(resolution / 2, resolution / 2);

	// Screen position of the sprite
	D3DXVECTOR2 trans = D3DXVECTOR2(screen_pos_x, screen_pos_y);

	// Build our matrix to rotate, scale and position our sprite
	D3DXMATRIX mat;

	D3DXVECTOR2 scaling(scale, scale);

	// out, scaling centre, scaling rotation, scaling, rotation centre, rotation, translation
	D3DXMatrixTransformation2D(&mat, NULL, 0.0, &scaling, &spriteCentre, rotation, &trans);

	//pDevice->SetRenderState(D3DRS_ZENABLE, false);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG2, D3DTA_DIFFUSE);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->SetPixelShader(NULL);
	sSprite->Begin(NULL);
	sSprite->SetTransform(&mat); // Tell the sprite about the matrix
	sSprite->Draw(tex, NULL, NULL, NULL, 0xFFFFFFFF);
	sSprite->End();
}

int CDraw::FirstFontIndex()
{
	//return FontNr;
	for (int i = 0; i < mFontSize; i++)
	{
		if (pFont[i])
			return i;
	}
	return -1;
}

void CDraw::AddFont(const char* caption, float size, bool bold, bool italic)
{
	if (mFontSize < MAX_FONTS) {

		D3DXCreateFont(this->GetDevice(),
			size, 0, (bold) ? FW_BOLD : FW_NORMAL, 1, (italic) ? 1 : 0,
			DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH,
			(LPCWSTR)caption, &pFont[mFontSize]);

		++mFontSize;
	}
}

void CDraw::OnLostDevice()
{
	for (int i = 0; i < mFontSize; i++)
	{
		if (pFont[i])
			pFont[i]->OnLostDevice();
	}
}

void CDraw::OnResetDevice()
{
	for (int i = 0; i < mFontSize; i++)
	{
		if (pFont[i])
			pFont[i]->OnResetDevice();
	}
}

void CDraw::FontRelease()
{
	for (int i = 0; i < mFontSize; ++i)
	{
		if (pFont[i]) {
			pFont[i]->Release();
			pFont[i] = NULL;
		}
	}
}
