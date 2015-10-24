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
	//マテリアルの読み込み
	//テクスチャの読み込み
	BOOL MaterialRead(LPDIRECT3DDEVICE9 pD3D9);

	
	//環境光の設定
	BOOL NatureLight(LPDIRECT3DDEVICE9 pD3D9);
	//Xファイル描画関数
	BOOL Render(LPDIRECT3DDEVICE9 pD3D9);
	//デバイス解放
	void CleanUp();

	DirectInput dInput;
	


	float looptime=0.0f;
	
	float speed=5.0f;
	//90度/s
	float anglesp = D3DX_PI / 2;
	DWORD MaterialNum = 0L;

	

protected:
	LPD3DXMESH              g_pMesh = NULL;
	D3DMATERIAL9*			g_pMaterial=NULL;
	LPDIRECT3DTEXTURE9*		g_pTexture = NULL;
	D3DXVECTOR3 PlayerPos;
	D3DXVECTOR3 PlayerAngel;
	D3DXVECTOR3 PlayerVec;
	D3DXMATERIAL* d3dxMaterials;
	//一時記憶用バッファ
	LPD3DXBUFFER pD3DXMatrlBuffer;
	//ビュー変換
	D3DXVECTOR3 vEyePt, vLookatPt, vUpVec;
	D3DXMATRIXA16
		matWorld,		//
		matView,		//
		matProj;	//射形変換
	D3DMATERIAL9 mat9;
	D3DXVECTOR3  vecDir;
	D3DLIGHT9  light;

	
};