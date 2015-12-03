#pragma once
#include"../Global.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/texture.h"
//#include"../Enemy/Enemy.h"
struct BoundingBox
{
	D3DXVECTOR3 minv;	//最少頂点
	D3DXVECTOR3 maxv;	//最大頂点
};



class Map : public X_FILE
{
private:
	//Textureのインスタンス生成
	Texture ttfloor;
	Texture tpanelSky[4];
	Texture tSky;
	Texture tpanelSun;
	Texture tBuil[4];
	//Xfileのインスタンス生成
	X_FILE xfloor;
	X_FILE xpanelSky;
	X_FILE xBuil[4];
	X_FILE xSky;
	//Enemyのインスタンス生成
	//Enemy Cem;
	//メンバ変数
	DWORD numv[8], stride[8];
	LPDIRECT3DVERTEXBUFFER9 pvb9;
	BYTE *pvertices;
	HRESULT hr[8];
	D3DXVECTOR3 lminv, lmaxv;


public:
	//コンストラクタ
	Map();
	//デストラクタ
	~Map();
	
	//メンバ関数
	HRESULT LoadBuldings();
	void MapRender();
	//プレイヤーと地形のあたり判定
	BOOL HitTikei(D3DXVECTOR3 *pmina,D3DXVECTOR3 *pmaxa);
	//敵の地形とのあたり判定
	BOOL HitETikei(D3DXVECTOR3 *emina, D3DXVECTOR3 *emaxa);
	//カメラと地形のあたり判定
	BOOL HitCTikei(D3DXVECTOR3 *cmina, D3DXVECTOR3 *cmaxa);

protected:
	int i = 0;

	static BoundingBox buildingsbox[8];
};