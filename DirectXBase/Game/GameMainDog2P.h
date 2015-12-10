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



class GameMainDodge2P :public BaseScene, Direct3D
{
private:
	//テクスチャインスタンス
	Texture dtimeTexture[10];
	//スプライトインスタンス
	Sprite dtimeSprite[2];
	//プレイヤーインスタンス
	Player d_player[2];
	//ボールインスタンス
	Ball d_ball[2];
	//カメラインスタンス
	Camera *d_camera;
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
	bool Ballthrow2;
public:

	//現在のスタミナ
	int currentStamina;
	//スタミナを求める関数
	int sta(int currentStamina);
	//スタミナの上限下限制御する関数
	int sta_clamp(int currentstamina, int low, int high);
	D3DXVECTOR3 CameraPosition;
	D3DXVECTOR3 CameraPosition2;
	//コンストラクタ
	GameMainDodge2P(ISceneChanger *changer);
	//デストラクタ
	~GameMainDodge2P();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;


protected:
	D3DXVECTOR3 d_PlayerPos;
	D3DXVECTOR3 d_PlayerAngle;
	D3DXVECTOR3 d_PlayerPos2;
	D3DXVECTOR3 d_PlayerAngle2;
	D3DXVECTOR3 d_PlayerSpeed;
	D3DXVECTOR3 BallPos;
	D3DXVECTOR3 BallPos2;
};