#pragma once

#include"../SceneChanger/ISceneChanger.h"
#include"../SceneChanger/BaseScene.h"
#include "../Direct3D\texture.h"
#include "../Direct3D\sprite.h"
#include "../Direct3D/direct3d.h"
#include "../DirectInput\directInput.h"
#include"../Player/Player.h"
#include"../Direct3D/Camera.h"

#include"Map.h"
#include"../DirectXAnimation/MyAllocateHierarchy.h"
#include"../DirectXAnimation/AnimateObject.h"
#include"../Direct3D/font.h"
#include"../Enemy/Enemy.h"
#include"Title.h"
#include"Result.h"
#include"Gameover.h"
#include"../DirectSound/dxsound.h"

class GameMainTag :public BaseScene, Direct3D
{
private:
	//テクスチャインスタンス
	Texture timeTexture[10];
	//スプライトインスタンス
	Sprite timeSprite[2];
	//プレイヤーインスタンス
	Player player;

	//カメラインスタンス
	Camera *camera;
	//アニメーションインスタンス
	MyAllocateHierarchy mah;
	//メッシュインスタンス
	CSkinMesh cskinMesh;
	//マップのインスタンス
	Map map1P;
	//enemyのインスタンス
	Enemy gmtEnemy;
	//サウンドのインスタンス
	CSound wave[3];
	//時間用メンバ変数
	int time;
	int timeframe;
	//time10の位
	int tentime = 6;
	//time1の位
	int onetime = 0;

	//スコア仮置き
	DirectXText score1;
	DirectXText score2;
	int Score1p;
	int Score2p;

	//スタミナ
	//文字
	//Texture Stamina_bar;
	//Sprite Stamina_bar;
	//白
	Texture Stamina_W;
	Sprite sStamina_W;
	//黄色
	Texture Stamina_Y;
	Sprite sStamina_Y;
public:



	//スタミナ上限値
	const int MAX_STAMINA=360;
	//スタミナ下限値
	const int LOS_STAMINA = 0;
	//現在のスタミナ
	int currentStamina;
	//スタミナを求める関数
	int sta(int currentStamina);
	//スタミナの上限下限制御する関数
	int sta_clamp(int currentstamina , int low, int high);
	D3DXVECTOR3 CameraPosition;

	//コンストラクタ
	GameMainTag(ISceneChanger *changer);

	//デストラクタ
	~GameMainTag();

	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;



protected:
	D3DXVECTOR3 PlayerPos;
	D3DXVECTOR3 PlayerAngle;
	D3DXVECTOR3 PlayerSpeed;

	
};