#pragma once

#include"../Global.h"

class X_FILE
{
private:


public:
	BOOL XfileLoader(LPDIRECT3DDEVICE9 pD3D9 ,LPCWSTR name);
	BOOL SetupMatrices(LPDIRECT3DDEVICE9 pD3D9);
	BOOL Render();

protected:
	LPD3DXMESH              g_pMesh = NULL;

};