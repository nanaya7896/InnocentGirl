#pragma once
#include"../Global.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/texture.h"



struct EnemyBox{
	D3DXVECTOR3 minv;
	D3DXVECTOR3 maxv;
};

class Enemy : public Direct3D
{
private:
	Texture t_Enemy;
	X_FILE x_Enemy;

	
	//境界ボックス生成用変数
	LPDIRECT3DVERTEXBUFFER9 pvb9;
	BYTE *pvertices;
	HRESULT hr[31];
	D3DXVECTOR3 lminv, lmaxv;
	//メンバ変数
	DWORD numv[31], stride[31];
	//敵の場所
	D3DXVECTOR3 EnemyPos[30];
	//敵の向いている方向
	D3DXVECTOR3 EnemyAngle;
	//敵の移動スピード
	D3DXVECTOR3 EMoveSpeed;

	//敵の最大出現数
	const int MAX_ENEMY = 30;
	
	//敵の移動制御用フレーム
	int EnemyMoveFrame;

	//エネミーの自動移動かプレイヤー追いかけるかの判定
	bool TransformEnemy[30];

public:

	


	//コンストラクタ
	Enemy();
	//仮想化デストラクタ
	virtual ~Enemy();

	void Update();

	void Draw();

	void Load();

	BOOL EnemyProbe(float *pfoundangley);

	BOOL EneymHit(D3DXVECTOR3 *pmin,D3DXVECTOR3 *pmax);

	void EnemyMove();

	//ランダムで値を生成するヘルパー関数
	float Random(float min, float max);

protected:
	static EnemyBox em[30];




};

