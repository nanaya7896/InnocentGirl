#pragma once
#include"../Global.h"
#include"../DirectInput/directInput.h"
#include"../Direct3D/Xfile.h"
#include"../Direct3D/Texture.h"
#include"../Game/Map.h"
#include"../PhysicBases/PhysicBase.h"

#include"Player.h"
#include"../Enemy/Enemy.h"
#include"../Xinput/XbonInput.h"




class Ball : public Map
{
private:

	float unitTime;
	//バンドさせるための係数
	float Bound = -1.0f;
	float BoundCoefficient=0.0f;
	//ボールの半径
	float ballR = 0.5f;
	X_FILE Xball;
	X_FILE Xball2P;
	Texture Tball;
	Texture Tball2P;
	PhysicBase pb;
	float ballSpeed;

	

	//プレイヤーインスタンス
	Player bplayer;

	//コントローラーインスタンス
	XboxInput pInput;
public:
	//ボールの移動速度
	float ballspeed;
	//重力
	D3DXVECTOR3 G;
	//加速度
	D3DXVECTOR3 Vel;
	//場所
	D3DXVECTOR3 Pos;

	//ボールのフラグ
	bool Ball_flag;
	//ボールフレーム
	unsigned long frame = 0;
	//ボールにかける減速の力を管理するフレーム
	int ballStopFram = 30;
	//ボールの減速を管理する関数
	int ballStop();
	//コンストラクタ
	Ball();
	//デストラクタ
	~Ball();
	//ボール作成
	HRESULT BallLoad();
	void BallCreate(D3DXVECTOR3 bPos);
	void BallCreate2P(D3DXVECTOR3 bPos);
	//ボールの移動
	D3DXVECTOR3 BallMove(D3DXVECTOR3 bPos,D3DXVECTOR3 playerPos, D3DXVECTOR3 playerAngle);
	D3DXVECTOR3 BallMove2P(D3DXVECTOR3 bPos);

	D3DXVECTOR3 ballpos;
	D3DXVECTOR3 ballmaxa;//(ballpos.x + 0.5f, ballpos.y + 0.5f, ballpos.z + 0.5f);
	D3DXVECTOR3 ballmina;// (ballpos.x - 0.5f, ballpos.y - 0.5f, ballpos.z - 0.5f);
	bool bHit;

	D3DXVECTOR3 Init(D3DXVECTOR3 ballpos);

	
protected:


};