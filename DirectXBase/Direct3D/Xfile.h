#pragma once

#include"../Global.h"
#include"../DirectInput/directInput.h"
#include"direct3d.h"
class X_FILE :public Direct3D
{
private:
	

public:
	//メンバ変数
	D3DXVECTOR3 pos;
	D3DXVECTOR3 rota;
	D3DXVECTOR3 scale;



	X_FILE();
	X_FILE(LPCWSTR FileName);
	~X_FILE();

	//Xファイル読み込み関数
	BOOL XfileLoader(LPCWSTR name);
	//Xファイルセット関数
	BOOL SetupMatrices(LPDIRECT3DDEVICE9 pD3D9,DWORD lasttime);


	//Xファイル描画関数
	void Render(D3DXVECTOR3 *pos, D3DXVECTOR3 *rota, D3DXVECTOR3 *scale, LPDIRECT3DTEXTURE9 pTex9);
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
	
	
	D3DXVECTOR3 PlayerPos;
	D3DXVECTOR3 PlayerAngel;
	D3DXVECTOR3 PlayerVec;
	
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