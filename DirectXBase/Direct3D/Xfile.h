#pragma once

#include"../Global.h"
#define SAFE_DELETE(p)  { if (p) { delete (p);     (p)=NULL; } }
#define SAFE_RELEASE(p) { if (p) { (p)->Release(); (p)=NULL; } }


class X_FILE
{
protected:
	LPDIRECT3DDEVICE9       pDEV;        // 描写用デバイス
	LPD3DXMESH              pMesh;       // Our mesh object in sysmem
	D3DMATERIAL9*           pMat;        // Materials for our mesh
	LPDIRECT3DTEXTURE9*     pTex;        // Textures for our mesh
	DWORD                   dwNum;       // Number of mesh materials
	friend int _stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
public:
	X_FILE(LPDIRECT3DDEVICE9, LPCSTR);    //Constructor
	~X_FILE();                           //Destructor
	void	SetupMatrices(LPDIRECT3DDEVICE9);
	void	Render();
};