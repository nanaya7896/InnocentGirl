#pragma once
#include"../Global.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/texture.h"

struct BoundingBox
{
	D3DXVECTOR3 minv;	//最少頂点
	D3DXVECTOR3 maxv;	//最大頂点


};



class Map : public X_FILE
{
private:
	//Textureのインスタンス生成
	Texture tfloor[8];
	Texture tfloorGround[11];
	Texture tpanelSky[4];
	Texture tpanelSun;
	Texture tBuil[4];
	BoundingBox buildingsbox[5];


public:
	//コンストラクタ
	Map();
	//デストラクタ
	~Map();
	
	//メンバ関数
	HRESULT LoadBuldings();
	void MapRender();
	BOOL HitTikei(D3DXVECTOR3 *pmina,D3DXVECTOR3 *pmaxa);


	//メンバ変数
	DWORD numv[50], stride[50];
	LPDIRECT3DVERTEXBUFFER9 pvb9;
	BYTE *pvertices;
	HRESULT hr[50];
	D3DXVECTOR3 lminv, lmaxv;
	//Xfileのインスタンス生成
	X_FILE xfloor;
	X_FILE xpanelSky;
	X_FILE xBuil[4];
protected:
	int i = 0;


};