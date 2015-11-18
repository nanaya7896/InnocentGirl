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
	D3DXVECTOR3 EnemyAngle[30];
	//敵の移動スピード
	D3DXVECTOR3 EMoveSpeed[30];
	//敵の向きを変えるスピード関数
	D3DXVECTOR3 EnemyMoveAngleSpeed[30];
	//敵の最大出現数
	const int MAX_ENEMY = 30;
	
	D3DXVECTOR3 PlayerEnemyDistance[30];
	float AutoMoveSpeed;
	float AutoMove[30];
	//敵の移動制御用フレーム
	int EnemyMoveFrame;
	

	//エネミーの自動移動かプレイヤー追いかけるかの判定
	bool TransformEnemy[30];

	bool EnemyMoveFlag[30];

public:

	


	//コンストラクタ
	Enemy();
	//仮想化デストラクタ
	virtual ~Enemy();

	void Update(D3DXVECTOR3 pPos);

	void Draw();

	void Load();

	float EnemySearch(D3DXVECTOR3 pPos);

	BOOL EneymHit(D3DXVECTOR3 *pmin,D3DXVECTOR3 *pmax);

	void EnemyMove();

	//ランダムで値を生成するヘルパー関数
	float Random(float min, float max);

protected:
	static EnemyBox em[30];




};

