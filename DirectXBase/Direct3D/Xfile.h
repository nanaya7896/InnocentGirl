#pragma once

#include"../Global.h"

class X_FILE
{
private:


public:
	//Xファイル読み込み関数
	BOOL XfileLoader(LPDIRECT3DDEVICE9 pD3D9 ,LPCWSTR name);
	//Xファイルセット関数
	BOOL SetupMatrices(LPDIRECT3DDEVICE9 pD3D9);
	//環境光の設定
	BOOL NatureLight(LPDIRECT3DDEVICE9 pD3D9);
	//Xファイル描画関数
	BOOL Render();
	//デバイス解放
	BOOL CleanUp();

protected:
	LPD3DXMESH              g_pMesh = NULL;
	D3DXMATRIXA16   matWorld,		//
					matView,		//
					matProj;		//射形変換
	//ビュー変換
	D3DXVECTOR3 vEyePt, vLookatPt, vUpVec;
};