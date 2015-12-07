#pragma once

#include"../SceneChanger/ISceneChanger.h"
#include"../SceneChanger/BaseScene.h"
#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../DirectInput\directInput.h"
#include "../Player/Ball.h"
#include"../Direct3D/Camera.h"
#include"../DirectXAnimation/MyAllocateHierarchy.h"
#include"../DirectXAnimation/AnimateObject.h"
#include"../Direct3D/font.h"
#include"Title.h"
#include"Result.h"
#include"Gameover.h"
#include"../DirectSound/dxsound.h"



class GameMainDodge :public BaseScene, Direct3D
{
private:
	//テクスチャインスタンス
	Texture timeTexture[10];
	//スプライトインスタンス
	Sprite timeSprite[2];
	//プレイヤーインスタンス
	Player d_player;
	//ボールインスタンス
	Ball ball;
	//カメラインスタンス
	Camera *camera;
	//アニメーションインスタンス
	MyAllocateHierarchy mah;
	//メッシュインスタンス
	CSkinMesh cskinMesh;
	//マップのインスタンス
	Map mapDog1P;
	//enemyのインスタンス
	Enemy Dog_Enemy;
	//サウンドのインスタンス
	CSound wave[3];
	//時間用メンバ変数
	int time;
	int timeframe;
	//time10の位
	int tentime = 9;
	//time1の位
	int onetime = 0;
	//スタミナ上限値
	const int MAX_STAMINA = 360;
	//スタミナ下限値
	const int LOS_STAMINA = 0;

	bool Ballthrow;

public:

	//現在のスタミナ
	int currentStamina;
	//スタミナを求める関数
	int sta(int currentStamina);
	//スタミナの上限下限制御する関数
	int sta_clamp(int currentstamina, int low, int high);
	D3DXVECTOR3 CameraPosition;

	//コンストラクタ
	GameMainDodge(ISceneChanger *changer);
	//デストラクタ
	~GameMainDodge();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;


protected:
	D3DXVECTOR3 d_PlayerPos;
	D3DXVECTOR3 d_PlayerAngle;
	D3DXVECTOR3 d_PlayerSpeed;
	D3DXVECTOR3 BallPos;
};