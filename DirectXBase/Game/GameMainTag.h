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
public:
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