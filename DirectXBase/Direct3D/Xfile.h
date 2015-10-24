#pragma once

#include"../Global.h"
#include"../DirectInput/directInput.h"

class X_FILE
{
private:
	

public:
	X_FILE();

	~X_FILE();
	//Xファイル読み込み関数
	BOOL XfileLoader(LPDIRECT3DDEVICE9 pD3D9 ,LPCWSTR name);
	//Xファイルセット関数
	BOOL SetupMatrices(LPDIRECT3DDEVICE9 pD3D9, HWND hWnd,DWORD lasttime);
	//環境光の設定
	BOOL NatureLight(LPDIRECT3DDEVICE9 pD3D9);
	//Xファイル描画関数
	BOOL Render();
	//デバイス解放
	BOOL CleanUp();
	DirectInput dInput;
	


	float looptime=0.0f;
	D3DXVECTOR3 PlayerPos;
	D3DXVECTOR3 PlayerAngel;
	float speed=5.0f;
	//90度/s
	float anglesp = D3DX_PI / 2;


	D3DXVECTOR3 PlayerVec;

protected:
	LPD3DXMESH              g_pMesh = NULL;
	
	//ビュー変換
	D3DXVECTOR3 vEyePt, vLookatPt, vUpVec;
	D3DXMATRIXA16
		matWorld,		//
		matView,		//
		matProj;	//射形変換
	
	
};