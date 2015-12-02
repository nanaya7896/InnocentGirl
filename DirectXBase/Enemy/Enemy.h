#pragma once
#include"../Global.h"
#include"../Direct3D/direct3d.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/texture.h"
#include"../Game/Map.h"
#include"../DirectSound/dxsound.h"

struct EnemyBox{
	D3DXVECTOR3 minv;
	D3DXVECTOR3 maxv;
};
struct Score
{
	int Score1P;
	int Score2P;
};



class Enemy : public Direct3D
{
private:
	Texture t_Enemy;
	X_FILE x_Enemy;
	Map eMap;


	//境界ボックス生成用変数
	LPDIRECT3DVERTEXBUFFER9 pvb9;
	BYTE *pvertices;
	HRESULT hr[31];
	D3DXVECTOR3 lminv, lmaxv;
	//メンバ変数
	DWORD numv[31], stride[31];
	//敵の場所
	D3DXVECTOR3 EnemyPos[31];
	//敵の向いている方向
	D3DXVECTOR3 EnemyAngle[31];
	//敵の移動スピード
	D3DXVECTOR3 EMoveSpeed[31];
	//敵の向きを変えるスピード関数
	D3DXVECTOR3 EnemyMoveAngleSpeed[31];
	//敵の最大出現数
	const int MAX_ENEMY = 31;

	
	
	//プレイヤーとユキちゃんの距離の差を保存する
	D3DXVECTOR3 PlayerEnemyDistance[31];
	//三平方の定理で求めた対象物との距離差
	float AutoMoveSpeed;
	//行動する象限を判断する関数
	float AutoMove[31];
	//敵の移動制御用フレーム
	int EnemyMoveFrame;
	bool MapHit[31];

	//追跡者フラグ
	bool SearcherFlag[31];
	//追跡者移動制御フレーム
	int SearcherFrame;
	//エネミーの自動移動かプレイヤー追いかけるかの判定
	bool TransformEnemy[31];

	bool EnemyMoveFlag[31];
	D3DXVECTOR3 maxe;//(mypos.x + 0.5f, mypos.y + 0.5f, mypos.z + 0.5f);
	D3DXVECTOR3 mine;// (mypos.x - 0.5f, mypos.y - 0.5f, mypos.z - 0.5f);
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

	//追跡者の移動関数
	void SerachMove();
	//ランダムで値を生成するヘルパー関数
	float Random(float min, float max);
	//スコア
	int score1P();
	int score2P();

	//Waveファイル
	CSound wave[2];

protected:
	static EnemyBox em[31];
	static Score dscore;


};

